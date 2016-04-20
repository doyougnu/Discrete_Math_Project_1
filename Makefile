run: CommandLine.o Graph.o Vertex.o Edge.o Tools.o
	g++ -std=c++11 CommandLine.o Graph.o Vertex.o Edge.o Tools.o -o run

CommandLine.o: CommandLine.cpp Graph.h Tools.h
	g++ -c CommandLine.cpp

Graph.o: Graph.cpp Graph.h Vertex.h Edge.h Tools.h
	g++ -c Graph.cpp

Vertex.o: Vertex.cpp Vertex.h
	g++ -c Vertex.cpp

Edge.o: Edge.cpp Edge.h
	g++ -c Edge.cpp

Tools.o: Tools.cpp Tools.h
	g++ -c Tools.cpp
