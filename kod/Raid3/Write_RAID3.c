#include <stdio.h>

#define Dysk1 "../../disks/RAID_3/dysk1.bin"
#define Dysk2 "../../disks/RAID_3/dysk2.bin"

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

    FILE *fptr;
    
    fptr = fopen(Dysk1, "ab");
    fclose(fptr); 

    fptr = fopen(Dysk2, "ab");
    fclose(fptr); 

    return 0;
}