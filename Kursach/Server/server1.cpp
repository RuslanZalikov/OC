#include <iostream>
#include <string>
#include <pthread.h>
#include <sys/types.h> //для переменных 
#include <sys/socket.h> //для сокета
#include <stdlib.h> //для exit
#include <netinet/in.h> //для sockaddr_in
#include <arpa/inet.h> //для htons
#include <unistd.h> //для sleep

using namespace std;

int createServer();
struct sockaddr_in createAddress();
void Bind(int server, struct sockaddr_in address_server);
void Listener(int server);
void* recvMSG(void* client_void);
void* Accept(void* server_void);

int createServer(){
	int server = socket(AF_INET, SOCK_STREAM, 0);
        if (server == -1){
                cout << "Error: socker failed" << endl;
                exit(0);
        }
	return server;
}

struct sockaddr_in createAddress(){
	struct sockaddr_in address_server;

	address_server.sin_family = AF_INET;
        address_server.sin_port = htons(3333); //от хоста в интернет
        int inpt = inet_pton(AF_INET, "127.0.0.1", &address_server.sin_addr);
        
	if (inpt == -1){
                cout << "Error: inet_pton failed" << endl;
                exit(0);
        }

	return address_server;

}

void Bind(int server, struct sockaddr_in address_server){
	if(bind(server, (struct sockaddr*)&address_server, sizeof(address_server)) == -1){
                cout << "Error: bind failed" << endl;
                exit(0);
        }

}

void Listener(int server){
	if(listen(server, 0) == -1){
                cout << "Error: listen failed" << endl;
                exit(0);
        }	
}

void* recvMSG(void* client_void){
        int client = *(int*)client_void;

        uint32_t size;
        recv(client, &size, sizeof(uint32_t), 0);
        size = ntohl(size);

        char msg[size];
        recv(client, &msg, size, 0);

        cout << "START\n";
        sleep(5);
        cout << msg;
	return nullptr;
}

void* Accept(void* server_void){
	while(true){
        	int server = *(int*)server_void;
	
		struct sockaddr_in address_client;
        	socklen_t address_client_len;
        	int client = accept(server, (struct sockaddr*)&address_client, &address_client_len);
        	if (client == -1){
			cout << "Error: client failed" << endl;
		}
		pthread_t thread;
		pthread_create(&thread, NULL, recvMSG, &client);
	}
}

int main(){
	int server = createServer();
	
	struct sockaddr_in address_server = createAddress();
	
	Bind(server, address_server);

	Listener(server);

	Accept(&server);

	return 0;
}
