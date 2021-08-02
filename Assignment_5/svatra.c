/* Svatra Assignment from the Challenges of Week 4 of AADS */
/* Done by : Constantin Cainarean s4142152 and Garabajiu Denis S4142551 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define PRIME 800077 // A relatively large prime number, that will be used as the size of the hash table.

//Function to safely allocate memory
void *safeMalloc(long int n) {
	void *a = malloc(n);
	if (a == NULL) {
		fprintf(stderr, "Fatal error: safeMalloc(%ld) failed.\n", n);
		exit(EXIT_FAILURE);
	}
	return a;
}

//Function to check if the two strings are equal
int isEqual(char *str1, char *str2) {
	if (strlen(str1) == strlen(str2)) { 
		for (int i = 0; i < strlen(str1); i++) {
			if (str1[i] != str2[i]) {
				return 0;
			}
		}
		return 1;
	}
	return 0;
}

struct HashTable {
    int value;
	// THe maximal length of the name, that will be stored as the key in the hash table is 50, 
	// and +1 character for string terminating char.
	char key[51];
    struct HashTable *succesor;
};

// Function used to initialize hash table with NULL values.
void initializeHashArray(struct HashTable **arr, int capacity) {
    for (int i = 0; i < capacity; i++) {
        arr[i] = NULL;
    }
}

// This function is used to insert a key (string) and a value corresponding to the key in the hash table.
void HashInsert(char *key, int value, struct HashTable **arr) {
    struct HashTable *link;
	link = safeMalloc(sizeof(struct HashTable));
	link->succesor = *arr;
    strcpy(link->key, key); // We copy from the string given in the parameters, to the key that will be inserted in hash table.
    link->value = value; // New value becomes the input value
    *arr = link;
}

// This function is used to search the key (string) in the hash table.
struct HashTable *HashSearch(char *key, struct HashTable *arr) {
    if(arr != NULL) { // If the hash table is not empty
        struct HashTable *element = arr;

        while (element != NULL) {
			// If the two strings are equal, return the element that we are searching for
            if (isEqual(key, element->key)) {
                return element;
            }
            element = element->succesor;
        }
    }
    return NULL; // if hashtable is null, return null directly.
}

// This function is used to free structure we are using.
void freeList(struct HashTable *hashedArray) {
	struct HashTable *destroy;
	while (hashedArray != NULL) {
		destroy = hashedArray;
		hashedArray = hashedArray->succesor;
		free(destroy);
	}
}

//This function is used to free the memory allocated for the hash table.
void hashFree(int n, struct HashTable **arr) {
	for (int i = 0; i < n; i++) {
	    if (arr[i] != NULL){ 
	        freeList(arr[i]);
	    }
	}
	free(arr);
}

// DJB2 hash function by Dan Bernstein.
// Reference : http://www.cse.yorku.ca/~oz/hash.html.
unsigned long generateHashCode(char *str) {
        unsigned long hash = 5381;
        int c;
        while ((c = *str++))
            hash = ((hash << 5) + hash) + c;
        return hash % PRIME;
}

//This function is used to compute input kilometers
void computeKilometers(struct HashTable **arr, char key[], int km) {
	// Transform the string into the hash code, to be able to find the key we are looking for.
	int index = generateHashCode(key);
	// Find the string inside the hash table.
	struct HashTable *link = HashSearch(key, arr[index]);

	if (link == NULL) {
	    HashInsert(key, km, &arr[index]); // If there was no such key before, add it to hash table.
	} else {
		// If the key was added before, it means the participant has scored additional kilometers,
		// Add kilometers to the previous value.
	    link->value += km;
	}

}

// Function to output the required result
void retrieveKMprogress(struct HashTable **arr, char key[]) {
	// Transform the string into the hash code, to be able to find the key we are looking for.
	int index = generateHashCode(key);
	// Find the string inside the hash table.
	struct HashTable *link = HashSearch(key, arr[index]);

	if (link == NULL){
	    printf("0\n"); // In the final stage, if there is no participant with the input name, we print 0 km for it.
	} else {
		// If there is a participant with the input name, we output his total kilometers made in the journey.
	    printf("%d\n", link->value);
	}
}

int main(int argc, char *argv[]) {
	int journeys, kilometers, queries;
	char names[51];
	struct HashTable **hashedArray;
	hashedArray = safeMalloc(PRIME * sizeof(struct HashTable *));

	initializeHashArray(hashedArray, PRIME);
	// We decided to skip the second integer that stands for the number of friends that take part in the journey
	// Since this integer is not affecting by any means our program.
	scanf("%d %*d", &journeys);

	while (journeys > 0) {
		scanf("%s %d", names, &kilometers);
		computeKilometers(hashedArray, names, kilometers);
		journeys--;
	}

	scanf("%d", &queries);

	while (queries > 0) {
		scanf("%s", names);
		retrieveKMprogress(hashedArray, names);
		queries--;
	}

	hashFree(PRIME, hashedArray);
	return 0;
}