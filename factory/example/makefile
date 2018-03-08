CXX ?= g++
CC ?= gcc
CPPFLAGS += -std=c++11 -O2

#export CXX CC CFLAGS CPPFLAGS

all: example

example: main.cpp factory.cpp
	$(CXX) $(CPPFLAGS) $^ -o $@

clean:
	@rm -rf example

