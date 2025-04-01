#include <stdio.h>
void swap(int *a, int *b) {

    int temp = *a;

    *a = *b;

    *b = temp;

}
int partition(int arr[], int low, int high) {

    int pivot = arr[low];

    int i = low + 1;

    int j = high;



    while (i <= j) {



        while (i <= high && arr[i] <= pivot)

            i++;



        while (arr[j] > pivot)

            j--;



        if (i < j)

            swap(&arr[i], &arr[j]);

    }

    swap(&arr[low], &arr[j]);

    return j;

}
void quickSort(int arr[], int low, int high) {

    if (low < high) {

        int pi = partition(arr, low, high);
       quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);

    }

}
void printArray(int arr[], int size) {

    for (int i = 0; i < size; i++)

        printf("%d ", arr[i]);

    printf("\n");

}
int main() {

    int arr[] = {19,32,18,24,30,12,28,14};

    int n = sizeof(arr) / sizeof(arr[0]);
    printf("Original array: ");
    printArray(arr, n);



    quickSort(arr, 0, n - 1);



    printf("Sorted array: ");

    printArray(arr, n);



    return 0;

}
