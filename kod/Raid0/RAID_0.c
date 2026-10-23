#include <stdio.h>

int main(void){
    int dane = 0;

    FILE *fptr;

    printf("podaj dane do zapisu: ");
    scanf("%d", &dane);
    printf("%d",dane);

    fptr = fopen("../disks/RAID_0/filename.bin", "a");

    fprintf(fptr, "%d", dane);

    fclose(fptr); 
    return 0;
}