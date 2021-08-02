/* ARREST Assignment from the Challenges of Week 6 of AADS */
/* Done by : Constantin Cainarean s4142152 and Garabajiu Denis S4142551 */

#include <stdio.h>
#include <stdlib.h>


// Since we are dealing with a 2-dimensional grid, we will always have an array of the size NxN.
// We decided to use a single global variable to denote the size of the grid, 
// in order to make the code more readable, and without repetitions.
int GRID_SIZE;


// Function to safely allocate memory.
void *safeMalloc(int size) {
	void *p = malloc(size);
	if (p == NULL) {
		printf("Error: malloc(%d) failed. Out of memory?\n", size);
		exit(EXIT_FAILURE);
	}
	return p;
}

// Function to scan characters into 2D array and count the number of protesters.
void scan2DArray(char **arr, int *counter) {
    getchar();
    for (int row = 0; row < GRID_SIZE; row++) {
        for (int column = 0; column < GRID_SIZE; column++) {
            arr[row][column] = getchar();
            // In order to skip the terminating character at the end of the line
            if (column == GRID_SIZE - 1) {
                getchar();
            }
            if (arr[row][column] == '-') {
                (*counter)++; // First of all we get the total number of all protesters
            }
        }
    }
}

//Function to dynamically allocate memory for the 2D array. Simmilar function to the one's used in course impprog by A.Meijster.
char **make2DArray(int size) {
    char **arr;
    arr = safeMalloc(size * sizeof(char *));
        for(int row = 0; row < size; row++) {
            arr[row] = safeMalloc(size * sizeof(char));
        }
    return arr;
}

// Recursive function based on the principle of Flood Fill algorithm
// We have approached the problem from another side, 
// we count the number of protesters that aren't in the risk of getting arested,
// and out of total number of protesters we subtract the counted ammount.
void floodFillFunc(int x, int y, char **arr, int *counter) {

    // Base case 1: if we do not exceed the grid bound limit
    if (x < 0 || x >= GRID_SIZE || y < 0 || y >= GRID_SIZE ) {
        return;
    }

    // Following base case: in order to fill correctly with "officers".
    if(arr[x][y] == '*') {
		return;
	}

    arr[x][y] = '*';
    // From the previously accumulated total number of proters, we subtract the one's that can't be arrested.
    (*counter)--;

    floodFillFunc(x + 1, y, arr, counter);
    floodFillFunc(x, y + 1, arr, counter);
    floodFillFunc(x - 1, y, arr, counter);
    floodFillFunc(x, y - 1, arr, counter);
    return;
}

//Function used to "flood fill" the edges of the grid
// We fill the grid with '*' characters, that denote police officers, on the edges,
// this means that the surrounded areas aren't touched, so we count & fill only the protesters
// that can't be arrested.
void fillTheEdges(char **arr, int *counter) {

    //Loop to fill the left part
    for (int i = 0; i < GRID_SIZE; i++) {
        floodFillFunc(0, i, arr, counter);
    }
    // Loop to fill the right part
    for (int j = 0; j < GRID_SIZE; j++ ) {
        floodFillFunc((GRID_SIZE - 1), j, arr, counter);
    }

    // Loop to fill the upper line of the grid
    for (int k = 0; k < GRID_SIZE; k++ ) {
        floodFillFunc(k, 0, arr, counter);
    }
    // Loop to fill the lower line
    for (int l = 0; l < GRID_SIZE; l++ ) {
        floodFillFunc(l, (GRID_SIZE - 1), arr, counter);
    }
}

int main(int argc, char* argv[]) {
    int counter = 0;
    char **protestGrid;

    //Scanning the size of the grid in the global variable.
    scanf("%d", &GRID_SIZE);
    protestGrid = make2DArray(GRID_SIZE);

    scan2DArray(protestGrid, &counter);
    fillTheEdges(protestGrid, &counter);

    printf("%d\n", counter);

    for (int i = 0; i < GRID_SIZE; i++) {
        free(protestGrid[i]);
    }
    free(protestGrid);
    return 0;
}