.PHONY: all clean
all: client chatserver groupservermanager

Chat.cpp Chat.h:
	slice2cpp Chat.ice

client: Client.cpp Chat.cpp UserI.cpp
	g++ -I. Client.cpp Chat.cpp UserI.cpp -lIce -lIceUtil -lpthread -o client

chatserver: Server.cpp Chat.cpp ChatServerI.cpp GroupServerI.cpp GroupServerManagerI.cpp ChatException.cpp
	g++ -I. Server.cpp Chat.cpp ChatServerI.cpp GroupServerI.cpp GroupServerManagerI.cpp ChatException.cpp -lIce -lIceUtil -lpthread -o server

groupservermanager: GroupServerManager.cpp Chat.cpp GroupServerI.cpp GroupServerManagerI.cpp
	g++ -I. GroupServerManager.cpp Chat.cpp GroupServerI.cpp GroupServerManagerI.cpp -lIce -lIceUtil -lpthread -o groupservermanager

clean:
	-rm Chat.cpp Chat.h client server groupservermanager
