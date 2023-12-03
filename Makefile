MAIN_SRC_FILES := fml.c
MAIN_EXECUTABLE_FILE := fml

CC := gcc
CFLAGS := -Wall -Wextra

CLANG_FORMAT := clang-format
FORMAT_FILES := $(wildcard *.c)

.PHONY: format clean run-fml

$(MAIN_EXECUTABLE_FILE)): $(MAIN_SRC_FILES)
	$(CC) $(CFLAGS) $(MAIN_SRC_FILES) -o $(MAIN_EXECUTABLE_FILE) -lm

format:
	$(CLANG_FORMAT) -i $(FORMAT_FILES)
