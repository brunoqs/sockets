#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h> 
#include <arpa/inet.h> //inet_addr

int main(int argc, char const *argv[]){
	// criando socket
	int network_socket;
	network_socket = socket(AF_INET, SOCK_STREAM, 0);

	// criando struct com com os campos do servidor
	struct sockaddr_in server_address;
	memset(&server_address, 0, sizeof(server_address));
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(9000);
	server_address.sin_addr.s_addr = inet_addr("104.211.27.158");

	// fazendo conexao com o servidor
	int connection_status = connect(network_socket, (struct sockaddr *) &server_address, sizeof(server_address));

	// verificando erro de conexao com servidor
	if (connection_status == -1){
		printf("There was an error making a connection to the remote socket\n");
	}

	// pegando a response do servidor
	char server_response[256];
	recv(network_socket, &server_response, sizeof(server_response), 0);

	printf("The server sent the data: %s\n", server_response);

	close(network_socket);
	
	return 0;
}