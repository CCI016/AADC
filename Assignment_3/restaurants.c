/* RESTAURANTS Assignment from the Challenges of Week 3 of AADS */
/* Done by : Constantin Cainarean s4142152 and Garabajiu Denis S4142551 */

#include <stdio.h>
#include <stdlib.h>

// Function to safely allocate memory.
void *safeMalloc(int n) {
	void *p = malloc(n);
	if (p == NULL) {
		printf("Error: malloc(%d) failed. Out of memory?\n", n);
		exit(EXIT_FAILURE);
	}
	return p;
}

// Function to swap two elements inside an array.
void swap(int i, int k, int arr[]) {
   int h = arr[i];
   arr[i] = arr[k];
   arr[k] = h;
}

// Below there is an implementation of Quick Sort algorith by Arnold Meijster, used in previous courses
int partition(int length, int arr[]) {
   int left = 0;
   int right = length;
   int pivot = arr[0];
   while (left < right) {
      while ((left < right) && (arr[left] <= pivot)) {
         left++;
      }
      while ((left < right) && (pivot < arr[right - 1])) {
         right--;
      }
      if (left < right) {
         swap(left, right - 1, arr);
      }
   }
   left--;
   arr[0] = arr[left];
   arr[left] = pivot;
   return left;
}

void quickSort(int length, int *arr) {
   if (length <= 1) {
      return; /* nothing to sort */
   }
   int boundary = partition(length, arr);
   quickSort(boundary, arr);
   quickSort(length - boundary - 1, &arr[boundary + 1]);
}

// This function is finding the median value from an array
int findMedian(int arr[], int size) {

    int median = 0;

   // In order to find the median, the array must be sorted
    quickSort(size, arr);

   // If we have odd number of elements, the median is the element from the middle of the array, ex : [1,2,3] the median will be 2.
    if (size % 2 != 0) {
        median = arr[(size / 2)];
    } else {
       // If we have even number of elements, the median is the value of two elements from the middle divided by 2
       // ex : [1,2,3,4] the median will be (2 + 3) / 2.
        median = (arr[size / 2] + arr[(size / 2) - 1]) / 2;
    }

    return median;
}


int main(int argc, char* argv[]) {
	
   int n, r, index = 0;
   //Scanning the size of city grid and the number of restaurants. (On the GRID 0 means no restaurant, and 1 means there's restaurant).
   scanf("%d %d", &n, &r);

   // Temporary variable to scan the input and check where there is a restaurant (value 1 on the grid).s
   int temp;

   // Two array's to store the X coordinate of all the restaurants, and Y coordinate respectively.
   int *pointX, *pointY, optimalX, optimalY;

   // Trying with dynamic memory.
   pointX = safeMalloc(r * sizeof(int));
   pointY = safeMalloc(r * sizeof(int));
 
   for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
         scanf("%d", &temp);
         if (temp == 1) {
            pointX[index] = i;
            pointY[index] = j;
            index++;
         }
      }
   }

   // To find the optimal position where Bob should stay, we compute the median from the X and median from Y coordinates of all the restaurants.
   optimalX = findMedian(pointX, r);
   optimalY = findMedian(pointY, r);

   // Freeing the dynamically allocated memory
   free(pointX);
   free(pointY);

   printf("%d %d\n", optimalX, optimalY);
	return 0;
}