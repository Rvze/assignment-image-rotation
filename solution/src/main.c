#include <stdio.h>
#include "../include/bmp/bmp_reader.h"
#include "../include/file/file_io.h"
#include "../include/image_rotation/image_rotation.h"


#define ERROR  1


int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "%s", "Incorrect count of arguments");
        return ERROR;
    }
    printf("%s", "program started\n");
    struct image image;
    FILE *maybe_input_file = NULL;
    FILE *maybe_output_file = NULL;
    const char *input_file = argv[1];
    const char *output_file = argv[2];

    enum io_return_code code = open_file(&maybe_input_file, input_file, "r");
    fprintf(stderr, "%s\n", io_return_code_string[code]);
    if (code != OPEN_OK)
        return fprintf(stderr, "%s", io_return_code_string[code]);
    enum read_status read_status = from_bmp(maybe_input_file, &image);
    fprintf(stderr, "%s", read_status_string[read_status]);
    if (read_status != READ_OK) {
        fprintf(stderr, "%s", "Ошибка при конвертации в image");
        return ERROR;
    }
    struct image rotated = rotate_image(image);
    code = open_file(&maybe_output_file, output_file, "w");
    if (code != OPEN_OK)
        return OPEN_ERROR;
    enum write_status write_status = to_bmp(maybe_output_file, &rotated);
    if (write_status != WRITE_OK)
        return WRITE_ERROR;
    return 0;

}
