#!/bin/bash
valgrind -q ../main -i ../examples/silabas.txt -o temp
valgrind -q ../main -r -s -i ../examples/silabas.txt -o dump 2> temp
valgrind -q ../main -c -r -i ../examples/silabas.txt 2> temp > dump
valgrind -q ../main -c -i ../examples/silabas.txt > temp
valgrind -q ../main -r -i ../examples/silabas.txt -o temp
valgrind -q ../main -s -i ../examples/silabas.txt > temp

valgrind -q ../main -i ../examples/abc.txt -o temp
valgrind -q ../main -r -s -i ../examples/abc.txt -o dump 2> temp
valgrind -q ../main -c -r -i ../examples/abc.txt 2> temp > dump
valgrind -q ../main -c -i ../examples/abc.txt > temp
valgrind -q ../main -r -i ../examples/abc.txt -o temp
valgrind -q ../main -s -i ../examples/abc.txt > temp

valgrind -q ../main -i ../examples/test.txt -o temp
valgrind -q ../main -r -s -i ../examples/test.txt -o dump 2> temp
valgrind -q ../main -c -r -i ../examples/test.txt 2> temp > dump
valgrind -q ../main -c -i ../examples/test.txt > temp
valgrind -q ../main -r -i ../examples/test.txt -o temp
valgrind -q ../main -s -i ../examples/test.txt > temp

rm dump
rm temp
