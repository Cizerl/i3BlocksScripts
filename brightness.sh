#!/bin/bash 

#BRIGHTNESS SKRIPT
#Author: A. Cizerl
#16 June 2022

lightwert=$(light -G)

printf "${lightwert%.*}%%\n"

