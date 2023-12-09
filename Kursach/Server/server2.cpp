#include <iostream>
#include <fstream>
#include <string>
#include <pthread.h>
#include <ctime>
#include <sys/types.h> //для переменных 
#include <sys/socket.h> //для сокета
#include <stdlib.h> //для exit
#include <netinet/in.h> //для sockaddr_in
#include <arpa/inet.h> //для htons
#include <unistd.h> //для sleep
#include <cstdlib> //для system

using namespace std;

struct ThreadWithClient;
int createServer();
struct sockaddr_in createAddress();
void Bind(int server, struct sockaddr_in address_server);
void Listener(int server);
void Send(int client, string msg);
void* recvMSG(void* client_void);
void* Accept(void* server_void);
string task3();
string task4(int client);

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
        address_server.sin_port = htons(3334); //от хоста в интернет
        int inpt = inet_pton(AF_INET, "0.0.0.0", &address_server.sin_addr);
        
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

void Send(int client, string msg){
        int size = msg.size();
        char msg_c[size+1];
        for (int i = 0; i < size; i++){
                msg_c[i] = msg[i];
        }
        msg_c[size] = '\0';
        size++;
        send(client, &size, sizeof(int), 0);
        send(client, &msg_c, size, 0);
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

		if ((string)msg == "stop"){
                        break;
                }
		if ((string)msg == "swap"){
			string response = task3();
			time_t result = std::time(nullptr);
			response = (string)"\n" + asctime(std::localtime(&result)) + (string)"\n" + response;
			Send(client, response);
		}
		if ((string)msg == "memory"){
			string response = task4(client);
			if(response == "disconnect"){
				break;
			}
			time_t result = std::time(nullptr);
                        response = (string)"\n" + asctime(std::localtime(&result)) + (string)"\n" + response;
			Send(client, response);
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
		
		string msg = "Connection in server2\nPull command:\n\tswap: get swap information\n\tmemory: get memory information then you continue request\n\t\tg-gigabyte\n\t\tm-megabyte\n\t\tk-kilobyte\n\t\tb-byte";
                Send(client, msg);


		pthread_t thread;
		ThreadWithClien arg;
		arg.client = client;
		arg.thread = thread;
		pthread_create(&thread, NULL, recvMSG, &arg);
	}
}

string task3(){
	system("./scripts/swap.sh");
	ifstream file("scripts/swap.txt");
	if (!file){
		cout << "Error: swap failed" << endl;
	}
	string swresp = "";
	string tmp;
	while(!file.eof()){
		getline(file, tmp);
		swresp += tmp;
		swresp += "\n";
	}
	return swresp;
}

string task4(int client){
	int size = 0;

        int resp = recv(client, &size, sizeof(int), 0);

        char msg[size];
        recv(client, &msg, size, 0);
        string msg_s = msg;
        if (msg_s == "G" || msg_s == "g"){
		system("./scripts/mem_g.sh");
        	ifstream file("scripts/mem_g.txt");
        	if (!file){
                	cout << "Error: swap failed" << endl;
        	}
        	string swresp = "";
        	string tmp;
        	while(!file.eof()){
                	getline(file, tmp);
                	swresp += tmp;
                	swresp += "\n";
        	}
        	return swresp;
	}
	if (msg_s == "M" || msg_s == "m"){
		system("./scripts/mem_m.sh");
                ifstream file("scripts/mem_m.txt");
                if (!file){
                        cout << "Error: swap failed" << endl;
                }
                string swresp = "";
                string tmp;
                while(!file.eof()){
                        getline(file, tmp);
                        swresp += tmp;
                        swresp += "\n";
                }
                return swresp;
	}
	if (msg_s == "K" || msg_s == "k"){
		system("./scripts/mem_k.sh");
                ifstream file("scripts/mem_k.txt");
                if (!file){
                        cout << "Error: swap failed" << endl;
                }
                string swresp = "";
                string tmp;
                while(!file.eof()){
                        getline(file, tmp);
                        swresp += tmp;
                        swresp += "\n";
                }
                return swresp;
	}
	if (msg_s == "B" || msg_s == "b"){
		system("./scripts/mem_b.sh");
                ifstream file("scripts/mem_b.txt");
                if (!file){
                        cout << "Error: swap failed" << endl;
                }
                string swresp = "";
                string tmp;
                while(!file.eof()){
                        getline(file, tmp);
                        swresp += tmp;
                        swresp += "\n";
                }
                return swresp;
	}
	if (msg_s == "stop"){
		return "disconnect";
	}
	return "disconnect";
}

int main(){
	int server = createServer();
	
	struct sockaddr_in address_server = createAddress();
	
	Bind(server, address_server);

	Listener(server);

	Accept(&server);

	return 0;
}
