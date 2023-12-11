# Vocab Acquisition & Comprehension Tool (VACT) - CIS 278

## Installation
```
git clone https://github.com/AlexKCA/VACT.git
```

## Dependencies
NOTE: This project depends on ncurses.h which is a Unix library. *It has only been tested on Linux*, but MacOS and other Unix-based OSs should work. 

If you are using Windows, [WSL](https://learn.microsoft.com/en-us/windows/wsl/install) should allow you to run this project. However, I haven't specifically tested it. Alternatively, you could use a full-on virtual machine. However, WSL is more convienient.

To build this project, you will need g++ and ncurses.h


**Debian-based (WSL, Ubuntu, Debian, Linux Mint)**
```
sudo apt install g++ libncurses-dev
```

**Arch**
```
sudo pacman -S ncurses gcc
```

**MacOS**
```
brew install ncurses g++
```

## Building & Running
To build the project, cd into VACT/src and run the following

```sh build.sh```

In VACT/bin Run the project with

```./main```


## Hotkeys
While viewing document:
```
q - quit
h - left
j - down
k - up
l - right
<Enter> - Select/Continue
```

## Workflow
1. Go to ```VACT/res/files/``` and add a ```.txt``` file with the text you want to process (or don't; there are some default files).
2. Build and run.
3. Go through your file. Add entries to your dictionary and set your familiarity with particular words.
