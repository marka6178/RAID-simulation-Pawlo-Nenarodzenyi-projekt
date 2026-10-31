#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define Dysk1 "../../disks/RAID_4/dysk1.bin"
#define Dysk2 "../../disks/RAID_4/dysk2.bin"
#define Dysk3 "../../disks/RAID_4/dysk3.bin"


typedef uint32_t block;

block xor_block(block a, block b) {
    return a ^ b;
}

int main(void){
    unsigned char input[1024];
    printf("podaj dane (ilosc znakow krotna 8, prosze <3): ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 1;
    }

    size_t len = strlen(input);
    if (len > 0 && input[len - 1] == '\n') {
        input[--len] = '\0';                        //usuniecie \n 
    }

    if(len < 7){
        printf("za malo danych pidor");
        return 1;
    }

    FILE *ftpr1;
    FILE *ftpr2;
    FILE *ftprparity;

    ftpr1= fopen(Dysk1, "ab");
    ftpr2= fopen(Dysk2, "ab");
    ftprparity= fopen(Dysk3, "ab");

    if(ftpr1 == NULL || ftpr2 == NULL || ftprparity == NULL){
        printf("BLAD DYSKU");
        return 1;
    }

    block A;
    block B;
    block parity;
    for(int i = 0; i < len; i+=8){
        memcpy(&A,input + i,4);
        memcpy(&B,input + i + 4,4);

        parity = A ^ B;

        fwrite(&A,sizeof(A),1,ftpr1);
        fwrite(&B,sizeof(B),1,ftpr2);
        fwrite(&parity,sizeof(parity),1,ftprparity);
    }

    fclose(ftpr1);
    fclose(ftpr2);
    fclose(ftprparity);

    return 0;
}