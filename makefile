FLAGS = -O3 -std=c++17 -lpthread
# FLAGS =  -Wall -O3 -std=c++17 -lpthread

all: exe

io.o: src/io.cc
		g++ -o io.o -c src/io.cc                             ${FLAGS}

renderer.o: src/renderer.cc
		g++ -o renderer.o -c src/renderer.cc                 ${FLAGS}

primitives.o: src/primitives.cc
		g++ -o primitives.o -c src/primitives.cc             ${FLAGS}

exe: io.o renderer.o primitives.o src/main.cc
		g++ -o exe src/main.cc io.o renderer.o primitives.o  ${FLAGS}

clean:
		rm *.o
