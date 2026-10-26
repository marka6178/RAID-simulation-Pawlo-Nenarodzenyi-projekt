#include <stdio.h>

#define Dysk1 "../../disks/RAID_1/dysk1.bin"
#define Dysk2 "../../disks/RAID_1/dysk2.bin"

int main(void){
    FILE *fptr;
    
    fptr = fopen(Dysk1, "w");
    fclose(fptr); 

    fptr = fopen(Dysk2, "w");
    fclose(fptr); 

    return 0;
}