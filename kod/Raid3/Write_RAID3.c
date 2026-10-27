#include <stdio.h>
#include <string.h>

#define Dysk1 "../../disks/RAID_3/dysk1.bin"
#define Dysk2 "../../disks/RAID_3/dysk2.bin"
#define Dysk3 "../../disks/RAID_3/dysk3.bin"

int main(void){
    char input[1024];

    printf("Podaj dane: ");

    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 1;
    }
  
    size_t len = strlen(input);
    if (len > 0 && input[len - 1] == '\n') {
        input[--len] = '\0';                        //usuniecie \n 
    }

    if(input[1] == NULL){
        perror("za malo danych pidor");
        return 1;
    }

    FILE *fptr1;
    FILE *fptr2; 
    FILE *fptr3; 

    fptr1 = fopen(Dysk1, "ab");
    fptr2 = fopen(Dysk2, "ab");
    fptr3 = fopen(Dysk3, "ab");

    for(size_t i=0; i<len; i++){
        if(i % 2 == 0){
            fwrite(&input[i], sizeof(input[i]), 1, fptr1);
        }
        else{
            fwrite(&input[i], sizeof(input[i]), 1, fptr2);
            char parity = input[i] ^ input[i-1];
            fwrite(&parity, sizeof(parity), 1, fptr3);
        }
    }
    
    fclose(fptr1); 
    fclose(fptr2);
    fclose(fptr3);


    return 0;
}