CC = g++
CFLAGS = -std=c++20 -Wall -pedantic
SOURCES = main.cpp
CLASS = NDArray.h

ifeq ($(OS), Windows_NT)
	RM = del
	TARGET = main.exe
	SLASH = .\
else
	RM = rm
	TARGET = main
	SLASH = ./
endif

all:
	$(CC) $(CFLAGS) $(SOURCES) $(CLASS) -o $(TARGET)

clean:
	$(RM) $(SLASH)$(TARGET)

run: all
	$(SLASH)$(TARGET)
