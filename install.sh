#!/bin/bash
g++ alb.cpp -c
g++ alb.o -o alb
echo "Interpreter compiled and built successfully\n"

sudo cp alb /usr/bin/
rm alb
rm alb.o

echo "The ALB interpreter is now ready to use in version 0.0.2. Type \"alb fileName\" to run your code."
