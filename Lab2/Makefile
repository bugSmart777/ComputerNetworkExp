src = $(wildcard *.cc)
obj = $(patsubst %.cc, %.o, $(src))

all: TCPServer TCPClient Mpts Mptc UDPServer UDPClient Mtts Mttc

TCPServer: TCPServer.o global.o
	g++ TCPServer.o global.o -o TCPServer -Wall
TCPClient: TCPClient.o global.o
	g++ TCPClient.o global.o -o TCPClient -Wall
UDPServer: UDPServer.o global.o
	g++ UDPServer.o global.o -o UDPServer -Wall
UDPClient: UDPClient.o global.o
	g++ UDPClient.o global.o -o UDPClient -Wall
Mpts: muti_process_tcpServer.o global.o
	g++ muti_process_tcpServer.o global.o -o Mpts -Wall
Mptc: muti_process_tcpClient.o global.o
	g++ muti_process_tcpClient.o global.o -o Mptc -Wall
Mtts: muti_thread_tcpServer.o global.o
	g++ muti_thread_tcpServer.o global.o -o Mtts -Wall -lpthread
Mttc: muti_thread_tcpClient.o global.o
	g++ muti_thread_tcpClient.o global.o -o Mttc -Wall -lpthread


%.o:%.cc
	g++ -c $< -Wall

.PHONY: clean all
clean: 
	-rm -rf TCPServer TCPClient UDPServer UDPClient Mpts Mptc Mtts Mttc $(obj)

