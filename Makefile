CC=g++
SRC=main.cpp image.cpp
TARGET=raytracer
CFLAGS=-std=c++17 -O3
LDFLAGS=

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(LDFLAGS) $(SRC) -o $(TARGET)

clean:
	rm raytracer
