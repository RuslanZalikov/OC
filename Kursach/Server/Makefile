server2: delete2 server1
	g++ server2.cpp -o server2
server1: delete1
	g++ server1.cpp -o server1
delete2:
	if test -f "server2"; then rm server2; fi
delete1:
	if test -f "server1"; then rm server1; fi

install:
	apt update && update-pciids
