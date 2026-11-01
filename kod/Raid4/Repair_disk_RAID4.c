#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define Dysk1 "../../disks/RAID_4/dysk1.bin"
#define Dysk2 "../../disks/RAID_4/dysk2.bin"
#define Dysk3 "../../disks/RAID_4/dysk3.bin"

typedef uint32_t block;

struct disk{
    FILE *ftpr;
    bool was_damaged;
};

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

void repair_disk(FILE *ftpr_A,FILE *ftpr_B, FILE *ftpr_repair, long len){
    block buffer_A;
    block buffer_B;
    block buffer_wbyt;
    for(long i = 0; i < len/4; i++){
        buffer_A = read_block(i,ftpr_A);
        buffer_B = read_block(i, ftpr_B);

        buffer_wbyt = buffer_A ^ buffer_B;

        repair_block(buffer_wbyt, i,ftpr_repair);
    }
}

int main(void){

    block A;
    block B;
    block repair;

    struct disk ftpr1;
    struct disk ftpr2;
    struct disk ftprparity;

    long len;

    ftpr1.ftpr= fopen(Dysk1, "rb+");
    ftpr2.ftpr= fopen(Dysk2, "rb+");
    ftprparity.ftpr= fopen(Dysk3, "rb+");

    if(ftpr1.ftpr == NULL){
        ftpr1.ftpr= fopen(Dysk1, "wb");
        ftpr1.was_damaged = true;

        fseek(ftpr2.ftpr, 0, SEEK_END);
        len = ftell(ftpr2.ftpr);
    }
    if(ftpr2.ftpr == NULL){
        ftpr2.ftpr= fopen(Dysk2, "wb");
        ftpr2.was_damaged = true;

        fseek(ftpr1.ftpr, 0, SEEK_END);
        len = ftell(ftpr1.ftpr);
    }
    if(ftprparity.ftpr == NULL){
        ftprparity.ftpr= fopen(Dysk3, "wb");
        ftprparity.was_damaged = true;

        fseek(ftpr2.ftpr, 0, SEEK_END);
        len = ftell(ftpr2.ftpr);
    }

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