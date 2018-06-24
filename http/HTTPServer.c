/* 
Usage: gcc HTTPServer.c -o httpserver
	   create an index.html in the same folder
	   ./httpserver
	   telnet localhost 8000
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <arpa/inet.h>

int main(int argc, char const *argv[]){
	// abrindo o arquivo que vai ser enviado para o cliente
	FILE *html_data;
	html_data = fopen("index.html", "r");
	
	char response_data[1024];
	// copiando arquivo para variavel
	fgets(response_data, 1024, html_data);

	char http_header[2048] = "HTTP/1.1 200 OK\r\n";
	strcat(http_header, response_data);

	// criando o socket
	int server_socket;
	server_socket = socket(AF_INET, SOCK_STREAM, 0);

	// definindo porta, addr
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(8000);
	server_address.sin_addr.s_addr = inet_addr("0.0.0.0");

	bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address));

	listen(server_socket, 5);

	int client_socket;
	while(1){
		client_socket = accept(server_socket, NULL, NULL);
		send(client_socket, http_header, sizeof(http_header), 0);
		close(client_socket);
	}

	return 0;
}