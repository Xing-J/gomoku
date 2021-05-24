# Documentation

Documentation for the entire project.

## Setup

### Windows

Install [Groff for Windows](http://gnuwin32.sourceforge.net/packages/groff.htm) and [Make for Windows](http://gnuwin32.sourceforge.net/packages/make.htm) and proceed to the compiling.

### Linux

Run the following commands to install Groff and Make:

```bash
# debian based systems
sudo apt-get update && sudo apt-get install groff make

# arch based systems
sudo pacman -S groff make
```

## Compiling

The documentation is compiled using Groff with the Make dependency management system. Run the make command to compile:

```bash
make

# to remove older versions of the documentation
make clean
```
