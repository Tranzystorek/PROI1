CC=g++
INCLUDE_DIR=-Iheaders

all: program

program: Tile.o Map.o Generator.o Menu.o
	$(CC) $(INCLUDE_DIR) -o program.o src/main.cc src/Tile.o src/Map.o src/Generator.o src/Menu.o

clean:
	rm *.o
	rm src/*.o
	make program

Menu.o:
	$(CC) $(INCLUDE_DIR) -c -o src/Menu.o src/Menu.cc

Tile.o:
	$(CC) $(INCLUDE_DIR) -c -o src/Tile.o src/Tile.cc

Map.o:
	$(CC) $(INCLUDE_DIR) -c -o src/Map.o src/Map.cc

Generator.o:
	$(CC) $(INCLUDE_DIR) -c -o src/Generator.o src/Generator.cc
