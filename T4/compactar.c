/* HOMEWORK 4: FILES - CC3301
 * Student: Matías Vergara S.
 * Date: 31-10-2020
 * */

#include <stdio.h>

int main(int argc, char* argv[]) {
    FILE *fp;
    char buffer[20];

    /* Open file for both reading and writing */
    fp = fopen(argv[1], "r+");

    /* In case of problem opening file, raise error */
    if (fp == NULL) {
        perror("Error: ");
        return(-1);
    }

    int i = 0;
    int j = 0;

    fseek(fp, i*20, SEEK_SET);
    fread(buffer, sizeof(char), 20, fp);
    /* In case of success opening file, proceed to compact */
    while (!feof(fp)){

        char *p = buffer;

        /* While we read spaces, advance */
        while(*p == ' '){
            ++p;
        }

        /* Once we have read something different from space, check if it is a split line or end of string.
         * In this case, do stuff according to homework statement. */
        if (*p != '\n' && *p != '\0'){
            fseek(fp, j*20, SEEK_SET);
            fwrite(buffer, sizeof(char), 20, fp);
            j++;
        }
        /* If we did not found any character different from split line or end of string, we just advance to the next
         * line*/
        i++;
        fseek(fp, i*20, SEEK_SET);
        fread(buffer, sizeof(char), 20, fp);
    }

    /* Once we reach this point, we have reached the eof with i.
     * We proceed to fill with spaces until we reach the eof with j. */
    char* whiteline = "                   ";
    while(j<i){
        fseek(fp, j*20, SEEK_SET);
        fwrite(whiteline, sizeof(char), 19, fp);
        fwrite("\n", sizeof(char), 1, fp);
        j++;
    }
    fclose(fp);
    return 1;
}
