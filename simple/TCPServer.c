#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char const *argv[]){
	// response do servidor
	char server_message[256] = "You have rechead the server!";

	// criando socket do servidor
	int server_socket;
	server_socket = socket(AF_INET, SOCK_STREAM, 0);

	// setando dados do servidor (porta, addr)
	struct sockaddr_in server_address;
	memset(&server_address, 0, sizeof(server_address));
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(9000);
	server_address.sin_addr.s_addr = inet_addr("0.0.0.0");

	bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address));

	listen(server_socket, 5);

	// aceitando conexao com o cliente
	int client_socket;
	client_socket = accept(server_socket, NULL, NULL);

	// enviando response ao cliente
	send(client_socket, server_message, sizeof(server_message), 0);

	close(server_socket);

	return 0;
}