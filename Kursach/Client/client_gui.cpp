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
	int server;
	int w = 640, h = 480;

	RenderWindow window;
	window.create(VideoMode(w, h), L"OKHO", Style::Default);
	window.setVerticalSyncEnabled(false);

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



	std::string status = "server_menu";

	while(window.isOpen()){
		Vector2i mousePoz = Mouse::getPosition(window);

		Event event;
		while(window.pollEvent(event)){
			if(event.type == Event::Closed){
				window.close();
			}

			if(event.type == Event::MouseButtonPressed){
				if(event.mouseButton.button == Mouse::Left){
					if(button1.getGlobalBounds().contains(mousePoz.x, mousePoz.y) && status == "server_menu"){
						std::cout << "server1" << std::endl;
						button1.setFillColor(Color(80, 80, 80));
						text1.setFillColor(Color(30, 30, 30));

						server = createServer();

        					struct sockaddr_in address_server = createAddress();

        					Connect(server, address_server);
					}
					if(button2.getGlobalBounds().contains(mousePoz.x, mousePoz.y) && status == "server_menu"){
                                                std::cout << "server2" << std::endl;
						button2.setFillColor(Color(80, 80, 80));
                                                text2.setFillColor(Color(30, 30, 30));
                                        }
					if(buttonBack.getGlobalBounds().contains(mousePoz.x, mousePoz.y) && status != "server_menu"){
						std::cout << "back to menu" << std::endl;
						buttonBack.setFillColor(Color(80, 80, 80));
                                                textBack.setFillColor(Color(30, 30, 30));

						string msg_s = "stop";
						Send(server, msg_s);
					}
					if(button11.getGlobalBounds().contains(mousePoz.x, mousePoz.y) && status == "server1"){
                                                std::cout << "task1" << std::endl;
                                                button11.setFillColor(Color(80, 80, 80));
                                                text11.setFillColor(Color(30, 30, 30));

						string msg_s = "videocard";
                                                Send(server, msg_s);
                                                int size = 0;

                                                int resp = recv(server, &size, sizeof(int), 0);
                                                if (resp <= 0){
                                                        break;
                                                }

                                                char msg[size];
                                                recv(server, &msg, size, 0);
                                                cout << msg << endl;
                                        }
					if(button12.getGlobalBounds().contains(mousePoz.x, mousePoz.y) && status == "server1"){
                                                std::cout << "task2" << std::endl;
                                                button12.setFillColor(Color(80, 80, 80));
                                                text12.setFillColor(Color(30, 30, 30));
                                        }
					if(button21.getGlobalBounds().contains(mousePoz.x, mousePoz.y) && status == "server2"){
                                                std::cout << "task3" << std::endl;
                                                button21.setFillColor(Color(80, 80, 80));
                                                text21.setFillColor(Color(30, 30, 30));
                                        }
					if(button22.getGlobalBounds().contains(mousePoz.x, mousePoz.y) && status == "server2"){
                                                std::cout << "task4" << std::endl;
                                                button22.setFillColor(Color(80, 80, 80));
                                                text22.setFillColor(Color(30, 30, 30));
                                        }



				}
			}
			if(event.type == Event::MouseButtonReleased){
                                if(event.mouseButton.button == Mouse::Left){
                                        if(button1.getGlobalBounds().contains(mousePoz.x, mousePoz.y) && status == "server_menu"){
                                                button1.setFillColor(Color(100, 100, 100));
                                                text1.setFillColor(Color(50, 50, 50));
						status = "server1";
                                        }
                                        if(button2.getGlobalBounds().contains(mousePoz.x, mousePoz.y) && status == "server_menu"){
                                                button2.setFillColor(Color(100, 100, 100));
                                                text2.setFillColor(Color(50, 50, 50));
						status = "server2";
                                        }
					if(buttonBack.getGlobalBounds().contains(mousePoz.x, mousePoz.y) && status != "server_menu"){
                                                buttonBack.setFillColor(Color(100, 100, 100));
                                                textBack.setFillColor(Color(50, 50, 50));
						status = "server_menu";
                                        }
					if(button11.getGlobalBounds().contains(mousePoz.x, mousePoz.y) && status == "server1"){
                                                button11.setFillColor(Color(100, 100, 100));
                                                text11.setFillColor(Color(50, 50, 50));
                                        }
					if(button12.getGlobalBounds().contains(mousePoz.x, mousePoz.y) && status == "server1"){
                                                button12.setFillColor(Color(100, 100, 100));
                                                text12.setFillColor(Color(50, 50, 50));
                                        }
					if(button21.getGlobalBounds().contains(mousePoz.x, mousePoz.y) && status == "server2"){
                                                button21.setFillColor(Color(100, 100, 100));
                                                text21.setFillColor(Color(50, 50, 50));
                                        }
					if(button22.getGlobalBounds().contains(mousePoz.x, mousePoz.y) && status == "server2"){
                                                button22.setFillColor(Color(100, 100, 100));
                                                text22.setFillColor(Color(50, 50, 50));
                                        }

                                }
                        }
		}
		window.clear(Color(255, 255, 255));
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
		window.display();
	}
	return 0;
}
