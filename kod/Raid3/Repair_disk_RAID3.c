#include <stdio.h>
#include <stdbool.h>

#define Dysk1 "../../disks/RAID_3/dysk1.bin"
#define Dysk2 "../../disks/RAID_3/dysk2.bin"
#define Dysk3 "../../disks/RAID_3/dysk3.bin"

void repair_byt(FILE *fptr,int adress,unsigned char byt){
    if (fseek(fptr, adress, SEEK_SET) != 0) {
        perror("Blad fseek");
        fclose(fptr);
        return;
    }
    if (fwrite(&byt, sizeof(unsigned char), 1, fptr) != 1) {
        perror("Blad zapisu");
        fclose(fptr);
        return;
    }
}

unsigned char read_byt(FILE *fptr,long adress,unsigned char *buffer){
    if (fseek(fptr, adress, SEEK_SET) != 0) {
        perror("Blad fseek");
        fclose(fptr);
        return 0;
    }
    if (fread(buffer, sizeof(unsigned char), 1, fptr) != 1) {
        perror("Blad odczytu");
        fclose(fptr);
        return 0;
    }
    return *buffer;
}

void repair_disk(FILE *ftpr_A,FILE *ftpr_B, FILE *ftpr_repair, long len){
    unsigned char buffer_A;
    unsigned char buffer_B;
    unsigned char buffer_wbyt;
    for(long i = 0; i < len; i++){
        read_byt(ftpr_A, i, &buffer_A);
        printf("%c\n",buffer_A);
        read_byt(ftpr_B, i, &buffer_B);
        printf("%c\n",buffer_B);

        buffer_wbyt = buffer_A ^ buffer_B;

        printf("%c\n",buffer_wbyt);
        repair_byt(ftpr_repair, i, buffer_wbyt);
    }
}

struct Dysk{
    FILE *ftpr;
    bool was_damaged;
};


int main(void){

    struct Dysk ftpr1;
    struct Dysk ftpr2;
    struct Dysk ftprparity;

    long len;
    ftpr1.ftpr = fopen(Dysk1, "rb+");
    ftpr2.ftpr = fopen(Dysk2, "rb+");
    ftprparity.ftpr = fopen(Dysk3, "rb+");

    if(ftpr1.ftpr == NULL){
        ftpr1.was_damaged = true;
        ftpr1.ftpr = fopen(Dysk1, "wb");

        fseek(ftpr2.ftpr, 0, SEEK_END);
        len = ftell(ftpr2.ftpr);
    }

    else if(ftpr2.ftpr == NULL){
        ftpr2.ftpr = fopen(Dysk2, "wb");
        ftpr2.was_damaged = true;
        fseek(ftpr1.ftpr, 0, SEEK_END);
        len = ftell(ftpr1.ftpr);
    }

    else if(ftprparity.ftpr == NULL){
        ftprparity.ftpr = fopen(Dysk3, "wb");
        ftprparity.was_damaged = true;
        fseek(ftpr1.ftpr, 0, SEEK_END);
        len = ftell(ftpr1.ftpr);
    }

    else{
        return 0;
    }

    printf("%l", len);
    if(ftpr1.was_damaged){
        repair_disk(ftprparity.ftpr, ftpr2.ftpr, ftpr1.ftpr, len);
    }
    else if(ftpr2.was_damaged){
        repair_disk(ftprparity.ftpr, ftpr1.ftpr, ftpr2.ftpr, len);
    }
    else if(ftprparity.was_damaged){
        repair_disk(ftpr1.ftpr, ftpr2.ftpr, ftprparity.ftpr, len);
    }


    fclose(ftpr1.ftpr);
    fclose(ftpr2.ftpr);
    fclose(ftprparity.ftpr);

    return 0;
}