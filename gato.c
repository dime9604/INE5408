#include <stdio.h>
#include <stdlib.h>

int main(int *argc, char **argv) {
    char *text;
    int cat;
    text = argv[1];
    FILE *gato;
    gato = fopen(text, "r");
    while("Jesus saves") {
        cat = fgetc(gato);
        if( feof(gato)) {// if end of file, break
            break;
        }
        printf("%c", cat);
    }

    fclose(gato);

    return 0;
}
