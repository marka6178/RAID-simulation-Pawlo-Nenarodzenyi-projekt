#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define Dysk1 "../../disks/RAID_5/dysk1.bin"
#define Dysk2 "../../disks/RAID_5/dysk2.bin"
#define Dysk3 "../../disks/RAID_5/dysk3.bin"
#define Dysk4 "../../disks/RAID_5/dysk4.bin"

typedef uint32_t block;

int main(void){
    unsigned char input[1024];
    printf("podaj dane (ilosc znakow krotna 12, prosze <3): ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 1;
    }

    size_t len = strlen(input);
    if (len > 0 && input[len - 1] == '\n') {
        input[--len] = '\0';                        //usuniecie \n 
    }

    if(len < 11){
        printf("za malo danych pidor");
        return 1;
    }

    FILE *ftpr1;
    FILE *ftpr2;
    FILE *ftpr3;
    FILE *ftpr4;

    ftpr1 = fopen(Dysk1, "ab");
    ftpr2 = fopen(Dysk2, "ab");
    ftpr3 = fopen(Dysk3, "ab");
    ftpr4 = fopen(Dysk4, "ab");

    if (ftpr1 == NULL || ftpr2 == NULL || ftpr3 == NULL || ftpr4 == NULL) {
        perror("Blad otwierania plikow");
        if (ftpr1) fclose(ftpr1);
        if (ftpr2) fclose(ftpr2);
        if (ftpr3) fclose(ftpr3);
        if (ftpr4) fclose(ftpr4);
        return 1;
    }

    block A;
    block B;
    block C;
    block P;

    int z = ftell(ftpr1)*3;
    for(int i = z;i < (len + z);i+=12){
        memcpy(&A,input + i - z,4);
        memcpy(&B,input + i + 4 - z,4);
        memcpy(&C,input + i + 8 - z,4);
        
        P = A ^ B ^ C;
        switch ((i / 12) % 4){
            case 0:
                fwrite(&A,sizeof(A),1,ftpr1);
                fwrite(&B,sizeof(B),1,ftpr2);
                fwrite(&C,sizeof(C),1,ftpr3);
                fwrite(&P,sizeof(P),1,ftpr4);
                break;
            case 1:
                fwrite(&A,sizeof(A),1,ftpr1);
                fwrite(&B,sizeof(B),1,ftpr2);
                fwrite(&P,sizeof(P),1,ftpr3);
                fwrite(&C,sizeof(C),1,ftpr4);
                break;
            case 2:
                fwrite(&A,sizeof(A),1,ftpr1);
                fwrite(&P,sizeof(P),1,ftpr2);
                fwrite(&B,sizeof(B),1,ftpr3);
                fwrite(&C,sizeof(C),1,ftpr4);
                break;
            case 3:
                fwrite(&P,sizeof(P),1,ftpr1);
                fwrite(&A,sizeof(A),1,ftpr2);
                fwrite(&B,sizeof(B),1,ftpr3);
                fwrite(&C,sizeof(C),1,ftpr4);
                break;
            default:
                break;
        }
    }

    fclose(ftpr1);
    fclose(ftpr2);
    fclose(ftpr3);
    fclose(ftpr4);
}