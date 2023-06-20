#include <stdio.h>
#include <unistd.h>

int main() {

	pid_t pid;
	for (int i=0; i<3; i++) {
		if(pid==0)
			pid = fork();
	}

	int cnt=0;
	
	while(1){
		if (pid == 0)
			printf("I'm parent\n");
		else
			printf("I'm child(%d)\n", pid);
		sleep(1);
		cnt++;
		if(cnt==5)
			break;


		
	}

	return 0;
}
