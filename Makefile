CXX = clang++

SRC_DIR = src
LIB_DIR = lib

SRC = $(SRC_DIR)/main.cpp $(LIB_DIR)/init.cpp $(LIB_DIR)/tableau.cpp $(LIB_DIR)/stock.cpp $(LIB_DIR)/fndtion.cpp $(LIB_DIR)/util.cpp

TARGET = game

CXXFLAGS = -std=c++17 -Wall -Wextra -O3 -flto -march=native

INCLUDE = -I/usr/local/include -I$(LIB_DIR)

LIBS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

LIBRARY = -L/usr/local/lib -L$(LIB_DIR)

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) $(INCLUDE) $(LIBRARY) $(LIBS) -o $(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all clean

