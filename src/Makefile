CC= g++ 
SRC= graph/graph.cc graph/ants.cc graph/graphAlgorithms.cc libs/matrix/s21_matrix_oop.cc libs/matrix/supf.cc tests/*.cc
CFLAGS= -Wall -Werror -Wextra
STANDART= -std=c++17
TESTFLAGS=-lgtest
ASAN = -fsanitize=address
TESTFILES= tests/*.cc

all: build

main: clean
	g++ -Wall -Werror -Wextra -lm -lstdc++ -std=c++17 graph/*.cc libs/matrix/s21_matrix_oop.cc libs/matrix/supf.cc && ./a.out

test_graph: clean
	g++ -Wall -Werror -Wextra -lm -lstdc++ -std=c++17 $(ASAN) $(SRC) -o test.out $(TESTFLAGS) && ./test.out

s21_maze.a:
	$(CC) $(CFLAGS) $(STANDART) $(TESTFILES) -c
	ar -rcs s21_containers.a *.o
	rm -rf *.o

test: clean s21_containers.a
	$(CC) $(CFLAGS) $(STANDART) $(TESTFILES) s21_containers.a -o test $(TESTFLAGS)
	# $(CC) $(CFLAGS) $(STANDART) $(TESTFILES) -o test $(TESTFLAGS)
	./test

build: clean
	$(CC) $(CFLAGS) $(STANDART) s21_maze.cc 

clean:
	rm -rf *.out *.o s21_containers.a *.gcda *.gcno *.info *.dot tests/*.dot
	rm -rf report	
