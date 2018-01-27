.PHONY: all clean
all: client server

Printer.cpp Printer.h:
	slice2cpp Printer.ice

client: Client.cpp Printer.cpp
	g++ -I. Client.cpp Printer.cpp -lIce -lIceUtil -lpthread -o client

server: Server.cpp Printer.cpp
	g++ -I. Server.cpp Printer.cpp PrinterI.cpp -lIce -lIceUtil -lpthread -o server

clean:
	-rm Printer.cpp Printer.h client server
