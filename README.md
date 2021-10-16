# Kaipod Offensive Research Project: PST
![Generic badge](https://img.shields.io/badge/version-0.1.0-red.svg)
![Maintenance](https://img.shields.io/badge/Maintained%3F-yes-green.svg)
![Generic badge](https://img.shields.io/badge/Windows-Passed-blue.svg)

KORP-PST (Codename: Triumph) is an penetration testing tool for windows infrastructure that has been developing by Kaipod Homeland Security as an offensive research project. It can be used in red-teaming project and penetration testing of an active directory based environment. 

<p align="center">
<img src="https://github.com/kaipodresearch/korp-pst/blob/main/kaipod-logo.png">
</p>

KORP PST has direct dependency to psexec and some other handy tools for windows environment (like pass-the-hash module of mimikatz). However, in the near future, we have a plan to implement our own tool for doing pass-the-hash and also executing command on remote machines. 

## KORP-PST Components:
KORP PST consists of the following executable components:
- **pst.exe:** It is main executable that get credentials to spawn process and executing commands.
- **pst-engine.exe:** It is doing pass the hash operation in the background to spawn file manager with right privileges.
- **pst-fmc.exe:** it is a console based file system manager.
- **pst-fmg.exe:** it is a graphical based file system manager (It will add to the pst in the near future).

## Development of the PST:
 ![](https://img.shields.io/static/v1?label=&message=PST-v0.1.0:&color=brown)

- Spawn CMD.exe
- Getting remote desktop connection

## Change log of main components:

![](https://img.shields.io/static/v1?label=&message=pst.exe:&color=blue)
- Getting credentials
- Spawn CMD.exe
- Make RDP Connection

![](https://img.shields.io/static/v1?label=&message=pst-engine.exe:&color=blue)
- Pass-the-hash module
- FUD it from main anti-viruses

# Contact:
- e-mail: m.kahsari@gmail.com
- website: kaipod.ir
- telegram: kaipod
