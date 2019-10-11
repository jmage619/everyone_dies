CPPFLAGS = -I/usr/include/lua5.3
LDFLAGS = -L/opt/local/lib
CXXFLAGS := -Wall -g
LIB = -llua5.3
CXX = g++

all: everyone_dies

everyone_dies: everyone_dies.o
	$(CXX) $(LDFLAGS) -o $@ $^ $(LIB)

everyone_dies.o : everyone_dies.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c -o $@ $<
