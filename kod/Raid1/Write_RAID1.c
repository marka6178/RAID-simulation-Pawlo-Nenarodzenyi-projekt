#include <stdio.h>

#define Dysk1 "../../disks/RAID_1/dysk1.bin"
#define Dysk2 "../../disks/RAID_1/dysk2.bin"

int main(void){
    int dane = 0;

    FILE *fptr;

    printf("podaj dane do zapisu: ");
    scanf("%d", &dane);
    printf("%d",dane);

    fptr = fopen(Dysk1, "a");
    fprintf(fptr, "%d", dane);
    fclose(fptr); 

    fptr = fopen(Dysk2, "a");
    fprintf(fptr, "%d", dane);
    fclose(fptr); 

    return 0;
}