MAIN_SRC_FILES := fml.c fml_parser.c
PARSER_TESTS_SRC_FILES := fml_parser_tests.c fml_parser.c
INSTRUCTIONS_TESTS_SRC_FILES := fml_instructions_tests.c fml_instructions.c

OBJECT_FILES = $(MAIN_SRC_FILES:.c=.o)
DEBUG_OBJECT_FILES = $(MAIN_SRC_FILES:.c=_debug.o)
PARSER_TESTS_OBJECT_FILES = $(PARSER_TESTS_SRC_FILES:.c=.o)
INSTRUCTIONS_TESTS_OBJECT_FILES = $(INSTRUCTIONS_TESTS_SRC_FILES:.c=.o)

MAIN_EXECUTABLE_FILE := fml
DEBUG_EXECUTABLE_FILE := fml_debug
PARSER_TESTS_EXECUTABLE_FILE := fml_parser_tests
INSTRUCTIONS_TESTS_EXECUTABLE_FILE := fml_instructions_tests

CC := gcc
CFLAGS := -Wall -Wextra
DEBUG_CFLAGS := $(CFLAGS) -g

CLANG_FORMAT := clang-format
FORMAT_FILES := $(wildcard *.c) $(wildcard *.h)

.PHONY: format clean run-fml fml fml_debug run-parser-tests run-instructions-tests

fml: $(OBJECT_FILES)
	$(CC) $(CFLAGS) -o $(MAIN_EXECUTABLE_FILE) $^ -lm

fml_debug: $(DEBUG_OBJECT_FILES)
	$(CC) $(DEBUG_CFLAGS) -o $(DEBUG_EXECUTABLE_FILE) $^ -lm

fml_parser_tests: $(PARSER_TESTS_OBJECT_FILES)
	$(CC) $(CFLAGS) -o $(PARSER_TESTS_EXECUTABLE_FILE) $^ -lm

fml_instructions_tests: $(INSTRUCTIONS_TESTS_OBJECT_FILES)
	$(CC) $(CFLAGS) -o $(INSTRUCTIONS_TESTS_EXECUTABLE_FILE) $^ -lm

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

%_debug.o: %.c
	$(CC) $(DEBUG_CFLAGS) -c -o $@ $<

run-parser-tests: fml_parser_tests
	./$(PARSER_TESTS_EXECUTABLE_FILE)

run-instructions-tests: fml_instructions_tests
	./$(INSTRUCTIONS_TESTS_EXECUTABLE_FILE)

format:
	$(CLANG_FORMAT) -i $(FORMAT_FILES)

clean:
	rm -f $(MAIN_EXECUTABLE_FILE) $(DEBUG_EXECUTABLE_FILE) $(OBJECT_FILES) $(DEBUG_OBJECT_FILES) $(PARSER_TESTS_EXECUTABLE_FILE) $(PARSER_TESTS_OBJECT_FILES) $(INSTRUCTIONS_TESTS_EXECUTABLE_FILE) $(INSTRUCTIONS_TESTS_OBJECT_FILES)
