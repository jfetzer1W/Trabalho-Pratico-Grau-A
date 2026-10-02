CXX = g++
CXXFLAGS = -std=c++17 -Wall
SRCS = $(wildcard *.cpp)
TARGET = jogo

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET) save.txt

.PHONY: all run clean
