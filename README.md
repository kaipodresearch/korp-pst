# Kaipod Offensive Research Project: PST
![Generic badge](https://img.shields.io/badge/version-1.1.0-red.svg)
![Maintenance](https://img.shields.io/badge/Maintained%3F-yes-green.svg)
![Generic badge](https://img.shields.io/badge/Windows-Passed-blue.svg)

KORP-PST (Codename: Triumph) is a penetration testing tool for windows infrastructure that has been developing by Kaipod Homeland Security as an offensive research project. It can be used in the red-teaming projects and penetration testing of an active directory-based environment.

<p align="center">
<img src="https://github.com/kaipodresearch/korp-pst/blob/main/v1.1.0.PNG">
</p>

KORP PST has a direct dependency on psexec and some other handy tools for the windows environments (like the pass-the-hash module of mimikatz). However, in the near future, we have a plan to implement our own tool for doing pass-the-hash and also executing commands on remote machines. 

## KORP-PST Components:
KORP PST consists of the following executable components:
- **pst.exe:** It is main executable that get credentials to spawn process and executing commands.
- **pst-engine.exe:** It is doing pass the hash operation in the background to spawn file manager, making rdp connection and other useful things with right privileges (It is using mimikatz pass the hash module).
- **pst-fmc.exe:** it is a console based file system manager.
- **pst-fmg.exe:** it is a graphical based file system manager (It will add to the pst in the near future).

## Development of the PST:
![](https://img.shields.io/static/v1?label=&message=pst.exe:&color=blue)
- Getting credentials
- Spawn CMD.exe
- Make RDP Connection
- Spawn console based file manager

![](https://img.shields.io/static/v1?label=&message=pst-engine.exe:&color=blue)
- Pass-the-hash module
- FUD it from some anti-viruses

![](https://img.shields.io/static/v1?label=&message=pst-fmc.exe:&color=blue)
- Change directories
- Make files
- Make directories
- Delete files
- Delete directories
- List directories content
- Show files/directories attributes
- Change files/directories attributes
- Make an RDP connection with remote machine
- Create an CMD.exe instance of remote machine
- Upload and Download files from/to remote machine
		
# Bug Tracker:
![](https://img.shields.io/static/v1?label=&message=pst-v1.1.0:&color=red)
- no bug no pain. :D

# Contact:
- e-mail: m.kahsari@gmail.com
- website: kaipod.ir
- telegram: kaipod
