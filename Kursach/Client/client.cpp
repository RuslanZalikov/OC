#include <iostream>
#include <string>
#include <sys/types.h> //для переменных 
#include <sys/socket.h> //для сокета
#include <stdlib.h> //для exit
#include <netinet/in.h> //для sockaddr_in
#include <arpa/inet.h> //для htons

using namespace std;

int createServer();
struct sockaddr_in createAddress(int port);
void Connect(int server, struct sockaddr_in address_server);
void Send(int server, char* msg);
void Sending(int server, int port);
string Convertor(string msg);

int createServer(){
        int server = socket(AF_INET, SOCK_STREAM, 0);
        if (server == -1){
                cout << "Error: socker failed" << endl;
                exit(0);
        }
        return server;
}

struct sockaddr_in createAddress(int port){
        struct sockaddr_in address_server;

        address_server.sin_family = AF_INET;
        address_server.sin_port = htons(port); //от хоста в интернет
        int inpt = inet_pton(AF_INET, "0.0.0.0", &address_server.sin_addr);

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
	int size = msg.size();
	char msg_c[size+1];
	for (int i = 0; i < size; i++){
		msg_c[i] = msg[i];
	}
	msg_c[size] = '\0';
	size++;
        send(server, &size, sizeof(int), 0);
        send(server, &msg_c, size, 0);
}

void Sending(int server, int port){
	int size_1 = 0;

        recv(server, &size_1, sizeof(int), 0);

        char msg_l[size_1];
        recv(server, &msg_l, size_1, 0);
        cout << msg_l << endl;
	while(true){

		string msg;
		getline(cin, msg);

		Send(server, msg);
		if (msg == "stop"){
			return;
		}
		if (msg == "videocard" && port == 3333){
			int size = 0;

                	int resp = recv(server, &size, sizeof(int), 0);
                	if (resp <= 0){
                        	break;
                	}

                	char msg[size];
                	recv(server, &msg, size, 0);
			cout << msg << endl;

		}
		if (msg == "client size" && port == 3333){
			string msg_1;
			msg_1 = "100 100";
			Send(server, msg_1);
		
			int size = 0;

                        int resp = recv(server, &size, sizeof(int), 0);
                        if (resp <= 0){
                                break;
                        }

                        char msg[size];
                        recv(server, &msg, size, 0);
                        cout << msg << endl;
		}

		if (msg == "swap" && port == 3334){
                     	int size = 0;

                        int resp = recv(server, &size, sizeof(int), 0);
                        if (resp <= 0){
                                break;
                        }

                        char msg[size];
                        recv(server, &msg, size, 0);
                        cout << msg << endl;
                }

		if (msg == "memory" && port == 3334){
			string msg_1;
			getline(cin, msg_1);
			Send(server, msg_1);

			int size = 0;

                        int resp = recv(server, &size, sizeof(int), 0);
                        if (resp <= 0){
                                break;
                        }

                        char msg[size];
                        recv(server, &msg, size, 0);
                        cout << msg << endl;
		}

	}
}

string Convertor(string msg){
	return msg +"\n";
}

int main(){
	cout << "Enter server1 or server2: ";

	string msg;
	getline(cin, msg);

	cout << endl;
	
	int port = 3333;

	if (msg == "server1"){
		port = 3333;
	}
	if (msg == "server2"){
		port = 3334;
	}

	int server = createServer();

	struct sockaddr_in address_server = createAddress(port);
	
	Connect(server, address_server);
		
	Sending(server, port);
	
	return 0;
}
