all:
	g++ `pkg-config --cflags opencv` label_face.cpp `pkg-config --libs opencv`

run:
	./a.out 800/base/ >800-landmarks

clean:
	rm *.o a.out
