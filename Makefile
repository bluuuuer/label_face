all:
	g++ `pkg-config --cflags opencv` label_face.cpp `pkg-config --libs opencv`

run:
	./a.out 800/base/ > landmarks-800

clean:
	rm *.o a.out
