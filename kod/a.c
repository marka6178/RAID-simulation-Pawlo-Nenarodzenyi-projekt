#include <stdio.h>
#include <string.h>

int main(void)
{
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

    
    return 0;
}