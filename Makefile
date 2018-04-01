CC=g++
SRC=camera.cpp geometry.cpp image.cpp main.cpp material.cpp raytracer.cpp scene.cpp
TARGET=raytracer
CFLAGS=-std=c++17
LDFLAGS=
RELEASE=-O3
DEBUG=-g -Wall

release: $(SRC)
	$(CC) $(CFLAGS) $(RELEASE) $(LDFLAGS) $(SRC) -o $(TARGET)

debug: $(SRC)
	$(CC) $(CFLAGS) $(DEBUG) $(LDFLAGS) $(SRC) -o $(TARGET)

clean:
	rm raytracer
