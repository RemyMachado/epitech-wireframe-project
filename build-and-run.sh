#!/bin/bash

rm a.out
gcc -Wall -Wextra src/*.c -lcsfml-graphics -lcsfml-window
./a.out