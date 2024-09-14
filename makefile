# Variables
BUILD_DIR = build

# All target
all: $(BUILD_DIR) SCAN

# Ensure the build directory exists
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# SCAN target
SCAN: $(BUILD_DIR)/utility.o $(BUILD_DIR)/config.o $(BUILD_DIR)/SymbolTable.o $(BUILD_DIR)/TransitionGraph.o $(BUILD_DIR)/Scanner.o $(BUILD_DIR)/main.o
	g++ -o $(BUILD_DIR)/scan $(BUILD_DIR)/main.o $(BUILD_DIR)/utility.o $(BUILD_DIR)/config.o $(BUILD_DIR)/SymbolTable.o $(BUILD_DIR)/TransitionGraph.o $(BUILD_DIR)/Scanner.o

# Object file compilation rules
$(BUILD_DIR)/main.o: main.cpp
	g++ -c -g main.cpp -o $(BUILD_DIR)/main.o

$(BUILD_DIR)/config.o: config.cpp
	g++ -c -g config.cpp -o $(BUILD_DIR)/config.o

$(BUILD_DIR)/utility.o: utility.cpp
	g++ -c -g utility.cpp -o $(BUILD_DIR)/utility.o

$(BUILD_DIR)/SymbolTable.o: SymbolTable.cpp
	g++ -c -g SymbolTable.cpp -o $(BUILD_DIR)/SymbolTable.o

$(BUILD_DIR)/TransitionGraph.o: TransitionGraph.cpp
	g++ -c -g TransitionGraph.cpp -o $(BUILD_DIR)/TransitionGraph.o

$(BUILD_DIR)/Scanner.o: Scanner.cpp
	g++ -c -g Scanner.cpp -o $(BUILD_DIR)/Scanner.o

# Clean up build files
removal:
	rm -f $(BUILD_DIR)/*.o $(BUILD_DIR)/scan
