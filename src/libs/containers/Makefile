CC= g++ 
CFLAGS= -Wall -Wextra -Werror
STANDART= -std=c++17
TESTFLAGS=-lgtest
TESTFILES= tests/*.cc
#set/test.cc

all: gcov_report

s21_containers.a:
	$(CC) $(CFLAGS) $(STANDART) $(TESTFILES) -c
	ar -rcs s21_containers.a *.o
	rm -rf *.o

test: clean s21_containers.a
	$(CC) $(CFLAGS) $(STANDART) $(TESTFILES) s21_containers.a -o test $(TESTFLAGS)
	# $(CC) $(CFLAGS) $(STANDART) $(TESTFILES) -o test $(TESTFLAGS)
	./test

gcov_report: clean
	$(CC) $(CFLAGS) --coverage $(STANDART) $(TESTFILES) -o test $(TESTFLAGS)
	./test
	lcov -t "test" -o test.info -c -d . --no-external
	genhtml -o report test.info
	open report/index.html

clean:
	rm -rf *.out *.o s21_containers.a *.gcda *.gcno *.info test main
	rm -rf report	

linters: 
	cp ../materials/linters/.clang-format .

	clang-format -n s21_containers.hpp

	clang-format -n tests/*.cc
	clang-format -n tests/*.hpp
	
	clang-format -n map/*.hpp
	clang-format -n list/*.hpp

	clang-format -n abstract/*.h
	clang-format -n abstract/*.tpp

	clang-format -n array/*.h
	clang-format -n array/*.tpp

	clang-format -n set/*.hpp
	
	clang-format -n multiset/*.hpp

	clang-format -n queue/*.hpp

	clang-format -n stack/*.h

	clang-format -n vector/*.h
	clang-format -n vector/*.tpp

	rm .clang-format

valgring:
	valgrind  --track-origins=yes --leak-check=full --show-leak-kinds=all -v ./test

	
