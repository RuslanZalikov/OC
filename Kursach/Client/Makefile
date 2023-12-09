client: delete
	g++ client.cpp -o client

delete:
	if test -f "client"; then rm client; fi

install:
	apt update

client_gui: install_gui delete_gui compile_gui compose_gui
	if test -f "client_gui.o"; then rm client_gui.o; fi

compose_gui:
	g++ client_gui.o -o client_gui -lsfml-graphics -lsfml-window -lsfml-system

compile_gui:
	g++ -c client_gui.cpp

delete_gui:
	if test -f "client_gui"; then rm client_gui; fi

install_gui:
	sudo apt update && sudo apt-get install libsfml-dev
