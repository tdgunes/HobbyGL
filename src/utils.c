//
// Created by Taha Doğan Güneş on 18/01/16.
//

#include <stdio.h>
#include <stdlib.h>
#include "utils.h"


const char *read_file(const char *file_name) {
    char *source = NULL;

    FILE *file = fopen(file_name, "r");
    if (file != NULL) {
        if (fseek(file, 0L, SEEK_END) == 0) {
            long buffer_size = ftell(file);
            if (buffer_size == -1) {
                fprintf(stderr, "Unable to get size of: %s\n", file_name);
            }

            source = malloc(sizeof(char) * (buffer_size + 1));

            if (fseek(file, 0L, SEEK_SET) != 0) {
                fprintf(stderr, "Unable to go back to start of the file: %s\n", file_name);
            }

            size_t length = fread(source, sizeof(char), buffer_size, file);
            if (!length) {
                fprintf(stderr, "Error reading file: %s\n", file_name);
            }
            else {
                source[length++] = '\0';
            }

        }
    }

    fclose(file);

    return source;
}
