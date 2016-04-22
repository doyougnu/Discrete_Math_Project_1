run: CommandLine.o Graph.o Vertex.o Edge.o Tools.o
	g++ -std=c++11 CommandLine.o Graph.o Vertex.o Edge.o Tools.o -o run

CommandLine.o: CommandLine.cpp Graph.h Tools.h
	g++ -std=c++11 -c CommandLine.cpp

Graph.o: Graph.cpp Graph.h Vertex.h Edge.h Tools.h
	g++ -std=c++11 -c Graph.cpp

Vertex.o: Vertex.cpp Vertex.h
	g++ -std=c++11 -c Vertex.cpp

Edge.o: Edge.cpp Edge.h
	g++ -std=c++11 -c Edge.cpp

Tools.o: Tools.cpp Tools.h
	g++ -std=c++11 -c Tools.cpp
