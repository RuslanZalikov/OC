#include <stdio.h>
#include <unistd.h>
#include <sys/utsname.h>

char* getHostName(){
	int lenght = 256;
	char host_name[lenght];
	gethostname(host_name, lenght);
	char* start = &host_name[0];
	return start;
}


char* getLoginName(){
	int lenght = 256;
	char login_name[lenght];
	getlogin_r(login_name, lenght);
	char* start = &login_name[0];
	return start;
}

int main(){

	char* host_name = getHostName();
	char* login_name = getLoginName();
	printf("Host name: %s\n", host_name);
	printf("Login name: %s\n", login_name);
	struct utsname uts;
	uname(&uts);
	printf("%s", uts.version);
	return 0;

}
