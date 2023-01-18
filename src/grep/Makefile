CC= gcc -std=c11 -D_GNU_SOURCE
CFLAGS= -Wall -Wextra -Werror

all: s21_grep

s21_grep:
	$(CC) $(CFLAGS) s21_grep.c -o s21_grep

test: s21_grep
	@chmod 777 test_grep.sh
	@./test_grep.sh

clean:
	@rm -rf s21_grep
	@rm -rf *.a *.out *.o

check:
	@cppcheck s21_grep.c
	@cp ../../materials/linters/CPPLINT.cfg CPPLINT.cfg
	@python3 ../../materials/linters/cpplint.py --extensions=c s21_grep.c
	@CK_FORK=no leaks --atExit -- ./s21_grep

rebuild: clean all
	@rm -rf  *.o *.a