/* WRITERS Assignment from the Challenges of Week 2 of AADS */
/* Done by : Constantin Cainarean s4142152 and Garabajiu Denis S4142551 */

#include <stdio.h>
#include <stdlib.h>

struct Writers {
  int identifier;
  int difficulty;
};

// Function that swaps two integer's inside an array. (Updated for struct array)
void swap(int i, int k, struct Writers arr[]) {
   struct Writers h = arr[i];
   arr[i] = arr[k];
   arr[k] = h;
}


// Below there is an implementation of Quick Sort algorithm by Arnold Meijster, used in previous courses.
int partition(int length, struct Writers arr[]) {
   int left = 0;
   int right = length;
   int indentifier = arr[0].identifier;
   int pivot = arr[0].difficulty;
   while (left < right) {
      while ((left < right) && (arr[left].difficulty <= pivot)) {
         left++;
      }
      while ((left < right) && (pivot < arr[right - 1].difficulty)) {
         right--;
      }
      if (left < right) {
         swap(left, right - 1, arr);
      }
   }
   left--;
   arr[0] = arr[left];
   arr[left].difficulty = pivot;
   arr[left].identifier = indentifier;
   return left;
}

void quickSort(int length, struct Writers *arr) {
   if (length <= 1) {
      return; /* nothing to sort */
   }
   int boundary = partition(length, arr);
   quickSort(boundary, arr);
   quickSort(length - boundary - 1, &arr[boundary + 1]);
}

// This function is the core of the Heap, arranges the elements in array.
void heapifyFunction(int node, int size, struct Writers heap[]) {
	
	int minHeap = node;
    int leftChild = 2 * node, rightChild = (2 * node) + 1;

   // This statement checks if the right child is smaller than its parent.
    if (rightChild < size && heap[rightChild].difficulty < heap[minHeap].difficulty)
      minHeap = rightChild;

    // This statement checks if left child is smaller than its parent.
    if (leftChild  < size && heap[leftChild].difficulty < heap[minHeap].difficulty)
      minHeap = leftChild ;

	// If the node which will be heapified is not a parent.
    if (minHeap != node) {
      swap(node, minHeap, heap);
      heapifyFunction(minHeap, size, heap);
    }
}

// Function to build a Min-Heap for the input array.
void minHeapFromArray(struct Writers heap[], int size) {
	for (int i = 0 ; i < size; i++) {
		heapifyFunction(i, size, heap);
	}
}


// This function is used to insert new entries of the assignments to the Heap structure we are using.
void insertMinHeap (struct Writers newWriter,struct Writers writers[], int size) {
	if (newWriter.difficulty > writers[0].difficulty) {
		writers[0] = newWriter;
		heapifyFunction(0, size, writers);
	}
}


// This function is responsible of scanning the rest of the input, forming from it a min-heap, 
// Afterwards sorting, and printing in descending order the assignments ranked by the difficulty.
void findAssignments(struct Writers writers[], int m, int n) {
	struct Writers newWriter;

	for (int i = m; i < n; i++) {
		scanf("%d %d", &newWriter.identifier, &newWriter.difficulty);
		insertMinHeap(newWriter,writers,m);
	}

  // We have decided to use quickSort algorithm as after the observations from the Assignment 1 it is faster than mergeSort.
  quickSort(m, writers);

  for (int i = m - 1; i >= 0; i--) {
    printf("%d %d\n", writers[i].identifier, writers[i].difficulty);
  }
}

int main(int argc, char* argv[]) {
	
	// We are scanning the input of the number of the assignments, and in how many are we interested
	int n, m;
	scanf("%d %d", &n, &m);

	// To keep the memory complexity O(m) we have decided to use structs, cause we have two types of data we classified it into
	// Assignment identifier (which is the number ID of the assignment) and it's difficulty.
  	struct Writers writers[m];

	// Scanning only m integers.
	for (int i = 0; i < m; i++) {
		scanf("%d %d", &writers[i].identifier, &writers[i].difficulty);
	}
     
	// Making use of the Min Heap Data Structures, as explained in the lectures.
	minHeapFromArray(writers, m);
	findAssignments(writers, m ,n);
	return 0;
}