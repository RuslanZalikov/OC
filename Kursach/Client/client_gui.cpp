#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <sys/types.h> //для переменных 
#include <sys/socket.h> //для сокета
#include <stdlib.h> //для exit
#include <netinet/in.h> //для sockaddr_in
#include <arpa/inet.h> //для htons

int createServer();
struct sockaddr_in createAddress();
void Connect(int server, struct sockaddr_in address_server);
void Send(int server, char* msg);
void Sending(int server);

using namespace std;
using namespace sf;

int createServer(){
        int server = socket(AF_INET, SOCK_STREAM, 0);
        if (server == -1){
                cout << "Error: socker failed" << endl;
                exit(0);
        }
        return server;
}

struct sockaddr_in createAddress(int host){
        struct sockaddr_in address_server;

        address_server.sin_family = AF_INET;
        address_server.sin_port = htons(host); //от хоста в интернет
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



int main(){
	int server1, server2;
	int w = 640, h = 480;

	RenderWindow window;
	window.create(VideoMode(w, h), L"OKHO", Style::Default);
	window.setVerticalSyncEnabled(true);

	RectangleShape button1(Vector2f(200, 100));
	button1.setPosition(w/2-100, h/2-110);
	button1.setFillColor(Color(100, 100, 100));

	RectangleShape button2(Vector2f(200, 100));
	button2.setPosition(w/2-100, h/2+10);
	button2.setFillColor(Color(100, 100, 100));

	RectangleShape buttonBack(Vector2f(160, 80));
        buttonBack.setPosition(20, 20);
        buttonBack.setFillColor(Color(100, 100, 100));

	RectangleShape button11(Vector2f(200, 100));
        button11.setPosition(w/2-100, h/2-110);
        button11.setFillColor(Color(100, 100, 100));

        RectangleShape button12(Vector2f(200, 100));
        button12.setPosition(w/2-100, h/2+10);
        button12.setFillColor(Color(100, 100, 100));

	RectangleShape button21(Vector2f(200, 100));
        button21.setPosition(w/2-100, h/2-110);
        button21.setFillColor(Color(100, 100, 100));

        RectangleShape button22(Vector2f(200, 100));
        button22.setPosition(w/2-100, h/2+10);
        button22.setFillColor(Color(100, 100, 100));

	RectangleShape button22G(Vector2f(80, 80));
        button22G.setPosition(w/2-100, h/2-100);
        button22G.setFillColor(Color(100, 100, 100));

	RectangleShape button22M(Vector2f(80, 80));
        button22M.setPosition(w/2, h/2-100);
        button22M.setFillColor(Color(100, 100, 100));

	RectangleShape button22K(Vector2f(80, 80));
        button22K.setPosition(w/2-100, h/2);
        button22K.setFillColor(Color(100, 100, 100));

	RectangleShape button22B(Vector2f(80, 80));
        button22B.setPosition(w/2, h/2);
        button22B.setFillColor(Color(100, 100, 100));

	
	Font font;
	font.loadFromFile("Rubik-Bold.ttf");

	Text text1;
	text1.setFont(font);
	text1.setString("server1");
	text1.setCharacterSize(50);
	text1.setPosition(w/2-95, h/2-95);
	text1.setFillColor(Color(50, 50, 50));

	Text text2;
	text2.setFont(font);
	text2.setString("server2");
	text2.setCharacterSize(50);
	text2.setPosition(w/2-98, h/2+25);
	text2.setFillColor(Color(50, 50, 50));
	
	Text textBack;
        textBack.setFont(font);
        textBack.setString("back");
        textBack.setCharacterSize(50);
        textBack.setPosition(37, 25);
        textBack.setFillColor(Color(50, 50, 50));

	Text text11;
        text11.setFont(font);
        text11.setString("task1");
        text11.setCharacterSize(50);
        text11.setPosition(w/2-70, h/2-95);
        text11.setFillColor(Color(50, 50, 50));

        Text text12;
        text12.setFont(font);
        text12.setString("task2");
        text12.setCharacterSize(50);
        text12.setPosition(w/2-70, h/2+25);
        text12.setFillColor(Color(50, 50, 50));

	Text text21;
        text21.setFont(font);
        text21.setString("task3");
        text21.setCharacterSize(50);
        text21.setPosition(w/2-70, h/2-95);
        text21.setFillColor(Color(50, 50, 50));

        Text text22;
        text22.setFont(font);
        text22.setString("task4");
        text22.setCharacterSize(50);
        text22.setPosition(w/2-70, h/2+25);
        text22.setFillColor(Color(50, 50, 50));

	Text text22G;
        text22G.setFont(font);
        text22G.setString("G");
        text22G.setCharacterSize(50);
        text22G.setPosition(w/2-80, h/2-90);
        text22G.setFillColor(Color(50, 50, 50));

	Text text22M;
        text22M.setFont(font);
        text22M.setString("M");
        text22M.setCharacterSize(50);
        text22M.setPosition(w/2+20, h/2-90);
        text22M.setFillColor(Color(50, 50, 50));

	Text text22K;
        text22K.setFont(font);
        text22K.setString("K");
        text22K.setCharacterSize(50);
        text22K.setPosition(w/2-80, h/2+10);
        text22K.setFillColor(Color(50, 50, 50));

	Text text22B;
        text22B.setFont(font);
        text22B.setString("B");
        text22B.setCharacterSize(50);
        text22B.setPosition(w/2+20, h/2+10);
        text22B.setFillColor(Color(50, 50, 50));



	std::string status = "server_menu";

	while(window.isOpen()){
		Vector2i mousePoz = Mouse::getPosition(window);

		Event event;

		double new_w = window.getSize().x, new_h = window.getSize().y;
                double k_w = w/new_w, k_h = h/new_h;

		while(window.pollEvent(event)){
			if(event.type == Event::Closed){
				window.close();
			}

			if(event.type == Event::MouseButtonPressed){
				if(event.mouseButton.button == Mouse::Left){
					if(button1.getGlobalBounds().contains(mousePoz.x*k_w, mousePoz.y*k_h) 
							&& status == "server_menu"){
						cout << "server1" << endl << endl;
						button1.setFillColor(Color(80, 80, 80));
						text1.setFillColor(Color(30, 30, 30));

						server1 = createServer();

        					struct sockaddr_in address_server = createAddress(3333);

        					Connect(server1, address_server);

						int size_1 = 0;

        					recv(server1, &size_1, sizeof(int), 0);

        					char msg_l[size_1];
        					recv(server1, &msg_l, size_1, 0);
        					cout << msg_l << endl;
					}
					if(button2.getGlobalBounds().contains(mousePoz.x*k_w, mousePoz.y*k_h)
							&& status == "server_menu"){
                                                cout << "server2" << endl << endl;
						button2.setFillColor(Color(80, 80, 80));
                                                text2.setFillColor(Color(30, 30, 30));

						server2 = createServer();

						struct sockaddr_in address_server = createAddress(3334);

						Connect(server2, address_server);

						int size_1 = 0;

        					recv(server2, &size_1, sizeof(int), 0);

        					char msg_l[size_1];
        					recv(server2, &msg_l, size_1, 0);
        					cout << msg_l << endl;
                                        }
					if(buttonBack.getGlobalBounds().contains(mousePoz.x*k_w, mousePoz.y*k_h) 
							&& status != "server_menu"){
						std::cout << "back to menu" << std::endl;
						buttonBack.setFillColor(Color(80, 80, 80));
                                                textBack.setFillColor(Color(30, 30, 30));

						string msg_s = "stop";
						if (status == "server1"){
							Send(server1, msg_s);
						}
						if (status == "server2" || status == "task4"){
							Send(server2, msg_s);
						}
					}
					if(button11.getGlobalBounds().contains(mousePoz.x*k_w, mousePoz.y*k_h)
							&& status == "server1"){
                                                std::cout << "task1" << std::endl;
                                                button11.setFillColor(Color(80, 80, 80));
                                                text11.setFillColor(Color(30, 30, 30));

						string msg_s = "videocard";
                                                Send(server1, msg_s);
                                                int size = 0;

                                                int resp = recv(server1, &size, sizeof(int), 0);
                                                if (resp <= 0){
                                                        break;
                                                }

                                                char msg[size];
                                                recv(server1, &msg, size, 0);
                                                cout << msg << endl;
                                        }
					if(button12.getGlobalBounds().contains(mousePoz.x*k_w, mousePoz.y*k_h)
							&& status == "server1"){
                                                std::cout << "task2" << std::endl;
                                                button12.setFillColor(Color(80, 80, 80));
                                                text12.setFillColor(Color(30, 30, 30));
						
						string msg_1 = "client size";
						Send(server1, msg_1);

						string msg_s = "";
						msg_s += to_string(window.getSize().x);
						msg_s += " ";
						msg_s += to_string(window.getSize().y);
						msg_s += "\n";
						Send(server1, msg_s);
						int size = 0;

                                                int resp = recv(server1, &size, sizeof(int), 0);
                                                if (resp <= 0){
                                                        break;
                                                }

                                                char msg[size];
                                                recv(server1, &msg, size, 0);
                                                cout << msg << endl;

                                        }
					if(button21.getGlobalBounds().contains(mousePoz.x*k_w, mousePoz.y*k_h)
							&& status == "server2"){
                                                std::cout << "task3" << std::endl;
                                                button21.setFillColor(Color(80, 80, 80));
                                                text21.setFillColor(Color(30, 30, 30));

						string msg_s = "swap";
						Send(server2, msg_s);

						int size = 0;

                                                int resp = recv(server2, &size, sizeof(int), 0);
                                                if (resp <= 0){
                                                        break;
                                                }

                                                char msg[size];
                                                recv(server2, &msg, size, 0);
                                                cout << msg << endl;
                                        }
					if(button22.getGlobalBounds().contains(mousePoz.x*k_w, mousePoz.y*k_h)
							&& status == "server2"){
                                                std::cout << "task4" << std::endl;
                                                button22.setFillColor(Color(80, 80, 80));
                                                text22.setFillColor(Color(30, 30, 30));

						string msg_s = "memory";
                                                Send(server2, msg_s);
                                        }
					if(button22G.getGlobalBounds().contains(mousePoz.x*k_w, mousePoz.y*k_h)
                                                        && status == "task4"){
                                                std::cout << "task4: G" << std::endl;
                                                button22G.setFillColor(Color(80, 80, 80));
                                                text22G.setFillColor(Color(30, 30, 30));
						
						string msg_s = "G";
                                                Send(server2, msg_s);

                                                int size = 0;

                                                int resp = recv(server2, &size, sizeof(int), 0);
                                                if (resp <= 0){
                                                        break;
                                                }

                                                char msg[size];
                                                recv(server2, &msg, size, 0);
                                                cout << msg << endl;
						
						string msg_mem = "memory";
						Send(server2, msg_mem);

                                        }
					if(button22M.getGlobalBounds().contains(mousePoz.x*k_w, mousePoz.y*k_h)
                                                        && status == "task4"){
                                                std::cout << "task4: M" << std::endl;
                                                button22M.setFillColor(Color(80, 80, 80));
                                                text22M.setFillColor(Color(30, 30, 30));

						string msg_s = "M";
                                                Send(server2, msg_s);

                                                int size = 0;

                                                int resp = recv(server2, &size, sizeof(int), 0);
                                                if (resp <= 0){
                                                        break;
                                                }

                                                char msg[size];
                                                recv(server2, &msg, size, 0);
                                                cout << msg << endl;

						string msg_mem = "memory";
                                                Send(server2, msg_mem);

                                        }
					if(button22K.getGlobalBounds().contains(mousePoz.x*k_w, mousePoz.y*k_h)
                                                        && status == "task4"){
                                                std::cout << "task4: K" << std::endl;
                                                button22K.setFillColor(Color(80, 80, 80));
                                                text22K.setFillColor(Color(30, 30, 30));

						string msg_s = "K";
                                                Send(server2, msg_s);

                                                int size = 0;

                                                int resp = recv(server2, &size, sizeof(int), 0);
                                                if (resp <= 0){
                                                        break;
                                                }

                                                char msg[size];
                                                recv(server2, &msg, size, 0);
                                                cout << msg << endl;

						string msg_mem = "memory";
                                                Send(server2, msg_mem);

                                        }
					if(button22B.getGlobalBounds().contains(mousePoz.x*k_w, mousePoz.y*k_h)
                                                        && status == "task4"){
                                                std::cout << "task4: B" << std::endl;
                                                button22B.setFillColor(Color(80, 80, 80));
                                                text22B.setFillColor(Color(30, 30, 30));

						string msg_s = "B";
                                                Send(server2, msg_s);

                                                int size = 0;

                                                int resp = recv(server2, &size, sizeof(int), 0);
                                                if (resp <= 0){
                                                        break;
                                                }

                                                char msg[size];
                                                recv(server2, &msg, size, 0);
                                                cout << msg << endl;

						string msg_mem = "memory";
                                                Send(server2, msg_mem);

                                        }



				}
			}
			if(event.type == Event::MouseButtonReleased){
                                if(event.mouseButton.button == Mouse::Left){
                                        if(button1.getGlobalBounds().contains(mousePoz.x*k_w, mousePoz.y*k_h)
							&& status == "server_menu"){
                                                button1.setFillColor(Color(100, 100, 100));
                                                text1.setFillColor(Color(50, 50, 50));
						status = "server1";
						continue;
                                        }
                                        if(button2.getGlobalBounds().contains(mousePoz.x*k_w, mousePoz.y*k_h)
							&& status == "server_menu"){
                                                button2.setFillColor(Color(100, 100, 100));
                                                text2.setFillColor(Color(50, 50, 50));
						status = "server2";
						continue;
                                        }
					if(buttonBack.getGlobalBounds().contains(mousePoz.x*k_w, mousePoz.y*k_h)
							&& status != "server_menu"){
                                                buttonBack.setFillColor(Color(100, 100, 100));
                                                textBack.setFillColor(Color(50, 50, 50));
						status = "server_menu";
						continue;
                                        }
					if(button11.getGlobalBounds().contains(mousePoz.x*k_w, mousePoz.y*k_h)
							&& status == "server1"){
                                                button11.setFillColor(Color(100, 100, 100));
                                                text11.setFillColor(Color(50, 50, 50));
						continue;
                                        }
					if(button12.getGlobalBounds().contains(mousePoz.x*k_w, mousePoz.y*k_h)
							&& status == "server1"){
                                                button12.setFillColor(Color(100, 100, 100));
                                                text12.setFillColor(Color(50, 50, 50));
						continue;
                                        }
					if(button21.getGlobalBounds().contains(mousePoz.x*k_w, mousePoz.y*k_h)
							&& status == "server2"){
                                                button21.setFillColor(Color(100, 100, 100));
                                                text21.setFillColor(Color(50, 50, 50));
						continue;
                                        }
					if(button22.getGlobalBounds().contains(mousePoz.x*k_w, mousePoz.y*k_h)
							&& status == "server2"){
                                                button22.setFillColor(Color(100, 100, 100));
                                                text22.setFillColor(Color(50, 50, 50));
						status = "task4";
						continue;
                                        }
					if(button22G.getGlobalBounds().contains(mousePoz.x*k_w, mousePoz.y*k_h)
                                                        && status == "task4"){
                                                button22G.setFillColor(Color(100, 100, 100));
                                                text22G.setFillColor(Color(50, 50, 50));
                                                status = "task4";
                                                continue;
                                        }
					if(button22M.getGlobalBounds().contains(mousePoz.x*k_w, mousePoz.y*k_h)
                                                        && status == "task4"){
                                                button22M.setFillColor(Color(100, 100, 100));
                                                text22M.setFillColor(Color(50, 50, 50));
                                                status = "task4";
                                                continue;
                                        }
					if(button22K.getGlobalBounds().contains(mousePoz.x*k_w, mousePoz.y*k_h)
                                                        && status == "task4"){
                                                button22K.setFillColor(Color(100, 100, 100));
                                                text22K.setFillColor(Color(50, 50, 50));
                                                status = "task4";
                                                continue;
                                        }
					if(button22B.getGlobalBounds().contains(mousePoz.x*k_w, mousePoz.y*k_h)
                                                        && status == "task4"){
                                                button22B.setFillColor(Color(100, 100, 100));
                                                text22B.setFillColor(Color(50, 50, 50));
                                                status = "task4";
                                                continue;
                                        }

                                }
                        }
		}

		window.clear(Color(255, 255, 255));

        	button1.setPosition((w/2-100)*k_w, (h/2-110)*k_h);
		button1.setSize(Vector2f(200*k_w, 100*k_h));

        	button2.setPosition((w/2-100)*k_w, (h/2+10)*k_h);
		button2.setSize(Vector2f(200*k_w, 100*k_h));

        	buttonBack.setPosition(20*k_w, 20*k_h);
		buttonBack.setSize(Vector2f(160*k_w, 80*k_h));

        	button11.setPosition((w/2-100)*k_w, (h/2-110)*k_h);
        	button12.setPosition((w/2-100)*k_w, (h/2+10)*k_h);
        	button21.setPosition((w/2-100)*k_w, (h/2-110)*k_h);
        	button22.setPosition((w/2-100)*k_w, (h/2+10)*k_h);

		button11.setSize(Vector2f(200*k_w, 100*k_h));
		button12.setSize(Vector2f(200*k_w, 100*k_h));
		button21.setSize(Vector2f(200*k_w, 100*k_h));
		button22.setSize(Vector2f(200*k_w, 100*k_h));

		button22G.setPosition((w/2-100)*k_w, (h/2-100)*k_h);
                button22M.setPosition((w/2)*k_w, (h/2-100)*k_h);
                button22K.setPosition((w/2-100)*k_w, (h/2)*k_h);
                button22B.setPosition((w/2)*k_w, (h/2)*k_h);

		button22G.setSize(Vector2f(80*k_w, 80*k_h));
                button22M.setSize(Vector2f(80*k_w, 80*k_h));
                button22K.setSize(Vector2f(80*k_w, 80*k_h));
                button22B.setSize(Vector2f(80*k_w, 80*k_h));

		text1.setPosition((w/2-95)*k_w, (h/2-95)*k_h);
		text1.setScale(k_w, k_h);
		
		text2.setPosition((w/2-98)*k_w, (h/2+25)*k_h);
                text2.setScale(k_w, k_h);
		
		textBack.setPosition(37*k_w, 25*k_h);
		textBack.setScale(k_w, k_h);
			
		text11.setPosition((w/2-70)*k_w, (h/2-95)*k_h);
		text12.setPosition((w/2-70)*k_w, (h/2+25)*k_h);
		text21.setPosition((w/2-70)*k_w, (h/2-95)*k_h);
		text22.setPosition((w/2-70)*k_w, (h/2+25)*k_h);

		text11.setScale(k_w, k_h);
		text12.setScale(k_w, k_h);
		text21.setScale(k_w, k_h);
		text22.setScale(k_w, k_h);
		
		text22G.setPosition((w/2-80)*k_w, (h/2-90)*k_h);
                text22M.setPosition((w/2+20)*k_w, (h/2-90)*k_h);
                text22K.setPosition((w/2-80)*k_w, (h/2+10)*k_h);
                text22B.setPosition((w/2+20)*k_w, (h/2+10)*k_h);

		text22G.setScale(k_w, k_h);
		text22M.setScale(k_w, k_h);
		text22K.setScale(k_w, k_h);
		text22B.setScale(k_w, k_h);

		if(status == "server_menu"){
			window.draw(button1);
                	window.draw(text1);
               	 	window.draw(button2);
                	window.draw(text2);
		}
		if(status == "server1"){
			window.draw(buttonBack);
			window.draw(textBack);
			window.draw(button11);
			window.draw(text11);
			window.draw(button12);
			window.draw(text12);

		}
		if(status == "server2"){
			window.draw(buttonBack);
			window.draw(textBack);
			window.draw(button21);
                        window.draw(text21);
                        window.draw(button22);
                        window.draw(text22);
		}
		if(status == "task4"){
			window.draw(buttonBack);
			window.draw(textBack);

			window.draw(button22G);
			window.draw(button22M);
			window.draw(button22K);
			window.draw(button22B);

			window.draw(text22G);
			window.draw(text22M);
			window.draw(text22K);
			window.draw(text22B);
		}
		window.display();
	}
	return 0;
}
