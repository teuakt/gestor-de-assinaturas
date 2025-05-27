CXX = g++
CXXFLAGS = -std=c++17 -Wall -g
INCLUDES = -Iinclude

OBJ = build/gestor.o build/assinatura.o build/lembrete.o build/usuario.o build/main.o
TARGET = gestor

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(TARGET)

build/%.o: src/%.cpp | build
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

build/main.o: main.cpp | build
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c main.cpp -o build/main.o

build:
	mkdir -p build

clean:
	rm -rf build $(TARGET)

run: all
	./$(TARGET)

