CXX = g++
CXXFLAGS = -std=c++17 -Wall -g
INCLUDES = -Iinclude

SRC = gestor.cpp assinatura.cpp lembrete.cpp usuario.cpp

OBJ = $(addprefix build/, gestor.o assinatura.o lembrete.o usuario.o)

MAIN_OBJ = build/main.o

TARGET = gestor

TEST_DIR = tests
TEST_SRCS = $(wildcard $(TEST_DIR)/test_*.cpp)
TEST_EXES = $(patsubst $(TEST_DIR)/%.cpp, build/%,$(TEST_SRCS))

all: $(TARGET)

$(TARGET): $(OBJ) $(MAIN_OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) $(MAIN_OBJ) -o $(TARGET)

build/%.o: src/%.cpp | build
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

build/main.o: main.cpp | build
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c main.cpp -o build/main.o

build:
	mkdir -p build

build/%: tests/%.cpp $(OBJ)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $< $(OBJ) -o $@

test: $(TEST_EXES)
	@for test_exec in $(TEST_EXES); do \
		echo "Running $$test_exec..."; \
		./$$test_exec || exit 1; \
	done

clean:
	rm -rf build $(TARGET)

run: all
	./$(TARGET)
