########################## DOCKER ##########################

CXX=g++
CXX_STANDARD=-std=c++14
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

	@echo "# Benchmark" > docs/benchmarks/benchmark-$(CXX).md
	@echo "" >> docs/benchmarks/benchmark-$(CXX).md
	@echo "Compiler : $(CXX)" >> docs/benchmarks/benchmark-$(CXX).md
	@echo "running benchmark : START"

	@echo "" >> docs/benchmarks/benchmark-$(CXX).md
	@echo "## Pure C++" >> docs/benchmarks/benchmark-$(CXX).md
	@echo "" >> docs/benchmarks/benchmark-$(CXX).md
	@echo "| Block Cipher | Mode | MB | Seconds | Speed | Result |" >> docs/benchmarks/benchmark-$(CXX).md
	@echo "| ------------ | ---- | -- | ------- | ----- | ------ |" >> docs/benchmarks/benchmark-$(CXX).md
	@./bin/benchmark.out >> docs/benchmarks/benchmark-$(CXX).md
	
	@echo "" >> docs/benchmarks/benchmark-$(CXX).md
	@echo "## AES-NI" >> docs/benchmarks/benchmark-$(CXX).md
	@echo "" >> docs/benchmarks/benchmark-$(CXX).md
	@echo "| Block Cipher | Mode | MB | Seconds | Speed | Result |" >> docs/benchmarks/benchmark-$(CXX).md
	@echo "| ------------ | ---- | -- | ------- | ----- | ------ |" >> docs/benchmarks/benchmark-$(CXX).md
	@./bin/benchmark-aesni.out >> docs/benchmarks/benchmark-$(CXX).md
	@echo "running benchmark : DONE"

compile_all: clean compile_test compile_debug compile_profile compile_release

compile_test:
	$(CXX) $(CXX_STANDARD) -g tests/byte_array.cpp -D CLASSIC_MAKE -o bin/byte_array.out $(FLAGS)
	$(CXX) $(CXX_STANDARD) -g tests/testvectors.cpp -D CLASSIC_MAKE -o bin/test.out $(FLAGS)
	$(CXX) $(CXX_STANDARD) -g tests/byte_array.cpp -D CLASSIC_MAKE -DUSE_AESNI -maes -o bin/byte_array_aesni.out $(FLAGS)
	$(CXX) $(CXX_STANDARD) -g tests/testvectors.cpp -D CLASSIC_MAKE -DUSE_AESNI -maes -o bin/test_aesni.out $(FLAGS)

run_test:
	./bin/byte_array.out
	./bin/test.out
	./bin/byte_array_aesni.out
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
