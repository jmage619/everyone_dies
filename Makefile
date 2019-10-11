CPPFLAGS = -I/usr/include/lua5.3
CXXFLAGS := -Wall -g
LIB = -llua
CXX = g++

all: everyone_dies

everyone_dies: everyone_dies.o

everyone_dies.o : everyone_dies.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c -o $@ $<
