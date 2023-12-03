MAIN_SRC_FILES := fml.c fml_parser.c
OBJECT_FILES = $(MAIN_SRC_FILES:.c=.o)
MAIN_EXECUTABLE_FILE := fml

CC := gcc
CFLAGS := -Wall -Wextra

CLANG_FORMAT := clang-format
FORMAT_FILES := $(wildcard *.c) $(wildcard *.h)

.PHONY: format clean run-fml

$(MAIN_EXECUTABLE_FILE): $(OBJECT_FILES)
	$(CC) $(CFLAGS) -o $@ $^ -lm

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

format:
	$(CLANG_FORMAT) -i $(FORMAT_FILES)
