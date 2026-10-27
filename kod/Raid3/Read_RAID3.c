#include <stdio.h>

#define Dysk1 "../../disks/RAID_3/dysk1.bin"
#define Dysk2 "../../disks/RAID_3/dysk2.bin"
#define Dysk3 "../../disks/RAID_3/dysk3.bin"

int main(void){
    int bajt;
    printf("podaj bajt który chcesz odczytac: ");
    scanf("%d", &bajt);

    FILE *fptr1;                    //nieparzyste bajty
    FILE *fptr2;                    //parzyste bajty
    FILE *fptr3;                    //parity

    fptr1 = fopen(Dysk1, "rb");
    fptr2 = fopen(Dysk2, "rb");
    fptr3 = fopen(Dysk3, "rb");

    unsigned char buffer;
    unsigned char buffer_next_byt;
    unsigned char parity_byt;

    if (fptr1 == NULL || fptr2 == NULL || fptr3 == NULL) {
        perror("Blad otwierania plikow");

        if (fptr1 != NULL) fclose(fptr1);
        if (fptr2 != NULL) fclose(fptr2);
        if (fptr3 != NULL) fclose(fptr3);

        return 1;
    }

    if(bajt % 2 == 0){
        if (fseek(fptr1, bajt/2, SEEK_SET) != 0) {
            perror("Blad fseek");
            fclose(fptr1);
            return 1;
        }
        if (fread(&buffer, sizeof(char), 1, fptr1) != 1) {
            printf("Nie udalo sie odczytac bajtu.\n");
            fclose(fptr1);
            return 1;
        }

        //
        if (fseek(fptr2, bajt/2, SEEK_SET) != 0) {
            perror("Blad fseek");
            fclose(fptr2);
            return 1;
        }
         if (fread(&buffer_next_byt, sizeof(char), 1, fptr2) != 1) {
            printf("Nie udalo sie odczytac bajtu.\n");
            fclose(fptr2);
            return 1;
        }

        //
        if (fseek(fptr3, bajt/2, SEEK_SET) != 0) {
            perror("Blad fseek");
            fclose(fptr3);
            return 1;
        }
        if (fread(&parity_byt, sizeof(char), 1, fptr3) != 1) {
            printf("Nie udalo sie odczytac bajtu\n");
            fclose(fptr3);
            return 1;
        }
        if((buffer ^ buffer_next_byt) != parity_byt){
            printf("parity check faild, adres pamieci %d\n", bajt/2);
        }
    }
    else{
        if (fseek(fptr2, (bajt-1)/2, SEEK_SET) != 0) {
            perror("Blad fseek");
            fclose(fptr2);
            return 1;
        }
        if (fread(&buffer, sizeof(char), 1, fptr2) != 1) {
            printf("Nie udalo sie odczytac bajtu.\n");
            fclose(fptr2);
            return 1;
        }

        if (fseek(fptr1, (bajt-1)/2, SEEK_SET) != 0) {
            perror("Blad fseek");
            fclose(fptr1);
            return 1;
        }
        if (fread(&buffer_next_byt, sizeof(char), 1, fptr1) != 1) {
            printf("Nie udalo sie odczytac bajtu.\n");
            fclose(fptr1);
            return 1;
        }

        if (fseek(fptr3, (bajt-1)/2, SEEK_SET) != 0) {
            perror("Blad fseek");
            fclose(fptr3);
            return 1;
        }
        if (fread(&parity_byt, sizeof(char), 1, fptr3) != 1) {
            printf("Nie udalo sie odczytac bajtu.\n");
            fclose(fptr3);
            return 1;
        }
        if((buffer ^ buffer_next_byt) != parity_byt){
            printf("parity check faild, adres pamieci %d\n", bajt/2);
        }
    }

  
    fclose(fptr1);
    fclose(fptr2);
    fclose(fptr3);

    printf("%c\n", buffer);
    printf("%c\n", buffer_next_byt);

    return 0;
}