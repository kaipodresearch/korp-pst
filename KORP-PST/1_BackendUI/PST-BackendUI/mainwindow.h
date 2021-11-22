#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "about.h"


#include <QApplication>
#include <QMessageBox>
#include <QTimer>
#include <QFile>
#include <QDir>

#include <windows.h>

#pragma comment(lib, "Shlwapi.lib")
#pragma comment(lib, "Advapi32.lib")

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    bool is_user_admin();

    void get_information();

    void dropper(QString arg_username,
                 QString arg_password,
                 QString arg_computer_name,
                 QString arg_ui_type);

    void powershell_command();

    void create_temporary_files();

    wchar_t* get_current_path(wchar_t* arg_dest, DWORD arg_dest_size);

    void remote_desktop(QString arg_target_ip);

    void on_actionAbout_triggered();

    void on_actionExit_triggered();

    void on_pushButtonConnection_clicked();

    void on_pushButtonExit_clicked();

    void on_actionMode_triggered();

    void on_actionCheck_Update_triggered();

    void on_actionKaipod_triggered();

private:
    Ui::MainWindow *ui;
    About aboutWindowForm;
};
#endif // MAINWINDOW_H
