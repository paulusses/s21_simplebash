CC = gcc
FLAGS = -Wall -Werror -Wextra -std=c11
CLEAN = rm -rf
sis_uname := $(shell uname -s)

#ALL INFO
BUILD_NAME = s21_cat

#DIRECTORY -> BUILD, SRC, TEST
D_BUILD = .
D_TEST = .
D_SRC = .

# ALL -> SRC HEADER OBJECTS
SOURCES = *.c
HEADERS = *.h
OBJECTS = *.o

# TESTS
TEST = test_allsysy.sh
TEST_LOGS = catalog_with_the_test_result
TESTING_FILE_NAME = scanme.text
TEST_FLAGS = flags_for_cat

#	valgrind s21_cat -b scanme.txt
ifeq ($(sis_uname), Linux)
	LEAKS=valgrind $(D_BUILD)/$(BUILD_NAME) $(TEST_FLAGS) $(TESTING_FILE_NAME)
else
	LEAKS=CK_FORK=no leaks --atExit -- $(D_BUILD)/$(BUILD_NAME) $(TEST_FLAGS) $(TESTING_FILE_NAME)
endif

all: $(BUILD_NAME) cpplint

$(BUILD_NAME):
	$(CC) $(CFLAGS) $(D_SRC)/$(SOURCES) -o $(D_BUILD)/$(BUILD_NAME)

re: clean all test

test:
	chmod 777 $(D_TEST)/$(TEST)
	mkdir $(TEST_LOGS)
	cp $(D_TEST)/$(TEST) $(TEST_LOGS)
	cp $(D_TEST)/$(TESTING_FILE_NAME) $(TEST_LOGS)
	cp $(D_TEST)/$(TEST_FLAGS) $(TEST_LOGS)
	-$(TEST_LOGS)/$(TEST) $(TEST_LOGS)/$(TEST_FLAGS) $(TEST_LOGS)/$(TESTING_FILE_NAME)

cpplint:
	cp ../../materials/linters/CPPLINT.cfg ./
	python3 ../../materials/linters/cpplint.py --recursive --extensions=c ../src/cat $(SOURCES) $(HEADERS)
	$(CLEAN) CPPLINT.cfg


leaks:
	$(LEAKS)

clean:
	$(CLEAN) $(D_BUILD)/$(BUILD_NAME)
	$(CLEAN) $(TEST_LOGS)
	$(CLEAN) *.a *.out *.o catalog_with_the_test_result