/* 
Usage: gcc HTTPClient.c -o httpclient
	   ./httpclient <ip-addr>
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <arpa/inet.h>

int main(int argc, char const *argv[]){

	const char *server_ip = argv[1];

	// criando socket do cliente
	int client_socket;
	client_socket = socket(AF_INET, SOCK_STREAM, 0);

	// infos do servidor
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET; //IPV4
	server_address.sin_port = htons(80);
	server_address.sin_addr.s_addr = inet_addr(server_ip);

	// conectando cliente - servidor
	connect(client_socket, (struct sockaddr *) &server_address, sizeof(server_address));

	// enviando request
	char request[] = "GET / HTTP/1.1\r\n\r\n";
	send(client_socket, request, sizeof(request), 0);

	// recebendo response
	char response[4096];
	recv(client_socket, &response, sizeof(response), 0);

	printf("%s\n", response);

	close(client_socket);

	return 0;
}