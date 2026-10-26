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
        input[--len] = '\0';
    }

    printf("Wczytano %zu bajtow\n", len);

    printf("%c\n",input[0]);

    for (size_t i = 0; i < len; i++) {
        for (int bit = 7; bit >= 0; bit--) {
            printf("%d", (input[i] >> bit) & 1);
        }

        printf(" ");
    }


    return 0;
}