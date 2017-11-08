test: run-tests
	./run-tests

run-tests: tests-main.cpp main.cpp DualLookup.h
	clang++ -std=c++11 tests-main.cpp main.cpp -o run-tests
