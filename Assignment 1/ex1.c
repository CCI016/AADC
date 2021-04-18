#include <stdio.h>
#include <stdlib.h>

void showArray(int length, int arr[]) {
  printf("%d", arr[0]);
  for (int i=1; i < length; i++) {
    printf(",%d", arr[i]);
  }
  printf("\n");
}

int *copySubArray(int left, int right, int arr[]) {
  int i, *copy;
  copy = malloc((right - left)*sizeof(int));
  for (i=left; i < right; i++) {
    copy[i - left] = arr[i];
  }
  return copy;
}

void mergeSort(int length, int arr[]) {
  int l, r, mid, idx, *left, *right;
  if (length <= 1) {
    return;
  }
  mid = length/2;
  left = copySubArray(0, mid, arr);
  right = copySubArray(mid, length, arr);
  mergeSort(mid, left);
  mergeSort(length - mid, right);
  idx = 0;
  l = 0;
  r = 0;
  while ((l < mid) && (r < length - mid)) {
    if (left[l] < right[r]) {
      arr[idx] = left[l];
      l++;
    } else {
      arr[idx] = right[r];
      r++;
    }
    idx++;
  }
  while (l < mid) {
    arr[idx] = left[l];
    idx++;
    l++;
  }
  while (r < length - mid) {
    arr[idx] = right[r];
    idx++;
    r++;
  }
  free(left);
  free(right);
}

void findMaxNumbersOfShops(int start[], int end[], long int n) {
   int shopsInitial = 1, maxShops = 1, day = start[0];
   int i = 1, j = 0;
 
   while (i < n && j < n) {
      if (start[i] <= end[j]) {
          shopsInitial++;

          if (shopsInitial > maxShops) {
              maxShops = shopsInitial;
              day = start[i];
          }
          i++;  
      }
      else {    
          shopsInitial--;
          j++;
      }
   }
   printf("%d %d\n", day,maxShops);
}

int main(int argc, char* argv[]) {
  long int n;
	
	scanf("%ld", &n);

  if (n == 0) {
    printf("%d %d\n", 0, 0);
    return 0;
  }

	int start[n], end[n];

	for ( int i = 0; i < n; i++) {
		scanf("%d %d", &start[i], &end[i]);
	}

  mergeSort(n, start);
  mergeSort(n, end);

  findMaxNumbersOfShops(start, end, n);
}
