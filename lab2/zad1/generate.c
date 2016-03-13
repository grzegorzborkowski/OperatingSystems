#include "libs.h"

/*
 * Należy również napisać
 * program generujący plik z rekordami.
 * Program ten przyjmuje w argumentach: nazwę pliku do wygenerowania,
 * rozmiar pojedynczego rekordu i liczbę rekordów. Zawartość generowanych
 * rekordów powinna być losowa (można wykorzystać np. funkcję rand).
 */

int main(int argc, char **argv) {
    int file_descriptor;
    unsigned record_length, record_count;

    if (argc != 4) {
        printf("Unsupported number of arguments\n");
        exit(1);
    }

    file_descriptor = open(argv[1], O_WRONLY);
    if(file_descriptor == -1) {
        printf("Error while opening the file");
        exit(1) ;
    }

    record_length = (atol)(argv[2]);
    if(record_length == 0) {
        printf("Record length must be a number");
        exit(1);
    }

    record_count = (atol)(argv[3]);
    if(record_count == 0) {
        printf("Record count must be a number");
        exit(1);
    }
    return 0;
}