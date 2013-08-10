#!/bin/bash

printf "***************************************************************\n"
printf "RUN + COMPILE SCRIPT HEADER ***********************************\n"

#build it
gcc absolute_this.c -lm -o abs_this

#run it
./abs_this

