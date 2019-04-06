#!/bin/bash
g++ alb.cpp -c
g++ alb.o -o alb
echo "Interpreter compiled and built successfully\n"

sudo cp alb /usr/bin/
rm alb
rm alb.o
echo "\n"
echo "    _    _     ____  "
echo "   / \  | |   | __ ) "
echo "  / _ \ | |   |  _ \ "
echo " / ___ \| |___| |_) |"
echo "/_/   \_\_____|____/ "
echo "The ALB interpreter is now ready to use in version 0.0.4. Type \"alb fileName\" to run your code.\n"

read -p "Do you want to install the syntax highlighting package for the Nano editor? [Y/n] " answer
if [[ $answer=="y" || $answer=="Y" ]]; then
	cp alb.nanorc /usr/share/nano/
	echo "Copied alb.nanorc to /usr/share/nano/alb.nanorc\n"
	echo "Syntax highlighting for ALB installed successfully.\n"
fi