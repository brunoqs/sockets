/*
 usage: gcc TCPServer.c -o server -lpthread 
		./server
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <pthread.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <arpa/inet.h>

void str_to_upper(char *src){
	while (*src != '\0'){
		*src = toupper((unsigned char) *src);
		src++;
	} 
}

void *connection_handler(void *socket){
	// response do servidor
	char server_message[256];
	int client_socket = *(int*)socket;

	memset(&server_message, '\0', sizeof(server_message));
	recv(client_socket, &server_message, sizeof(server_message), 0);

	// enviando response ao cliente modificada
	str_to_upper(server_message);
	send(client_socket, server_message, sizeof(server_message), 0);

	close(client_socket);
	return NULL;
}

int main(int argc, char const *argv[]){
	// response do servidor
	//char server_message[256];

	// criando socket do servidor
	int server_socket;
	server_socket = socket(AF_INET, SOCK_STREAM, 0);

	// setando dados do servidor (porta, addr)
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(9000);
	server_address.sin_addr.s_addr = inet_addr("0.0.0.0");

	bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address));

	listen(server_socket, 1);

	int client_socket;
	pthread_t thread_id;
	while(1){
		// aceitando conexao com o cliente
		client_socket = accept(server_socket, NULL, NULL);

		// criando thread
        if(pthread_create( &thread_id , NULL ,  connection_handler , (void*) &client_socket) < 0){
            perror("could not create thread");
            return 1;
        }
        
       // se colocar o join, a thread precisa terminar para executar outra
       // pthread_join(thread_id , NULL);

	}

	return 0;
}