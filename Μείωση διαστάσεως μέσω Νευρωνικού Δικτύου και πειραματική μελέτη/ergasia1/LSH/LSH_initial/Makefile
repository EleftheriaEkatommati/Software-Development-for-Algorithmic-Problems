CC = g++
modules = Create_image_vector.cpp Random.cpp Hash.cpp
args = -o

lsh: Create_image_vector.cpp Random.cpp Hash.cpp lsh.cpp
	$(CC) lsh.cpp $(modules) $(args) lsh

clean: 
	rm lsh