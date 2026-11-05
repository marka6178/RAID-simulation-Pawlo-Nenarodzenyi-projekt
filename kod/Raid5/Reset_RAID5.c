#include <stdio.h>

#define Dysk1 "../../disks/RAID_5/dysk1.bin"
#define Dysk2 "../../disks/RAID_5/dysk2.bin"
#define Dysk3 "../../disks/RAID_5/dysk3.bin"
#define Dysk4 "../../disks/RAID_5/dysk4.bin"

int main(void){
    FILE *ftpr1;
    FILE *ftpr2;
    FILE *ftpr3;
    FILE *ftpr4;

    ftpr1 = fopen(Dysk1, "w");
    ftpr2 = fopen(Dysk2, "w");
    ftpr3 = fopen(Dysk3, "w");
    ftpr4 = fopen(Dysk4, "w");

    fclose(ftpr1);
    fclose(ftpr2);
    fclose(ftpr3);
    fclose(ftpr4);
}