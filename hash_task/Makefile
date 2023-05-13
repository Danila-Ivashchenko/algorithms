CC = g++
CFLAGS = -std=c++20 -Wall -pedantic
SOURCES = main.cpp
FUNCTIONS = hash.hpp

ifeq ($(OS), Windows_NT)
	RM = del
	TARGET = main.exe
else
	RM = rm
	TARGET = main
endif

all:
	$(CC) $(CFLAGS) $(FUNCTIONS) -o $(TARGET) $(SOURCES)
clean:
	echo $(OS)
	$(RM) $(TARGET)

run: all
	./$(TARGET)