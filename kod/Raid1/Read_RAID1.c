#include <stdio.h>

#define Dysk1 "../../disks/RAID_1/dysk1.bin"
#define Dysk2 "../../disks/RAID_1/dysk2.bin"

int main(void){
    int bajt;
    char buffer[1];
    printf("podaj bajt który chcesz odczytac: ");
    scanf("%d", &bajt);

    FILE *fptr;

    fptr = fopen(Dysk1, "rb");
    if(fptr == NULL){
        perror("blad odczytu z dysku 1");

        fptr = fopen(Dysk2, "rb");
        
        if(fptr == NULL){
            perror("blad odczytu z dysku 1 i 2");
            return 1;
        }
        
        if (fseek(fptr, bajt, SEEK_SET) != 0) {
            perror("Blad fseek");
            fclose(fptr);
            return 1;
        }

        if (fread(buffer, sizeof(char), 1, fptr) != 1) {
            printf("Nie udalo sie odczytac bajtu.\n");
            fclose(fptr);
            return 1;
        }  
        fclose(fptr);
    }
    else{
        if (fseek(fptr, bajt, SEEK_SET) != 0) {
            perror("Blad fseek");
            fclose(fptr);
            return 1;
        }

        if (fread(buffer, sizeof(char), 1, fptr) != 1) {
            printf("Nie udalo sie odczytac bajtu.\n");
            fclose(fptr);
            return 1;
        }  
        fclose(fptr);
    }

    printf("%c\n", buffer[0]);

    return 0;
}