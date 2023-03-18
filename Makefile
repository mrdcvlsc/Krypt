########################## DOCKER ##########################

CXX=g++
FLAGS=-Wall -Wextra 
OS := $(shell uname)

ifeq ($(OS), Linux)
FLAGS+= -fsanitize=address
endif

########################## CLASSIC MAKEFILE ##########################

bench:
	@echo "compiling benchmark : START"
	@$(CXX) tests/benchmark.cpp -o bin/benchmark.out -O3
	@$(CXX) tests/benchmark.cpp -o bin/benchmark-aesni.out -DUSE_AESNI -maes -O3
	@echo "compiling benchmark : DONE"

	@echo "# Benchmark" > benchmark-$(CXX).md
	@echo "" >> benchmark-$(CXX).md
	@echo "Compiler : $(CXX)" >> benchmark-$(CXX).md
	@echo "running benchmark : START"

	@echo "" >> benchmark-$(CXX).md
	@echo "## Pure C++" >> benchmark-$(CXX).md
	@echo "" >> benchmark-$(CXX).md
	@echo "| Block Cipher | Mode | MB | Seconds | Speed | Result |" >> benchmark-$(CXX).md
	@echo "| ------------ | ---- | -- | ------- | ----- | ------ |" >> benchmark-$(CXX).md
	@./bin/benchmark.out >> benchmark-$(CXX).md
	
	@echo "" >> benchmark-$(CXX).md
	@echo "## AES-NI" >> benchmark-$(CXX).md
	@echo "" >> benchmark-$(CXX).md
	@echo "| Block Cipher | Mode | MB | Seconds | Speed | Result |" >> benchmark-$(CXX).md
	@echo "| ------------ | ---- | -- | ------- | ----- | ------ |" >> benchmark-$(CXX).md
	@./bin/benchmark-aesni.out >> benchmark-$(CXX).md
	@echo "running benchmark : DONE"

compile_all: clean compile_test compile_debug compile_profile compile_release

compile_test:
	$(CXX) -std=c++11 -g ./tests/moves.cpp -D CLASSIC_MAKE -o bin/moves.out $(FLAGS)
	$(CXX) -std=c++11 -g ./tests/tests.cpp -D CLASSIC_MAKE -o bin/test.out $(FLAGS)
	$(CXX) -std=c++11 -g ./tests/moves.cpp -D CLASSIC_MAKE -DUSE_AESNI -maes -o bin/moves_aesni.out $(FLAGS)
	$(CXX) -std=c++11 -g ./tests/tests.cpp -D CLASSIC_MAKE -DUSE_AESNI -maes -o bin/test_aesni.out $(FLAGS)

compile_debug:
	$(CXX) -g ./dev/main.cpp -o bin/debug.out

compile_profile:
	$(CXX) -pg ./dev/main.cpp -o bin/profile.out

compile_release:
	$(CXX) -O2 ./dev/main.cpp -o bin/release.out

run_test:
	./bin/moves.out
	./bin/test.out
	./bin/moves_aesni.out
	./bin/test_aesni.out

run_debug:
	./bin/debug.out

run_profile:
	./bin/profile.out

run_release:
	./bin/release.out

run_clean:
	rm -rf bin
	mkdir bin -p
