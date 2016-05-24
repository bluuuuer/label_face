all: label_face.cpp restore
	g++ `pkg-config --cflags opencv` label_face.cpp `pkg-config --libs opencv`

restore:
	g++ `pkg-config --cflags opencv` -o restore restore.cpp `pkg-config --libs opencv`

run:
	./a.out 800/base/ > landmarks-800

clean:
	rm *.o a.out
