#!/bin/bash

rm -rf *.o
rm -rf main
g++ -o setting.o -c setting.cpp -I include/
g++ -o func.o -c func.cpp -I include/
g++ -o Testfunc.o -c Testfunc.cpp -I include/
g++ -o TestALL.o -c TestALL.cpp -I include/
g++ -o main *.o -I include/ -L lib/ -lgtest -lgmock -lpthread

