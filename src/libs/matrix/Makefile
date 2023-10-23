C++ 	 = *.cc
FLAGS 	 = gcc -g -Wall -Werror -Wextra 
DOPFLAGS = -lm -lstdc++ -std=c++17
TESTFLAGS= -lgtest -pthread
TESTRUNS = --gtest_repeat=24 --gtest_break_on_failure

s21_matrix_oop.a:
	$(FLAGS) $(C++) $(DOPFLAGS) -c
	ar -rcs s21_matrix_oop.a *.o
	rm -rf *.o

test: clean s21_matrix_oop.a
	$(FLAGS) $(C++) *.a -o test.out $(DOPFLAGS) $(TESTFLAGS) && ./test.out $(TESTRUNS)

test_graph: clean
	g++ -Wall -Werror -Wextra -lm -lstdc++ -std=c++17 $(SRC) -o test.out $(TESTFLAGS) && ./test.out
	
lint:
	clang-format -i -style=Google *.cc *.hpp
	clang-format -n -style=Google *.cc *.hpp

clean:
	rm -rf *.out *.dSYM *.o *.a *.gcno
