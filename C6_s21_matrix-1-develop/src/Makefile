CC = gcc
FLAGS = -std=c11 -Wall -Werror -Wextra
FLAG_COV = --coverage
LIBS = -lcheck
TEST_LIBS = -lcheck -lm -lpthread
VALGRIND_FLAGS=--trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all --verbose

all: gcov_report

clang:
	clang-format -i --style=google *.c *.h
	cp ../materials/linters/.clang-format ../src/.clang-format
	clang-format -style=Google -n *.c *.h
	rm .clang-format

s21_matrix.a:
	$(CC) $(FLAGS) -c s21_matrix_helper.c s21_create_matrix.c s21_eq_matrix.c s21_mult_matrix.c s21_remove_matrix.c s21_sum_matrix.c s21_calc_complements.c s21_determinant.c s21_inverse_matrix.c s21_mult_number.c s21_sub_matrix.c s21_transpose.c
	ar rc s21_matrix.a *.o
	ranlib s21_matrix.a

test: s21_matrix.a
	$(CC) $(FLAGS) -c s21_matrix_test.c -o s21_matrix_test.o
	$(CC) s21_matrix_test.o s21_matrix.a $(TEST_LIBS) -o s21_matrix
	./s21_matrix

install lcov:
	curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | zsh
	brew install lcov

leak: s21_matrix.a
	$(CC) $(FLAGS) -c s21_matrix_test.c -o s21_matrix_test.o
	$(CC) s21_matrix_test.o s21_matrix.a $(TEST_LIBS) -o s21_matrix
	CK_FORK=no leaks -quiet -atExit -- ./s21_matrix

clean:
	rm -rf s21_matrix
	rm -rf *.o
	rm -rf *.a
	rm -rf *.gcno
	rm -rf *.gcda
	rm -rf *.gcov
	rm -rf *.info
	rm -rf *.html
	rm -rf *.css
	rm -rf test
	rm -rf gcov_test
	rm -rf ./report
	rm -rf *.txt
	rm -rf *.log

rebuild: clean all

main: clean
	gcc s21_matrix_helper.c s21_create_matrix.c s21_eq_matrix.c s21_mult_matrix.c s21_remove_matrix.c s21_sum_matrix.c s21_calc_complements.c s21_determinant.c s21_inverse_matrix.c s21_mult_number.c s21_sub_matrix.c s21_transpose.c main.c -o s21_matrix $(TEST_LIBS)
	./s21_matrix

valgrind: s21_matrix.a
	$(CC) s21_matrix_test.c s21_matrix.a -o test $(LIBS) $(TEST_LIBS)
	valgrind --log-file="s21_matrix.log" $(VALGRIND_FLAGS) ./test
	grep ERROR s21_matrix.log > error.txt
	grep -v "ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)" error.txt > __error.txt

gcov_report: test
	$(CC) $(FLAGS) --coverage s21_matrix_test.c s21_matrix_helper.c s21_create_matrix.c s21_eq_matrix.c s21_mult_matrix.c s21_remove_matrix.c s21_sum_matrix.c s21_calc_complements.c s21_determinant.c s21_inverse_matrix.c s21_mult_number.c s21_sub_matrix.c s21_transpose.c s21_matrix.a $(TEST_LIBS) -o gcov_test
	chmod +x *
	./gcov_test
	gcov s21_*.gcda
	lcov -t "gcovReport" -o gcov_test.info -c -d .
	genhtml -o report gcov_test.info
	open report/index.html
