
CCOMPILER := clang
DIRS := $(shell find src -type d)
SOURCE_FILES := $(shell find src -name "*.c")
CORRECT_DIRS := $(addprefix -I,$(DIRS))

OUTPUT := main.o

CCOMPILER_FLAGS := -Wno-unused-value


debug: 
	@echo "Compiling the program with debug parameters without rust"
	$(CCOMPILER) $(CCOMPILER_FLAGS) $(CORRECT_DIRS) -x c -g main.c $(SOURCE_FILES) -o $(OUTPUT) $(EXTRA_ARGS)

release: 
	@echo "Compiling the program with release parameters without rust"
	$(CCOMPILER) $(CCOMPILER_FLAGS) -x c $(CORRECT_DIRS) -O3 -Wl,--gc-sections main.c $(SOURCE_FILES) -o $(OUTPUT) $(EXTRA_ARGS)

debug-rust: 
	@echo "Compiling the program with debug parameters"
	cargo build --manifest-path=stupid-bindgen/Cargo.toml
	$(CCOMPILER) $(CCOMPILER_FLAGS) $(CORRECT_DIRS) -x c -g main.c $(SOURCE_FILES) stupid-bindgen/target/debug/libstupid_bindgen.a -o main.o 

release-rust: 
	@echo "Compiling the program with release parameters"
	cargo build --manifest-path=stupid-bindgen/Cargo.toml --release
	$(CCOMPILER) $(CCOMPILER_FLAGS) -x c $(CORRECT_DIRS) -O3 -Wl,--gc-sections main.c $(SOURCE_FILES) stupid-bindgen/target/debug/libstupid_bindgen.a -o main.o


