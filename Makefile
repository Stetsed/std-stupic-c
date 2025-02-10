
.PHONY: debug release debug-rust release-rust

CCOMPILER := clang
DIRS := $(shell find src -type d)
CORRECT_DIRS := $(addprefix -I,$(DIRS))

debug: 
	@echo "Compiling the program with debug parameters without rust"
	$(CCOMPILER) $(CORRECT_DIRS) -x c -g main.c -o main.o 

release: 
	@echo "Compiling the program with release parameters without rust"
	$(CCOMPILER) -x c $(CORRECT_DIRS) -O3 -Wl,--gc-sections main.c -o main.o

debug-rust: 
	@echo "Compiling the program with debug parameters"
	cargo build --manifest-path=stupid-bindgen/Cargo.toml
	$(CCOMPILER) $(CORRECT_DIRS) -x c -g main.c stupid-bindgen/target/debug/libstupid_bindgen.a -o main.o 

release-rust: 
	@echo "Compiling the program with release parameters"
	cargo build --manifest-path=stupid-bindgen/Cargo.toml --release
	$(CCOMPILER) -x c $(CORRECT_DIRS) -O3 -Wl,--gc-sections main.c stupid-bindgen/target/debug/libstupid_bindgen.a -o main.o


