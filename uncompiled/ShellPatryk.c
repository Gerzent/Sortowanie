#include <stdio.h>
#include <math.h>
void Shell(int arr[], int n) {
    int przyrost=1,kMax=1;
    while (przyrost<n) {
        przyrost=(pow(3,kMax)-1)/2;
        kMax++;
    }
    if (przyrost>=n) {
        przyrost=(pow(3,kMax--)-1)/2;
    }
    while (przyrost>0) {

        for (int i=przyrost;i<n;i++) {
            int key=arr[i];
            int j=i;
            while (j >= przyrost && arr[j - przyrost]<key) {
                arr[j]=arr[j-przyrost];
                j-=przyrost;
            }
            arr[j]=key;

        }
        przyrost=(pow(3,kMax--)-1)/2;

    }
    }

int main() {
    int n=10;
    scanf("%d", &n);
    int arr[n];//={68,2,89,3,100,5,6,8,4,101};
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    Shell(arr, n);
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
}
