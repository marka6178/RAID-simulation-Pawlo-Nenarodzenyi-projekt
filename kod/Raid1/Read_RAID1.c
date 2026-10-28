#include <stdio.h>

#define Dysk1 "../../disks/RAID_1/dysk1.bin"
#define Dysk2 "../../disks/RAID_1/dysk2.bin"

int main(void){
    int bajt;
    char buffer[1];
    printf("podaj bajt który chcesz odczytac: ");
    scanf("%d", &bajt);

    FILE *fptr1;
    FILE *fptr2;

    fptr1 = fopen(Dysk1, "rb");
    fptr2 = fopen(Dysk2, "rb");
    if(fptr1 == NULL){
        perror("blad odczytu z dysku 1");

        if(fptr2 == NULL){
            perror("blad odczytu z dysku 1 i 2");
            return 1;
        }
        
        if (fseek(fptr2, bajt, SEEK_SET) != 0) {
            perror("Blad fseek");
            fclose(fptr2);
            return 1;
        }

        if (fread(buffer, sizeof(char), 1, fptr2) != 1) {
            printf("Nie udalo sie odczytac bajtu.\n");
            fclose(fptr2);
            return 1;
        }  
        fclose(fptr2);
    }
    else{
        if (fseek(fptr1, bajt, SEEK_SET) != 0) {
            perror("Blad fseek");
            fclose(fptr1);
            return 1;
        }

        if (fread(buffer, sizeof(char), 1, fptr1) != 1) {
            printf("Nie udalo sie odczytac bajtu.\n");
            fclose(fptr1);
            return 1;
        }  
        fclose(fptr1);
    }

    printf("%c\n", buffer[0]);

    return 0;
}