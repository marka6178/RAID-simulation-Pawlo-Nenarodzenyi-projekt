#include <stdio.h>

#define Dysk1 "../../disks/RAID_1/dysk1.bin"
#define Dysk2 "../../disks/RAID_1/dysk2.bin"
#define Dysk_logiczny "../../disks/RAID_1/logiczny_dysk.bin"

int main(void){
    FILE *fptr;

    fptr = fopen(Dysk1, "a");
    fclose(fptr);

    fptr = fopen(Dysk2, "a");
    fclose(fptr);

    fptr = fopen(Dysk_logiczny, "a");
    fclose(fptr);

    return 0;
}