all: PracticalSocket.o server client main
server: PracticalSocket.o server.cpp
	g++ -pedantic-errors -g server.cpp PracticalSocket.o -o server
client: PracticalSocket.o client.cpp
	g++ -pedantic-errors -g client.cpp PracticalSocket.o -o client
PracticalSocket.o: PracticalSocket.h PracticalSocket.cpp
	g++ -pedantic-errors -g -c PracticalSocket.cpp -o PracticalSocket.o
main: main.cpp
	g++ -pedantic-errors -g main.cpp -o main
	