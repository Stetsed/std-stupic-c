
CCOMPILER := clang
DIRS := $(shell find src -type d)
SOURCE_FILES := $(shell find src -name "*.c")
CORRECT_DIRS := $(addprefix -I,$(DIRS))

TEST_DIRS := $(shell find src test -type d)
TEST_SOURCE_FILES := $(shell find src test -name "*.c")
TEST_CORRECT_DIRS := $(addprefix -I, $(TEST_DIRS))

OUTPUT := main.o

TEST_OUTPUT := build/test.out

CCOMPILER_FLAGS := -Wno-unused-value

LANG_ARGS := -x c -std=c99
WARNING_ARGS := -pedantic-errors -Wall -Wextra -Wno-unused-parameter
RELEASE_ARGS := -O3 -Wl,--gc-sections

.PHONY: debug test release

debug: 
	@echo "Compiling the program with debug parameters"
	$(CCOMPILER) $(CCOMPILER_FLAGS) $(CORRECT_DIRS) $(WARNING_ARGS) $(LANG_ARGS) -g main.c $(SOURCE_FILES) -o $(OUTPUT) $(EXTRA_ARGS)

test:
	@echo "Running tests for std-stupid-c with unity"
	mkdir build > /dev/null 2>&1 || true
	$(CCOMPILER) $(CCOMPILER_FLAGS) $(TEST_CORRECT_DIRS) $(WARNING_ARGS) $(LANG_ARGS) -g $(TEST_SOURCE_FILES) -o $(TEST_OUTPUT) $(EXTRA_ARGS)
	$(TEST_OUTPUT)

release: 
	@echo "Compiling the program with release parameters"
	$(CCOMPILER) $(CCOMPILER_FLAGS) $(CORRECT_DIRS) $(WARNING_ARGS) $(LANG_ARGS) $(RELEASE_ARGS) main.c $(SOURCE_FILES) -o $(OUTPUT) $(EXTRA_ARGS)

