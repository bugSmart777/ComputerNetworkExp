.PHONY: clean
#all: UDPClient UDPServer TCPClient TCPServer
all: TCPClient TCPServer

#UDPClient: UDPClient.cc
#	g++  UDPClient.cc -o UDPClient -Wall -g

#UDPServer: UDPServer.cc
#	g++  UDPServer.cc -o UDPServer -Wall -g
	
TCPClient: TCPClient.cc
	g++  TCPClient.cc -o TCPClient -Wall -g

TCPServer: TCPServer.cc
	g++  TCPServer.cc -o TCPServer -Wall -g


clean:
	rm -rf TCPClient
	rm -rf TCPServer
	rm -rf UDPClient
	rm -rf UDPServer
