#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* getfield(char* line, int num) {
    const char* tok;
    for (tok = strtok(line, ";"); tok && *tok; tok = strtok(NULL, ";\n")) {
        if (!--num) {
            return tok;
        }
    }
    return NULL;
}

int main() {
    FILE* bead = fopen("csv/bead.csv", "r");

    char line[1024];
    while (fgets(line, 1024, bead)) {
        char* tmp = strdup(line);
        printf("Record %s\n\tField 2: %s\n---\n", tmp, getfield(tmp, 2)); // field starts at 1 not at 0
        free(tmp);
    }
}
