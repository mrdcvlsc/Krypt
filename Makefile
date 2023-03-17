########################## DOCKER ##########################

CXX=g++
FLAGS=-Wall -Wextra 
OS := $(shell uname)

ifeq ($(OS), Linux)
FLAGS+= -fsanitize=address
endif

########################## CLASSIC MAKEFILE ##########################

gh_bench:
	mkdir bin
	$(CXX) tests/benchmark.cpp -lbenchmark -lpthread -o bin/benchmark -O3 -march=native
	bin/benchmark

gh_test:
	mkdir bin
	make compile_test

compile_all: clean compile_test compile_debug compile_profile compile_release

compile_test:
	$(CXX) -std=c++11 -g ./tests/moves.cpp -D CLASSIC_MAKE -o bin/moves $(FLAGS)
	$(CXX) -std=c++11 -g ./tests/tests.cpp -D CLASSIC_MAKE -o bin/test $(FLAGS)
	$(CXX) -std=c++11 -g ./tests/moves.cpp -D CLASSIC_MAKE -DUSE_AESNI -maes -o bin/moves_aesni $(FLAGS)
	$(CXX) -std=c++11 -g ./tests/tests.cpp -D CLASSIC_MAKE -DUSE_AESNI -maes -o bin/test_aesni $(FLAGS)

compile_debug:
	$(CXX) -g ./dev/main.cpp -o bin/debug

compile_profile:
	$(CXX) -pg ./dev/main.cpp -o bin/profile

compile_release:
	$(CXX) -O2 ./dev/main.cpp -o bin/release

run_test:
	bin/moves
	bin/test
	bin/moves_aesni
	bin/test_aesni

run_debug:
	bin/debug

run_profile:
	bin/profile

run_release:
	bin/release

run_clean:
	rm -rf bin
	mkdir bin -p
