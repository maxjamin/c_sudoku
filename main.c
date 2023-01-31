#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

#define BOARD_SIZE 81
#define MAX 100
#define BOARD_NAME_MAX_SIZE 100

struct sudoku_board {
	int data_values[BOARD_SIZE+1];
	char board_name[BOARD_NAME_MAX_SIZE];

};

typedef struct sudoku_board Board;

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

/*
    Each row contains unique values from 1-9.
    Each column contains unique values from 1-9.
    Each of the 9 sub-squares, of size 3x3, ​contains a unique value from 1-9.
*/

bool checkboard_for_rules(Board **gameboard)
{

	printf("\n");

	//Assuming board is size 9x9
	if(BOARD_SIZE == 81)
	{

		//checking 6*(3x3) sub squares

		//creating array to check for number of values of x type 1-9 starting at [0]
		//incr value at x place each time
		int unique_values [10] = {0};

		int base_incr = 0;
		int base_start_incr = 0;

		int base_start_incr_array[9] = {1, 4, 7, 28, 31, 34, 55, 58, 61};

		for (int k = 0; k < 9; k++)
		{
			base_start_incr = base_start_incr_array[k];
			printf("Base %d\n\n", base_start_incr);

			for(int i=base_start_incr; i<base_start_incr+9; i++)
			{

				printf("Value i:%d at %d: %d\n", i, (i-1)+base_incr,(*gameboard)->data_values[(i-1)+base_incr]);
				
				int temp_array_value = (*gameboard)->data_values[(i-1)+base_incr];

				unique_values[temp_array_value]++;

				if(i % 3 == 0)
					base_incr += 6;
			}

			//print out array of values
			for(int i=0; i<10; i++)
			{
				//!! Temp remove out 0 values from test!!
				if(i != 0 && unique_values[i] > 1)
				{
					printf("ERROR found two or more values of %d\n", i);
					return 1;
				}
				//printf("Number of unique_values for %d: %d\n", i, unique_values[i]);
			}
			memset(unique_values, 0, sizeof(unique_values));
			base_incr = 0;
		}
	}


}

int main()
{

	Board *game_board = board_init("New Game", "board1.txt");

	Display_board(&game_board);

	checkboard_for_rules(&game_board);
}