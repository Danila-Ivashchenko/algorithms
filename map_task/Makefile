CC = g++
PY = python
CFLAGS = -std=c++11 -Wall -pedantic
SOURCE_CPP = main.cpp
SOURCE_PY = map.py
DRAW_PY = draw.py

ifeq ($(OS), Windows_NT)
	RM = del
	TARGET_CPP = main.exe

else
	RM = rm
	TARGET_CPP = main

endif

all:
	$(CC) $(CFLAGS) -o $(TARGET_CPP) $(SOURCE_CPP)

clean:
	echo $(OS)
	$(RM) $(TARGET_CPP)

run: all
	$(TARGET_CPP) > ./data/map_cpp_stat.txt
	$(PY) $(SOURCE_PY) > ./data/map_py_stat.txt
	$(PY) $(DRAW_PY)