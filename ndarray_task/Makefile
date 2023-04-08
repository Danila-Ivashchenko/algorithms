CC = g++
CFLAGS = -std=c++20 -Wall -pedantic
#SOURCES = main.cpp
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
	$(CC) $(CFLAGS) $(CLASS) -o $(TARGET) $(SOURCES) 

clean:
	echo $(OS)
	$(RM) $(TARGET)

run: all
#	.\$(TARGET) | python .\main.py
	$(SLASH)$(TARGET)