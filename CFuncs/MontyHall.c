#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
	
	srand( time(NULL) );
	char options[3];
	int prize = rand()%3;
	int notPrize1 = (prize + 1)%3;
	int notPrize2 = (prize + 2)%3;
	int guess = 0;
	char changeDoor = 0;
	options[prize] = 1;
	options[notPrize1] = 0;
	options[notPrize2] = 0;

	printf("\n");
	printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
	printf(" Welcome to the Monty Hall Game\n");
	printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n");
	printf("Please Pick a Door(1-3). One has \n");
	printf("a car, the others have goats.\n");

	scanf("%d",&guess);
	guess = guess - 1;

	while(1){
		int temp = rand()%3;
		if((temp != prize) && (temp != guess)){
			printf("Door %d has a goat. Would you like to switch Doors? (y/n)\n",temp + 1);
			break;
		}
	}
	
	scanf(" %c", &changeDoor);

	if(((changeDoor == 'y') && (options[guess + 1] == 1)) || ((changeDoor == 'n') && (options[guess + 1] == 0))){
		printf("Ooh, you got a goat. Sorry :(\n");
	}
	else{ printf("YOU JUST WON A NEW CAR!\n");}

	return 0;
}
