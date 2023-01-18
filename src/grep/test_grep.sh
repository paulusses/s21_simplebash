#!/bin/bash

for i in i v c l n h e #ie ve ce le ne he vc vl vn vh ve cn ivcnhe
do
    echo "<---TESTING WITH FLAG '$i'--->"
    ./s21_grep -$i include s21_grep.c > s21_grep.txt
    grep -$i include s21_grep.c > grep.txt
    diff -s s21_grep.txt grep.txt
done

echo "<---TESTING WITHOUT FLAG--->"
    ./s21_grep [A-Z] s21_grep.c > s21_grep.txt
    grep [A-Z] s21_grep.c > grep.txt
    diff -s s21_grep.txt grep.txt

echo "<---TESTING WITH FLAG 'f'--->"
   ./s21_grep -f reg.txt s21_grep.c > s21_grep.txt
   grep -f reg.txt s21_grep.c > grep.txt
   diff -s s21_grep.txt grep.txt

echo "<---TESTING WITH FLAG 's'--->"
    ./s21_grep -s regex test.txt > s21_grep.txt
    grep -s regex test.txt > grep.txt
    diff -s s21_grep.txt grep.txt

echo "<---TESTING WITH TWO FILES--->"
    ./s21_grep include reg.txt s21_grep.c > s21_grep.txt
    grep include reg.txt s21_grep.c > grep.txt
    diff -s s21_grep.txt grep.txt

echo "<---TESTING WITH -v s FLAGS--->"
    ./s21_grep -v s s21_grep.c > s21_grep.txt
    grep -v s s21_grep.c > grep.txt
    diff -s s21_grep.txt grep.txt

echo "<---TESTING WITH -c s FLAGS--->"
    ./s21_grep -c s s21_grep.c > s21_grep.txt
    grep -c s s21_grep.c > grep.txt
    diff -s s21_grep.txt grep.txt

echo "<---TESTING WITH -l s FLAGS && THREE FILES--->"
    ./s21_grep -l s reg.txt Makefile s21_grep.c > s21_grep.txt
    grep -l s reg.txt Makefile s21_grep.c > grep.txt
    diff -s s21_grep.txt grep.txt

echo "<---TESTING WITH -n s FLAGS--->"
    ./s21_grep -n s s21_grep.c > s21_grep.txt
    grep -n s s21_grep.c > grep.txt
    diff -s s21_grep.txt grep.txt

echo "<---TESTING WITH -h FLAG && TWO FILES--->"
    ./s21_grep -h include reg.txt s21_grep.c > s21_grep.txt
    grep -h include reg.txt s21_grep.c > grep.txt
    diff -s s21_grep.txt grep.txt

rm -rf s21_grep.txt grep.txt