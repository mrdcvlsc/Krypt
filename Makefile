OS := $(shell uname)

CXX=g++
CXX_STANDARD=-std=c++17

########################## link ##########################

LINK=dynamic

ifeq ($(LINK), dynamic)
LINKER=
else ifeq ($(LINK), static)
LINKER=-static
endif

########################## sanitizer ##########################

ifeq ($(CXX), clang++)
ADDRESS_SANITIZER=-fsanitize=address
THREADS_SANITIZER=-fsanitize=thread
else
ADDRESS_SANITIZER=
THREADS_SANITIZER=
endif

########################## version ##########################

VERSION=portable

ifeq ($(VERSION), portable)
COMPILATION_MSG="compiling portable version"
DFLAGS=
else ifeq ($(VERSION), aesni)
COMPILATION_MSG="compiling AES-NI version"
DFLAGS=-DUSE_AESNI -maes
else ifeq ($(VERSION), neon)
COMPILATION_MSG="compiling AES aarch64 neon version"
DFLAGS=-DUSE_ARM_AES -march=armv8-a+crypto
endif

########################## type ##########################

TYPE=release

ifeq ($(TYPE), release)
CXX_FLAGS=-O3 -Wall -Wextra
else ifeq ($(TYPE), debug)
CXX_FLAGS=-O2 -Wall -Wextra $(ADDRESS_SANITIZER)
endif

########################## CLASSIC MAKEFILE ##########################

default:
	@echo "Makefile variables and possible values"
	@echo "The the first element are always the default value"
	@echo "CXX     : g++, clang++"
	@echo "TYPE    : release, debug"
	@echo "VERSION : portable, aesni, neon"
	@echo "LINK    : dynamic, static"
	@echo ""
	@echo "Makefile recipes"

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

compile:
	$(CXX) $(LINKER) $(CXX_STANDARD) tests/byte_array.cpp -o bin/byte_array.out $(DFLAGS) $(ADDRESS_SANITIZER) $(CXX_FLAGS)
	$(CXX) $(LINKER) $(CXX_STANDARD) tests/testvectors.cpp -o bin/test.out $(DFLAGS) $(ADDRESS_SANITIZER) $(CXX_FLAGS)

test_portable:
	@echo "Compiling portable version"
	$(MAKE) compile TYPE=debug VERSION=portable
	@echo "Running portable test"
	$(MAKE) run_test

test_aesni:
	@echo "Compiling aesni version"
	$(MAKE) compile TYPE=debug VERSION=aesni
	@echo "Running aesni test"
	$(MAKE) run_test

test_neon:
	@echo "Compiling neon version"
	$(MAKE) compile TYPE=debug VERSION=neon
	@echo "Running neon test"
	$(MAKE) run_test

run_test:
	./bin/test.out
	./bin/byte_array.out

run_debug:
	./bin/debug.out

run_profile:
	./bin/profile.out

run_release:
	./bin/release.out

run_clean:
	rm -rf bin
	mkdir bin -p

style:
	@clang-format -i -style=file *.cpp *.hpp tests/*.hpp tests/*.cpp src/*.hpp src/*.cpp src/mode/*.hpp src/mode/*.cpp src/padding/*.hpp src/padding/*.cpp src/blockcipher/AES/*.hpp src/blockcipher/AES/*.cpp