#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *getfield(char* line, int num);
char *getRecord(FILE *csvFile, int recordNo);

char* getfield(char* line, int num) {
    char* tok;
    for (tok = strtok(line, ";"); tok && *tok; tok = strtok(NULL, ";\n")) {
        if (!--num) {
            return tok;
        }
    }
    return NULL;
}

char *getRecord(FILE *csvFile, int recordNo) {
	char line[1024];
	int counter = 0;;
    while (fgets(line, 1024, csvFile)) {
        char* tmp = strdup(line);
        counter++;

        if(counter == recordNo) {
            return getfield(tmp, 2);
		}
    }

    return "none";
}

int main() {
    FILE* bead = fopen("csv/bead.csv", "r");

    /*char line[1024];
    while (fgets(line, 1024, bead)) {
        char* tmp = strdup(line);
        printf("Record %s\n\tField 2: %s\n\tline: %s\n---\n", tmp, getfield(tmp, 2), line); // field starts at 1 not at 0
        free(tmp);
    }*/
    printf("\nEnter a number [1-5] and press [enter]. : ");
    int myIndex = 0;
    scanf("%d", &myIndex);
    printf("you pressed %d\n", myIndex);

    printf("\nQuery Return: %s\n", getRecord(bead, myIndex));

}
