FLAGS = -O3 -std=c++17
# FLAGS =  -Wall -O3 -std=c++17

all: exe

exe: src/main.cc
		g++ -o exe src/main.cc ${FLAGS}
