CC = g++
CFLAGS = -std=c++20 -Wall -pedantic
#SOURCES = main.cpp
SOURCES = main.cpp
CLASS = msd.h

ifeq ($(OS), Windows_NT)
	RM = del
	TARGET = main.exe
else
	RM = rm
	TARGET = main
endif

all:
	$(CC) $(CFLAGS) $(SOURCES) $(CLASS) -o $(TARGET)

clean:
	echo $(OS)
	$(RM) $(TARGET)

run: all
#	.\$(TARGET) | python .\main.py
	.\$(TARGET)