#include <stdio.h>
#include <stdint.h>

#define Dysk1 "../../disks/RAID_4/dysk1.bin"
#define Dysk2 "../../disks/RAID_4/dysk2.bin"
#define Dysk3 "../../disks/RAID_4/dysk3.bin"

typedef uint32_t block;

block read_block(int address, FILE *ftpr){
    block buffer;
    if(fseek(ftpr, address*4, SEEK_SET) != 0){
        perror("blad fseek");
        fclose(ftpr);
        return 1;
    }
    if(fread(&buffer, sizeof(buffer),1,ftpr) != 1){
        printf("blad fread");
        fclose(ftpr);
        return -1;
    }
    return buffer;
}

void repair_block(block buffer, int address, FILE *ftpr){
    if(fseek(ftpr, address*4, SEEK_SET) != 0){
        perror("blad fseek");
        fclose(ftpr);
        return;
    }
    if(fwrite(&buffer, sizeof(buffer),1,ftpr) != 1){
        printf("blad fread");
        fclose(ftpr);
        return;
    }
}

int main(void){
    int dysk;
    printf("podaj dysk do naprawy: ");
    scanf("%d",&dysk);

    int address;
    printf("podaj adres do naprawy: ");
    scanf("%d",&address);

    block A;
    block B;
    block repair;

    FILE *ftpr1;
    FILE *ftpr2;
    FILE *ftprparity;

    ftpr1= fopen(Dysk1, "rb+");
    ftpr2= fopen(Dysk2, "rb+");
    ftprparity= fopen(Dysk3, "rb+");

    switch (dysk){
        case 1:    
            A = read_block(address,ftpr2);
            B = read_block(address,ftprparity);
            repair = A ^ B;
            
            repair_block(repair, address, ftpr1);

            break;
        case 2:
            A = read_block(address,ftpr1);
            B = read_block(address,ftprparity);
            repair = A ^ B;
            
            repair_block(repair, address, ftpr2);
            
            break;
        case 3:
            A = read_block(address,ftpr2);
            B = read_block(address,ftpr1);
            repair = A ^ B;
            
            repair_block(repair, address, ftprparity);
            
            break;
        default:
            break;
    }

    fclose(ftpr1);
    fclose(ftpr2);
    fclose(ftprparity);
    return 0;
}