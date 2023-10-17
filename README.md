# Vocabulary Aquisition & Comprehension Tool - CIS 278

## Dependencies
NOTE: This project depends on ncurses.h which is a Unix library. It has only been tested on Linux, but MacOS and other Unix-based OSs should work. If you are using Windows, setup [WSL2]([url](https://www.windowscentral.com/how-install-wsl2-windows-10)https://www.windowscentral.com/how-install-wsl2-windows-10) so that you can follow the instructions below.

To build this project, you need g++ and ncurses.h
On Debian-based systems (Debian, Ubuntu, Linux Mint, etc. [WSL2 is usually Debian-based by default]) you can run the following
```bash
sudo apt install g++ libncurses-dev
```

# Building
To build the project, cd into VACT/src and run the following
```bash
g++ -o ../bin/main main.cpp -lncurses
```
# Execution
To execute the project cd into VACT/bin and run the following
```bash
./main
```





