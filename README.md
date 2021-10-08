# Kaipod Offensive Research Project: PST
![Generic badge](https://img.shields.io/badge/version-1.0.0-red.svg)
![Maintenance](https://img.shields.io/badge/Maintained%3F-yes-green.svg)
![Generic badge](https://img.shields.io/badge/Windows-Passed-blue.svg)

# PST Overview
KORP-PST (Codename: Triumph) is an penetration testing tool for windows infrastructure that has been developing by Kaipod Homeland Security as a research offensive project. It can be used in red-teaming project and penetration testing of an active directory based environment. 

KORP PST has direct dependency to psexec and some other handy tools for windows environment (like pass-the-hash module of mimikatz). However, in the near future, we have a plan to implement our own tool for doing pass-the-hash and also executing command on remote machines. 

## KORP-PST Components:
KORP PST consists of the following executable components:
	- pst.exe: It is main executable that get credentials to spawn file manager.
	- engine.exe: It is doing pass the hash operation in the background to spawn file manager.
	- fm.exe: it is a console based file system manager.
	- fm-ui.exe: it is a graphical based file system manager.

## Change log of PST:
KORT PST v2.0.0:
- Change PsExec with KORP-PsExec
- Change Mimikatz with KORP-PTH
		
KORP PST v1.0.0:
- Graphical based file system
- Domain information summary
- Active machines in the domain
		
KORP PST v0.1.0:
- Console based file system
- Getting remote desktop connection
- Delete/Edit files and directories
- Executing command on remote machine
- Upload/Download files from remote machines
- Show/Edit files and directories attributes

## Change log of components and development summary:

KORP pst.exe:
- Pass the hash
- Command execution
- Remote desktop connection

KORP pst-engine.exe:
- Port it from mimikatz to customized module
- FUD it from main anti-viruses

KORP pst-fmc.exe:
- Change directories
- Make files
- Make directories
- Delete files
- Delete directories
- Show files attribute
- Show directories attribute
- Edit files attribute
- Edit directories attribute
- List directories contents
- Clear the screeen
- Getting cmd.exe access
- Getting remote connection (RDP) access
- Show non-latin files/directories names
- Download files from remote machines
- Upload files to remote machines

KORP pst-fmg.exe:
- It is been developing.

# Contact:
- e-mail: m.kahsari@gmail.com
- website: kaipod.ir
- telegram: kaipod
