FLAGS = -O3 -std=c++17 -lpthread
# FLAGS =  -Wall -O3 -std=c++17

all: exe

exe: src/main.cc
		g++ -o io.o -c src/io.cc     ${FLAGS}
		g++ -o exe src/main.cc io.o  ${FLAGS}
