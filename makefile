FLAGS = -O3 -std=c++17 -lpthread
# FLAGS =  -Wall -O3 -std=c++17

all: exe

exe: src/main.cc src/io.h src/AMvector.h
		g++ -o exe src/main.cc ${FLAGS}
