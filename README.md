# alb
The _ALB_ programming language (in development).


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

`(Any text before a BEGIN or after an END statement would be ingored by the interpreter. So this can be used as comments)
BEGIN
(some code...)
END`


# _Installation_:

REQUIREMENTS:

- G++

- Any Linux distribution

- Basic knowledge of Linux shell commands

1. Clone this repository into your computer.

2. Open a terminal (Ctrl+Alt+T) and move to the directory where the repository has been cloned.

3. Type `g++ alb.cpp -c`

4. After that, type `g++ alb.o -o alb`

# _Execution_:

1. Write your program (can be used any file extension, but it is recommended to use `.alb`. Also, the file must be in the same directory as the interpreter executable -> `alb`).

2. Open a terminal (Ctrl+Alt+T) and move to the directory where your code is located.

3. Type `./alb`

4. The interpreter will ask you the name of your file. Then, write it.

5. Then, the program should be running.
