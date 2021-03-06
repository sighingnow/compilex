## Makefile for libparsec.

MAKE 								:= make

CXX									:= g++
CXXFLAGS							:= -Wall -Wextra -std=c++11 $(CXX_FLAGS_$(ARCH))
LDFLAGS 							:= -O

## add -Wa, -mbig-obj option to mingw-w64.
SYS									:= $(shell $(CXX) -dumpmachine)
ifeq ($(CXX), g++)
ifneq (, $(findstring mingw, $(SYS)))
ifneq (, $(findstring x86_64, $(SYS)))
CXXFLAGS 							+= -Wa,-mbig-obj
endif
endif
endif

LIBGTEST_DIR 						:= ./gtest
LIBPARSEC_DIR						:= ./libparsec
GTEST_LDFLAGS						:=  -L $(LIBGTEST_DIR) -lgtest_main -lgtest

INCLUDE								:= -I .
INCLUDE 							+= -I $(LIBGTEST_DIR)/include
INCLUDE 							+= -I $(LIBPARSEC_DIR)/

DEBUG 								:= 0
ifeq ($(DEBUG), 1)
	CXXFLAGS 						+= -O0 -ggdb -DDEBUG -DTRACE
else
	CXXFLAGS						+= -O2 -DNDEBUG
endif

PATCH 								:= 0
ifeq ($(PATCH), 1)
	CXXFLAGS						+= -DENABLE_PATCH
endif

UTILS								:= pl0_parser.o \
									pl0_ast.o \
									pl0_tac_gen.o \
									pl0_opt.o \
									pl0_allocator.o \
									pl0_x86.o

## prevent make deleting the intermedia object file.
.SECONDARY: $(UTILS)

## default target.
all: dist

googletest: $(LIBGTEST_DIR)
	make --dir $(LIBGTEST_DIR) CXX=$(CXX)

test: googletest test test_pl0_parser.out
	./test_pl0_parser.out
.PHONY: test

dist: pl0c.out

pl0c.out: $(UTILS) pl0c.o
	@$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@

%.out: $(UTILS) %.o
	@$(CXX) $(CXXFLAGS) $(LDFLAGS) $(GTEST_LDFLAGS) $^ -o $@

%.o: %.cpp
	@$(CXX) $(CXXFLAGS) $(INCLUDE) -c $<

clean:
	@rm -f *.o *.out
	@rm -f *.obj *.exec
.PHONY: clean

%.asm: %.pas
	@pl0c.out $< > $@

%.obj: %.asm
	@nasm $< -f win32 -o $@

%.exec: pl0_cases/%.obj
	@gcc $< -o $@
	@./$@
	@rm -f $@

ht_cases		:= test_null_stmt.exec \
				test_for1.exec \
				test_for2.exec \
				test_recursive.exec \
				test_sum.exec \
				test_fib1.exec \
				test_fib2.exec \
				test_mul_div.exec \
				test_ref1.exec \
				test_ref2.exec \
				test_ref3.exec \
				test_array.exec \
				test_case.exec \
				test_swap.exec \
				test_io_char.exec \
				test_array_e_ref.exec \
				test_imm.exec \
				test_div.exec \
				test_gcd.exec \

luotg_cases		:= luotg_test_1.exec

romise_cases	:= romise_test_1.exec \
				romise_test_2.exec \

allcases		:= $(ht_cases) $(luotg_cases) $(romise_cases)

test-pas: dist $(allcases)

.SECONDARY: a.asm

compile: dist
	pl0c.out pl0_cases/simple.pas > a.asm
	@make asm_gcc

asm_gcc: a.asm
	nasm -f win32 a.asm -o a.obj
	gcc a.obj -o a.exec
	./a.exec

asm_vclink: a.asm
	nasm -f win32 a.asm -o a.obj
	link a.obj msvcrt.lib
	./a.exe



