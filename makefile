FLAGS = -O3 -std=c++17 -lpthread
# FLAGS =  -Wall -O3 -std=c++17 -lpthread

all: exe clean

io.o: src/io.cc
		g++ -o io.o -c src/io.cc                 ${FLAGS}

renderer.o: src/renderer.cc
		g++ -o renderer.o -c src/renderer.cc     ${FLAGS}

exe: io.o renderer.o
		g++ -o exe src/main.cc io.o renderer.o   ${FLAGS}

clean:
		rm *.o
