# alb

The _ALB_ programming language (in development).

[![current version 0.0.4](https://img.shields.io/badge/ALB%20current%20version-0.0.4-brightgreen.svg)](http://proshare.epizy.com) [![last stable version 0.0.2](https://img.shields.io/badge/last%20stable%20version-0.0.2-brightgreen.svg)](http://proshare.epizy.com) [![build passing](https://img.shields.io/badge/build-passing-brightgreen.svg)](http://proshare.epizy.com)

# *Keywords available:*

- `BEGIN`: beginning of program (cannot be used inside another `BEGIN` statement -> `ERROR 001`)

- `END`: end of program (cannot be used before a `BEGIN` statement -> `ERROR 002`)

- `out`: print on screen (equivalent to C `printf()`):

  `out` USAGE: `out elements ;`
  
- `NEWL`: new line (equivalent to `\n`). Must be used between `out` and `;`

- `repeat`: standard loop:
  
  `repeat` USAGE: `repeat times (code...) ENDLOOP`. `times` can be an integer (finite amount of iterations), or `infinity` (infinite amount of iterations. Must be cut with Ctrl+C).

- `ENDLOOP`: end of loop (must be used after a `repeat` that is not closed)


# _The_ ALB _program structure:_

```
// Comments...
BEGIN
(some code...)
END
```


# _Installation_:

REQUIREMENTS:

- G++

- Git

- Any Linux distribution

- Basic knowledge of Linux shell commands

- Have root permissions

1. Open a terminal (Ctrl+Alt+T) and move to your personal folder (type `cd ~`).

2. Clone this repository (type `git clone https://github.com/albertonl/alb.git`).

3. Type `cd alb/`.

4. Type `chmod +x install.sh`.

5. Run the installer script (install.sh) by typing `./install.sh`.

# _Execution_:

1. Write your program (can be used any file extension, but it is recommended to use `.alb`).

2. Open a terminal (Ctrl+Alt+T) and move to the directory where your code is located.

3. Type `alb fileName` (changing `fileName` by the name of your program, including the file extension).

4. Then, the program should be running.

# _Latest updates:_

- V 0.0.1: initial interpreter

- V 0.0.2: statements can be separated by spaces and lines, and tabs can be used at the beginning of statements. Added comments (`//` at the beginning of the comment. Comments have to be alone in a line).

- V 0.0.3: now the file name must be specificated when calling the interpreter in the same command. New installer script (only for Linux).

- V 0.0.3 B: added alb.nanorc for syntax coloring support for the ALB Programming Language in the Nano editor in GNU/Linux and UNIX based systems.

- V 0.0.4: various bug fixes.
