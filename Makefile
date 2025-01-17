CC = gcc -g
FLAGS = -Wall -Wextra -Werror -std=c11 
DECIMAL_SOURCE = arithmetic_operations/*.c
TEST_SOURCE = tests/*.c
BITCALLS_SOURCE = bit_calls/*.c
BINARY_SOURCE = bitwise_operations/*.c
SUBSIDIARY_SOURCE = subsidiary_functions/*.c
COMPARISON_SOURCE = comparison_operations/*.c
CONVERTORS_SOURCE = converters/*.c
OTHER_SOURCE = other_functions/*.c

GCOV_FLAGS = -L. --coverage 

all: s21_decimal.a test gcov_report

test: s21_decimal.a
	$(CC) $(FLAGS) $(TEST_SOURCE) s21_decimal.a -o s21_tests -lcheck -lm -lsubunit
	./s21_tests

rebuild: clean all

gcov_report: test
	rm -rf *.g*
	$(CC) $(FLAGS) $(DECIMAL_SOURCE) $(COMPARISON_SOURCE) $(CONVERTORS_SOURCE) $(OTHER_SOURCE) $(SUBSIDIARY_SOURCE) $(TEST_SOURCE) s21_decimal.a -o s21_tests -lcheck ${GCOV_FLAGS} -g
	./s21_tests
	lcov -t s21_tests -o test.info -c -d .
	genhtml -o report test.info
	open ./report/index.html
	rm -rf *.gcda *.gcno *.info s21_tests

s21_decimal.a:
	$(CC) $(FLAGS) -c $(DECIMAL_SOURCE) $(BITCALLS_SOURCE) $(BINARY_SOURCE) $(SUBSIDIARY_SOURCE) $(COMPARISON_SOURCE) $(CONVERTORS_SOURCE) $(OTHER_SOURCE)
	ar rc s21_decimal.a *.o
	ranlib s21_decimal.a

clean: 
	rm -rf s21_tests
	rm -rf  *.o *.a *.out
	rm -rf *.gcda *.gcno *.info
	rm -rf report
	rm -rf s21_tests.dSYM

clang:
	cp ../materials/linters/.clang-format ./
	clang-format -n *.h arithmetic_operations/*.c comparison_operations/*.c converters/*.c other_functions/*.c subsidiary_functions/*.c tests/*.c bit_calls/*.c bitwise_operations/*.c 
	clang-format -i *.h arithmetic_operations/*.c comparison_operations/*.c converters/*.c other_functions/*.c subsidiary_functions/*.c tests/*.c bit_calls/*.c bitwise_operations/*.c 
	rm .clang-format