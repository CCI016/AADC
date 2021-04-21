#include <stdlib.h>
#include <stdio.h>

void swap(int i, int j, int arr[]) {
	int h = arr[i];
	arr[i] = arr[j];
	arr[j] = h;
}

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
			swap(left, right-1, arr);
		}
	}
	left--;
	arr[0] = arr[left];
	arr[left] = pivot;
	return left;
}

void quickSort(int length, int *arr) {
	if (length <= 1) {
		return;
	}
  int boundary = partition(length, arr);
	quickSort(boundary, arr);
	quickSort(length - boundary - 1, &arr[boundary + 1]);
}

void sort(int *A, int *B, int n) {
	quickSort(n, A);
	quickSort(n, B);
}

int main(int argc, char* argv[]) {
	int time, maximal = 1, openedMomentaly = 1, opening = 1, closing = 0;
	int n;

	scanf("%d", &n);
	
	if (n == 0) {
		printf("%d %d\n", 0, 0);
		return 0;
	}

	int openingDays[n], closeDays[n];
	for ( int i = 0; i < n; i++) {
		scanf("%d %d", &openingDays[i], &closeDays[i]);
	}
	sort(openingDays, closeDays, n);

 	time = openingDays[0];
	while (opening < n && closing < n) {
		if (openingDays[opening] <= closeDays[closing]) {
			openedMomentaly++;
			if (openedMomentaly > maximal) {
				time = openingDays[opening];
				maximal = openedMomentaly;
			}
			opening++;  
		} else {  
			openedMomentaly--;
			closing++;
		}
	}
	printf("%d %d\n", time, maximal);

	return 0;
}