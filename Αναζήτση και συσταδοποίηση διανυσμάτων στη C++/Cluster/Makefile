CC = g++
modules = Hash.cpp Image.cpp Cluster.cpp
args = -o

cluster: Image.cpp Cluster.cpp Hash.cpp main.cpp
	$(CC) main.cpp $(modules) $(args) cluster

clean: 
	rm cluster