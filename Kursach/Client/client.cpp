#include <iostream>
#include <string>
#include <sys/types.h> //для переменных 
#include <sys/socket.h> //для сокета
#include <stdlib.h> //для exit
#include <netinet/in.h> //для sockaddr_in
#include <arpa/inet.h> //для htons

using namespace std;

int createServer();
struct sockaddr_in createAddress();
void Connect(int server, struct sockaddr_in address_server);
void Send(int server, string msg);

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

void Connect(int server, struct sockaddr_in address_server){
	if(connect(server, (struct sockaddr*)&address_server, sizeof(address_server)) < 0){
                cout << "connetion failed" << endl;
                exit(0);
        }
}

void Send(int server, string msg){
	uint32_t size = htonl(msg.size());
        send(server, &size, sizeof(uint32_t), 0);
        send(server, msg.c_str(), msg.size(), 0);
}

int main(){
	int server = createServer();

	struct sockaddr_in address_server = createAddress();
	
	Connect(server, address_server);

	string msg = "HELLO\n";
	
	Send(server, msg);
	
	return 0;
}
