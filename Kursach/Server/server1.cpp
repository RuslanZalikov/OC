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
struct ThreadWithClient;
int createServer();
struct sockaddr_in createAddress();
void Bind(int server, struct sockaddr_in address_server);
void Listener(int server);
void* recvMSG(void* client_void);
void* Accept(void* server_void);

struct ThreadWithClien{
	int client;
	pthread_t thread;
};


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
	if(listen(server, 10) == -1){
                cout << "Error: listen failed" << endl;
                exit(0);
        }	
}

void* recvMSG(void* arg_void){
	ThreadWithClien arg;
       	arg = *(struct ThreadWithClien*)arg_void;
	int client = arg.client;
	pthread_t thread = arg.thread;
	int counter = 0;
	while(true){
        	int size = 0;
		
        	int resp = recv(client, &size, sizeof(int), 0);
		if (resp <= 0){
			break;
		}

		char msg[size];
        	recv(client, &msg, size, 0);

		cout << "Message from " << client << " client: " << msg << "\n";	
		if (msg == "stop"){
			break;
		}
	}
	cout << "Disconnect client! Client id " << client << "\n";
	//pthread_join(thread, NULL);
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
		cout << "Connection client! Client id " << client << "\n";
		pthread_t thread;
		ThreadWithClien arg;
		arg.client = client;
		arg.thread = thread;
		pthread_create(&thread, NULL, recvMSG, &arg);
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
