#include <stdio.h>

#define Dysk1 "../../disks/RAID_3/dysk1.bin"
#define Dysk2 "../../disks/RAID_3/dysk2.bin"
#define Dysk3 "../../disks/RAID_3/dysk3.bin"

int main(void){
    int dysk;
    int adress;
    printf("podaj bledny dysk:");
    scanf("%d",&dysk);
    
    printf("podaj bledny adres:");
    scanf("%d",&adress);

    FILE *fptr1;
    FILE *fptr2;
    FILE *fptrparity;

    fptr1 = fopen(Dysk1, "rb+");
    fptr2 = fopen(Dysk2, "rb+");
    fptrparity = fopen(Dysk3, "rb+");

    unsigned char A;
    unsigned char B;
    unsigned char new_byt;

    switch (dysk){
        case 1:
            if (fseek(fptr2, adress, SEEK_SET) != 0) {
                perror("Blad fseek");
                fclose(fptr2);
                return 1;
            }
            if (fseek(fptrparity, adress, SEEK_SET) != 0) {
                perror("Blad fseek");
                fclose(fptrparity);
                return 1;
            }

            if (fread(&A, sizeof(char), 1, fptr2) != 1) {
                printf("Nie udalo sie odczytac bajtu\n");
                fclose(fptr2);
                return 1;
            }
            if (fread(&B, sizeof(char), 1, fptrparity) != 1) {
                printf("Nie udalo sie odczytac bajtu\n");
                fclose(fptrparity);
                return 1;
            }

            new_byt = A ^ B;

            if (fseek(fptr1, adress, SEEK_SET) != 0) {
                perror("Blad fseek");
                fclose(fptr1);
                return 1;
            }
            if (fwrite(&new_byt, sizeof(unsigned char), 1, fptr1) != 1) {
                perror("Blad zapisu");
                fclose(fptr1);
                return 1;
            }
            break;
        case 2:
            if (fseek(fptr1, adress, SEEK_SET) != 0) {
                perror("Blad fseek");
                fclose(fptr1);
                return 1;
            }
            if (fseek(fptrparity, adress, SEEK_SET) != 0) {
                perror("Blad fseek");
                fclose(fptrparity);
                return 1;
            }

            if (fread(&A, sizeof(char), 1, fptr1) != 1) {
                printf("Nie udalo sie odczytac bajtu\n");
                fclose(fptr1);
                return 1;
            }
            if (fread(&B, sizeof(char), 1, fptrparity) != 1) {
                printf("Nie udalo sie odczytac bajtu\n");
                fclose(fptrparity);
                return 1;
            }

            new_byt = A ^ B;

            if (fseek(fptr2, adress, SEEK_SET) != 0) {
                perror("Blad fseek");
                fclose(fptr2);
                return 1;
            }
            if (fwrite(&new_byt, sizeof(unsigned char), 1, fptr2) != 1) {
                perror("Blad zapisu");
                fclose(fptr2);
                return 1;
            }
            break;
        case 3:
            if (fseek(fptr2, adress, SEEK_SET) != 0) {
                perror("Blad fseek");
                fclose(fptr2);
                return 1;
            }
            if (fseek(fptr1, adress, SEEK_SET) != 0) {
                perror("Blad fseek");
                fclose(fptr1);
                return 1;
            }

            if (fread(&A, sizeof(char), 1, fptr2) != 1) {
                printf("Nie udalo sie odczytac bajtu\n");
                fclose(fptr2);
                return 1;
            }
            if (fread(&B, sizeof(char), 1, fptr1) != 1) {
                printf("Nie udalo sie odczytac bajtu\n");
                fclose(fptr1);
                return 1;
            }

            new_byt = A ^ B;

            if (fseek(fptrparity, adress, SEEK_SET) != 0) {
                perror("Blad fseek");
                fclose(fptrparity);
                return 1;
            }
            if (fwrite(&new_byt, sizeof(unsigned char), 1, fptrparity) != 1) {
                perror("Blad zapisu");
                fclose(fptrparity);
                return 1;
            }
            break;
        default:
            printf("zly numer dysku");
            break;
    }
      
    fclose(fptr1);
    fclose(fptr2);
    fclose(fptrparity);


    return 0;
}