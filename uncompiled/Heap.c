
#include <stdio.h>

void restoreHeap(int arr[], int length,int initialRoot) {
    int indexOfSmallest=initialRoot;
    int left=2*indexOfSmallest+1;
    int right=2*indexOfSmallest+2;
    if (left<length && arr[left] < arr[indexOfSmallest]) {
        indexOfSmallest = left;
    }
    if (right<length && arr[right] < arr[indexOfSmallest]) {
        indexOfSmallest = right;
    }//szukanie najmniejszego
    if (indexOfSmallest !=initialRoot) {
        int tmp = arr[initialRoot];
        arr[initialRoot] = arr[indexOfSmallest];
        arr[indexOfSmallest] = tmp;// jak był jakiś mniejszy to podmieniamy
        restoreHeap(arr, length, indexOfSmallest);//rekurencyjne wywoływanie
    }
}
void buildHeap(int arr[], int length) {
    for (int i=length/2-1;i>=0;i--) {
        restoreHeap(arr, length, i);//dla każdego nie liścia naprawamy stos
    }
}
void heapSort(int arr[], int length) {
    for (int i = length - 1; i > 0; i--) {//i robi za ostatni index nieprzesortowanej czesci i za to żeby wywołało się n razy
        int tmp = arr[0];
        arr[0] = arr[i];
        arr[i] = tmp;

        restoreHeap(arr, i, 0);
    }

}

int main() {
    int n;
    scanf("%d", &n);
    int arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    buildHeap(arr, n);
    heapSort(arr,n);
    //printf("Posortowana tablica:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
}