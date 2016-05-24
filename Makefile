all:
	g++ `pkg-config --cflags opencv` label_face.cpp `pkg-config --libs opencv`

run:
	./a.out 800/base

clean:
	rm *.o a.out
