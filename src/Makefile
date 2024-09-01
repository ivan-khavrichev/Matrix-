CC = g++
STD = -std=c++17
WFLAGS = -Wall -Werror -Wextra
TEST_FLAGS = -lgtest

S21_LIB = s21_matrix_oop.a
СС_FILES = $(wildcard s21_*.cc)
OBJ_FILES = $(patsubst %.cc, %.o, $(СС_FILES))

TEST_CC_FILES = $(wildcard tests.cc)
TEST_OBJ_FILES = $(patsubst %.cc, %.o, $(TEST_CC_FILES))

TRASH = $(wildcard *.o *.a *.gc* *.out tests test.info report)

all: $(S21_LIB) test

clean:
	rm -rf $(TRASH)

rebuild: clean all

$(S21_LIB):
	$(CC) $(STD) $(WFLAGS) -g -c $(СС_FILES)
	ar rc $(S21_LIB) $(OBJ_FILES)
	ranlib $(S21_LIB)

test: $(S21_LIB)
	$(CC) $(STD) $(WFLAGS) $(TEST_CC_FILES) $(S21_LIB) $(TEST_FLAGS) -o tests
	./tests

gcov_report: $(S21_LIB)
	$(CC) $(STD) --coverage $(СС_FILES) $(S21_LIB) $(TEST_CC_FILES) $(TEST_FLAGS) -o tests
	./tests
	lcov -t "test" --no-external -o test.info -c -d .
	genhtml -o report test.info
	open report/index.html

check_style:
	cp ../materials/linters/.clang-format ../src
	clang-format -n -style=google *.cc *.h
	rm -rf .clang-format

correct_style:
	cp ../materials/linters/.clang-format ../src
	clang-format -i -style=google *.cc *.h
	rm -rf .clang-format

check_leaks:
	leaks -atExit -- ./tests
