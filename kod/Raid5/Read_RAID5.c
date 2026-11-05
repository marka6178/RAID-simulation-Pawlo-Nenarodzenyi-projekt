#include <stdio.h>

#define Dysk1 "../../disks/RAID_5/dysk1.bin"
#define Dysk2 "../../disks/RAID_5/dysk2.bin"
#define Dysk3 "../../disks/RAID_5/dysk3.bin"
#define Dysk4 "../../disks/RAID_5/dysk4.bin"

char read_byt(int addsess, FILE *ftpr){
    char buffer;
    if(fseek(ftpr,(addsess%4)+(4*(addsess/12)),SEEK_SET) != 0){
        perror("clad fseek");
        return 1;
    }
    if(fread(&buffer, sizeof(buffer), 1, ftpr) != 1){
        printf("blad odczytu");
        return 1;
    }
    return buffer;
}

int main(void){
    int byt;
    printf("podaj bajt który chcesz odczytac: ");
    scanf("%d",&byt);

    char buffer;

    FILE *ftpr1;
    FILE *ftpr2;
    FILE *ftpr3;
    FILE *ftpr4;

    ftpr1 = fopen(Dysk1, "rb");
    ftpr2 = fopen(Dysk2, "rb");
    ftpr3 = fopen(Dysk3, "rb");
    ftpr4 = fopen(Dysk4, "rb");

    if (ftpr1 == NULL || ftpr2 == NULL || ftpr3 == NULL || ftpr4 == NULL) {
        perror("Blad otwierania plikow");
        if (ftpr1) fclose(ftpr1);
        if (ftpr2) fclose(ftpr2);
        if (ftpr3) fclose(ftpr3);
        if (ftpr4) fclose(ftpr4);
        return 1;
    }

    switch ((byt / 4) % 12) {
        case 0:
        case 3:
        case 6:
            buffer = read_byt(byt,ftpr1);
            break;
        case 1:
        case 4:
        case 9:
            buffer = read_byt(byt,ftpr2);
            break;
        case 2:
        case 7:
        case 10:
            buffer = read_byt(byt,ftpr3);
            break;
        case 5:
        case 8:
        case 11:
            buffer = read_byt(byt,ftpr4);
            break;
    }

    fclose(ftpr1);
    fclose(ftpr2);
    fclose(ftpr3);
    fclose(ftpr4);  

    printf("%c\n",buffer);

    return 0;
}