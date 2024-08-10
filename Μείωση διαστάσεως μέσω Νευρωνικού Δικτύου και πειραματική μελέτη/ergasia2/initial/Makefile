CC = g++
modules = Image.cpp Graph.cpp LSH.cpp Random.cpp algorithms.cpp
args = -o

graph_search: Image.cpp Graph.cpp LSH.cpp Random.cpp algorithms.cpp main.cpp
	$(CC) main.cpp $(modules) $(args) graph_search

graph_search_valgrind: Image.cpp Graph.cpp LSH.cpp Random.cpp algorithms.cpp main.cpp
	$(CC) main.cpp $(modules) -g $(args) graph_search_valgrind

clean: 
	rm graph_search