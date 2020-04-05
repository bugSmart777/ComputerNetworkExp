src = $(wildcard *.cc)
obj = $(patsubst %.cc, %.o, $(src))

all: TCPServer TCPClient

TCPServer: TCPServer.o global.o
	g++ TCPServer.o global.o -o TCPServer -Wall
TCPClient: TCPClient.o global.o
	g++ TCPClient.o global.o -o TCPClient -Wall

%.o:%.cc
	g++ -c $< -Wall

.PHONY: clean all
clean: 
	-rm -rf TCPServer TCPClient $(obj)

