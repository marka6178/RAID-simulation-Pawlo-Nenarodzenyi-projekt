#include <stdio.h>
#include <string.h>

#define Dysk1 "../../disks/RAID_1/dysk1.bin"
#define Dysk2 "../../disks/RAID_1/dysk2.bin"

int main(void){
    
    char input[1024];

    printf("Podaj dane: ");

    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 1;
    }
    size_t len = strlen(input);
    if (len > 0 && input[len - 1] == '\n') {
        input[--len] = '\0';                        //usuniecie /n 
    }

    FILE *fptr;

    fptr = fopen(Dysk1, "ab");
    for (size_t i = 0; i < len; i++) {
        fwrite(&input[i], sizeof(input[i]), 1, fptr);
    }

    fptr = fopen(Dysk2, "ab");
    for (size_t i = 0; i < len; i++) {
        fwrite(&input[i], sizeof(input[i]), 1, fptr);    
    }  
    fclose(fptr); 

    return 0;
}