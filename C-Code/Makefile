all: game client server

client:	client.c game.h game.c header.h packets.c packets.h
	gcc -o client client.c game.h game.c header.c

server:	server.c game.h game.c epoll.h epoll.c packets.h
	gcc -o server server.c game.h game.c epoll.h epoll.c

game:	main.c game.h game.c
	gcc -o game main.c game.c

clean:
	rm game server client *~
