#!/bin/sh

g++ main.cpp -o bin/monitor
g++ assembler.cpp -o bin/assembler

cp bin/assembler work/assembler
cp bin/monitor work/monitor