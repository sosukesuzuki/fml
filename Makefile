# ====================================================================
# Variables 
# ====================================================================

CC := gcc
CFLAGS := -Wall -Wextra
DEBUG_CFLAGS := $(CFLAGS) -g
LLDB := lldb

CLANG_FORMAT := clang-format
FORMAT_FILES := $(wildcard *.c) $(wildcard *.h)

# ====================================================================
# Files
# ====================================================================

MAIN_SRC_FILES := fml.c fml_parser.c
PARSER_TESTS_SRC_FILES := fml_parser_tests.c fml_parser.c
INSTRUCTIONS_TESTS_SRC_FILES := fml_instructions_tests.c fml_instructions.c
COMPILER_TESTS_SRC_FILES := fml_compiler_tests.c fml_compiler.c fml_parser.c fml_instructions.c
VM_STACK_TESTS_FILES := fml_vm_stack_tests.c fml_vm_stack.c
FML_LIB_TESTS_FILES := fml_lib_tests.c fml_lib.c fml_parser.c fml_compiler.c fml_instructions.c fml_vm_stack.c fml_vm.c

OBJECT_FILES = $(MAIN_SRC_FILES:.c=.o)
DEBUG_OBJECT_FILES = $(MAIN_SRC_FILES:.c=_debug.o)
PARSER_TESTS_OBJECT_FILES = $(PARSER_TESTS_SRC_FILES:.c=.o)
INSTRUCTIONS_TESTS_OBJECT_FILES = $(INSTRUCTIONS_TESTS_SRC_FILES:.c=.o)
COMPILER_TESTS_OBJECT_FILES = $(COMPILER_TESTS_SRC_FILES:.c=.o)
VM_STACK_TESTS_OBJECT_FILES = $(VM_STACK_TESTS_FILES:.c=.o)
FML_LIB_TESTS_OBJECT_FILES = $(FML_LIB_TESTS_FILES:.c=.o)
FML_LIB_TESTS_DEBUG_OBJECT_FILES = $(FML_LIB_TESTS_FILES:.c=_debug.o)

MAIN_EXECUTABLE_FILE := fml
DEBUG_EXECUTABLE_FILE := fml_debug
PARSER_TESTS_EXECUTABLE_FILE := fml_parser_tests
INSTRUCTIONS_TESTS_EXECUTABLE_FILE := fml_instructions_tests
COMPILER_TESTS_EXECUTABLE_FILE := fml_compiler_tests
VM_STACK_TESTS_EXECUTABLE_FILE := fml_vm_stack_tests
FML_LIB_TESTS_EXECUTABLE_FILE := fml_lib_tests
FML_LIB_TESTS_DEBUG_EXECUTABLE_FILE := fml_lib_tests_debug

.PHONY: format clean run-fml fml fml_debug run-parser-tests run-instructions-tests run-compiler-tests run-vm-stack-tests run-fml-lib-tests run-fml-lib-tests-debug

# ====================================================================
# Build targets
# ====================================================================

fml: $(OBJECT_FILES)
	$(CC) $(CFLAGS) -o $(MAIN_EXECUTABLE_FILE) $^ -lm

fml_debug: $(DEBUG_OBJECT_FILES)
	$(CC) $(DEBUG_CFLAGS) -o $(DEBUG_EXECUTABLE_FILE) $^ -lm

fml_parser_tests: $(PARSER_TESTS_OBJECT_FILES)
	$(CC) $(CFLAGS) -o $(PARSER_TESTS_EXECUTABLE_FILE) $^ -lm

fml_instructions_tests: $(INSTRUCTIONS_TESTS_OBJECT_FILES)
	$(CC) $(CFLAGS) -o $(INSTRUCTIONS_TESTS_EXECUTABLE_FILE) $^ -lm

fml_compiler_tests: $(COMPILER_TESTS_OBJECT_FILES)
	$(CC) $(CFLAGS) -o $(COMPILER_TESTS_EXECUTABLE_FILE) $^ -lm

fml_vm_stack_tests: $(VM_STACK_TESTS_OBJECT_FILES)
	$(CC) $(CFLAGS) -o $(VM_STACK_TESTS_EXECUTABLE_FILE) $^ -lm

fml_lib_tests: $(FML_LIB_TESTS_OBJECT_FILES)
	$(CC) $(CFLAGS) -o $(FML_LIB_TESTS_EXECUTABLE_FILE) $^ -lm

fml_lib_tests_debug: $(FML_LIB_TESTS_DEBUG_OBJECT_FILES)
	$(CC) $(DEBUG_CFLAGS) -o $(FML_LIB_TESTS_DEBUG_EXECUTABLE_FILE) $^ -lm

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

%_debug.o: %.c
	$(CC) $(DEBUG_CFLAGS) -c -o $@ $<

# ====================================================================
# Run tests
# ====================================================================

run-parser-tests: fml_parser_tests
	./$(PARSER_TESTS_EXECUTABLE_FILE)

run-instructions-tests: fml_instructions_tests
	./$(INSTRUCTIONS_TESTS_EXECUTABLE_FILE)

run-compiler-tests: fml_compiler_tests
	./$(COMPILER_TESTS_EXECUTABLE_FILE)

run-vm-stack-tests: fml_vm_stack_tests
	./$(VM_STACK_TESTS_EXECUTABLE_FILE)

run-fml-lib-tests: fml_lib_tests
	./$(FML_LIB_TESTS_EXECUTABLE_FILE)

run-all-tests: run-parser-tests run-instructions-tests run-compiler-tests run-vm-stack-tests run-fml-lib-tests

run-fml-lib-tests-debug: fml_lib_tests_debug
	$(LLDB) $(FML_LIB_TESTS_DEBUG_EXECUTABLE_FILE)

# ====================================================================
# Development utils
# ====================================================================

format:
	$(CLANG_FORMAT) -i $(FORMAT_FILES)

clean:
	rm -f $(MAIN_EXECUTABLE_FILE) $(DEBUG_EXECUTABLE_FILE) $(OBJECT_FILES) \
	$(DEBUG_OBJECT_FILES) $(PARSER_TESTS_EXECUTABLE_FILE) \
	$(PARSER_TESTS_OBJECT_FILES) $(INSTRUCTIONS_TESTS_EXECUTABLE_FILE) \
	$(INSTRUCTIONS_TESTS_OBJECT_FILES) $(COMPILER_TESTS_EXECUTABLE_FILE) \
	$(COMPILER_TESTS_OBJECT_FILES) $(VM_STACK_TESTS_EXECUTABLE_FILE) \
	$(VM_STACK_OBJECT_FILES) $(FML_LIB_TESTS_EXECUTABLE_FILE) \
	$(FML_LIB_OBJECT_FILES) $(FML_LIB_TESTS_DEBUG_EXECUTABLE_FILE) \
	$(FML_LIB_TESTS_DEBUG_OBJECT_FILES) $(FML_LIB_TESTS_OBJECT_FILES) \
	$(VM_STACK_TESTS_OBJECT_FILES)
