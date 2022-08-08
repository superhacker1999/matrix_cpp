.PHONY: all  clean test  s21_matrix_oop.a objects build_lib rebuild clean_obj
CC=gcc
CFLAGS=-Wall -Werror -Wextra -lstdc++

all: test
rebuild: clean all

s21_matrix_oop.a: build_lib clean_obj

build_lib: objects
	@ar rc s21_matrix_oop.a s21_matrix_oop.o
	@ranlib s21_matrix_oop.a

objects:
	@$(CC) $(CFLAGS) -c s21_matrix_oop.cpp

test: clean s21_matrix_oop.a tests.cpp
	@$(CC) $(CFLAGS) -lgtest tests.cpp s21_matrix_oop.a -o test -g
	@./test 

check:
	@cp ../materials/linters/CPPLINT.cfg .
	@python3 ../materials/linters/cpplint.py --extensions=cpp *.cpp *.h
	@rm -rf CPPLINT.cfg

valgrind:
	g++ tests.cpp s21_matrix_oop.cpp -o test -lgtest
	CK_FORK=no valgrind --vgdb=no --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./test

clean_obj:
	@rm -rf *.o

clean:
	@rm -rf *.a ./test CPPLINT.cfg *.gcno *.gcda
	@rm -rf ./test
	@rm -rf CPPLINT.cfg
