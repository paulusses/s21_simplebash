#!/bin/bash
fileflags=$1
filetest=$2
unamestr=$(uname)
test_file=s21_cat
case "$unamestr" in
    darwin*)
    liks_item=leaks -atExit --
    echo -e "\033[32m-----------------OSX\033[0m" ;; 
    Linux*)
    liks_item=valgrind 
    echo -e "\033[32m-----------------your system <LINUX>\033[0m" ;;
    msys*)    echo "WINDOWS" ;;
    *)        echo "unknown: $OSTYPE" ;;
esac

echo -e "\033[32m-----------------leaks <$liks_item>\033[0m\n"
test() {
echo -e "\033[32m-----------------TEST ON OPTIONS\033[0m"
for j in $(cat $fileflags)
do
    echo "s21_cat $j"
    #$liks_item ./s21_cat $j $filetest
    ./s21_cat $j $filetest > s21_cat.txt
    cat $j $filetest > cat.txt
    diff -s s21_cat.txt cat.txt
    rm -rf s21_cat.txt cat.txt
done
echo -e "\033[32m-----------------TEST ON INVALID OPTIONS AND FILE\033[0m"
./s21_cat -w OPA.GDE.TXT
echo -e "\033[32m-----------------TEST ON LEAKS\033[0m"
for u in $(cat $fileflags)
do
    echo ""
    echo "valgrind s21_cat $u"
    $liks_item ./s21_cat $u $filetest
done
echo -e "\033[32m-----------------TESTING COMPLETED\033[0m\n"
}
test
