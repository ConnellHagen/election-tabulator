CC = g++
CFLAGS = -Wall -std=c++23
SRC_DIR := src
OBJ_DIR := bin
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC_FILES))
INCLUDE = -Isrc/include
VPATH = src

election: $(OBJ_FILES)
	$(CC) $(CFLAGS) -o election $(OBJ_FILES)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

.PHONY:
clean-logs:
	rm audit_*

.PHONY:
clean:
	rm -rf bin/*
	rm -rf election
	rm -rf documentation/html
	rm -rf documentation/latex
	rm -rf build
	make clean-logs

.PHONY:
run:
	mkdir -p bin
	make && ./election

.PHONY:
test:
	mkdir -p bin
	make
	cmake -S . -B build
	cmake --build build
	cd build && ctest --output-on-failure

.PHONY:
docs:
	doxygen documentation/Doxyfile