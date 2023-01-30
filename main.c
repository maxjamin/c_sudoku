#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define BOARD_SIZE 81
#define MAX 100
#define BOARD_NAME_MAX_SIZE 100

struct sudoko_board {
	int data_values[BOARD_SIZE+1];
	char board_name[BOARD_NAME_MAX_SIZE];

};

typedef struct sudoko_board Board;

int Display_board(Board **gameboard)
{
	if((*gameboard)->board_name != NULL) {
		printf("Displaying board:%s\n", (*gameboard)->board_name);

		int j;
		for (j=0;j <= BOARD_SIZE-1;j++) {

			if((*gameboard)->data_values[j] != 0)
		    	printf("%d ",(*gameboard)->data_values[j]);
		    else
		    	printf("- ");

		    if((j+1)%9 == 0) {
				printf("\n");

				//print the horizontal lines, skip the line at the end
				if(((j+1)%27 == 0) && j < BOARD_SIZE-sqrt(BOARD_SIZE)) {
				printf("-");				
					for(int i=0; i < sqrt(BOARD_SIZE); i++)
						printf("--");
					printf("\n");
				}
			}
			if(((j+1)%3 == 0) && ((j+1)%9 != 0))
				printf("| ");
		}

	}
}


Board *board_init(char *board_name, char * file_name)
{
	Board *new_board = malloc(sizeof(Board));

	if(new_board)
	{
		//new_board->board_name = board_name;
		memcpy(new_board->board_name, board_name, sizeof(board_name));

		//load info from file to board_values
		FILE *fp;
		int file_array[MAX+1];

		file_array[MAX+1] = 0;
		size_t i = -1;
		char c;

		fp = fopen(file_name, "r");

		if(fp == NULL) {
			perror("Error opening file\n");
			return NULL;
		}
		else {
			while ( EOF != (c = fgetc( fp )) && ++i < MAX)
			{
				//printf("c:%d\n", c - '0');
            	file_array[ i ] = c - '0';
            	
            }
		}
		file_array[i] = 0;
		fclose(fp);

		/*int j;
		for (j=0;j < i && j < BOARD_NAME_MAX_SIZE;j++) {
		    printf("j: %d\n",file_array[j]);
		}*/

		if(i <= BOARD_SIZE) {
			memcpy(new_board->data_values, file_array, sizeof(int)*i);
		}
		else
			perror("Error file is two large\n");

		return new_board;
	}
	else
		return NULL;

}

int main()
{

	Board *game_board = board_init("New Game", "board1.txt");

	Display_board(&game_board);

}