MAIN_SRC_FILES := fml.c fml_parser.c
OBJECT_FILES = $(MAIN_SRC_FILES:.c=.o)
DEBUG_OBJECT_FILES = $(MAIN_SRC_FILES:.c=_debug.o)
MAIN_EXECUTABLE_FILE := fml
DEBUG_EXECUTABLE_FILE := fml_debug

CC := gcc
CFLAGS := -Wall -Wextra
DEBUG_CFLAGS := $(CFLAGS) -g

CLANG_FORMAT := clang-format
FORMAT_FILES := $(wildcard *.c) $(wildcard *.h)

.PHONY: format clean run-fml fml fml_debug

fml: $(OBJECT_FILES)
	$(CC) $(CFLAGS) -o $(MAIN_EXECUTABLE_FILE) $^ -lm

fml_debug: $(DEBUG_OBJECT_FILES)
	$(CC) $(DEBUG_CFLAGS) -o $(DEBUG_EXECUTABLE_FILE) $^ -lm

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

%_debug.o: %.c
	$(CC) $(DEBUG_CFLAGS) -c -o $@ $<

format:
	$(CLANG_FORMAT) -i $(FORMAT_FILES)

clean:
	rm -f $(MAIN_EXECUTABLE_FILE) $(DEBUG_EXECUTABLE_FILE) $(OBJECT_FILES) $(DEBUG_OBJECT_FILES)
