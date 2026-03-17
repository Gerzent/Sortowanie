#include <stdio.h>
#include <math.h>
long long comparisons=0;
long long swaps=0;
void Shell(int arr[], int n) {
    int przyrost=1,kMax=1;
    while (przyrost<n) {
        przyrost=(pow(3,kMax)-1)/2;
        kMax++;
    }
    if (przyrost>=n) {
        przyrost=(pow(3,kMax--)-1)/2;
    }//uzyskiwanie maksymalnego dla nas przyrostu
    while (przyrost>0) {

        for (int i=przyrost;i<n;i++) {
            int key=arr[i];
            int j=i;

            while (j >= przyrost) {
                comparisons++;
                if (arr[j - przyrost]<key) {
                    swaps++;
                    arr[j]=arr[j-przyrost];
                    j-=przyrost;
                }else {
                    break;
                }
            }
            swaps++;
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
    printf("Posortowana tablica:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    printf("Liczba prównań: %lld \n",comparisons);
    printf("Liczba zamian: %lld \n",swaps);
    return 0;
}
