#include <stdio.h>
#include <string.h>

#define Dysk1 "../../disks/RAID_4/dysk1.bin"
#define Dysk2 "../../disks/RAID_4/dysk2.bin"
#define Dysk3 "../../disks/RAID_4/dysk3.bin"

int main(void){

    FILE *ftpr1;
    FILE *ftpr2;
    FILE *ftprparity;

    ftpr1= fopen(Dysk1, "w");
    ftpr2= fopen(Dysk2, "w");
    ftprparity= fopen(Dysk3, "w");

    fclose(ftpr1);
    fclose(ftpr2);
    fclose(ftprparity);

    return 0;
}