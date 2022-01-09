#include "../include/bmp/bmp_reader_writer.h"
#include "../include/file/file_io.h"
#include "../include/image_rotation/image_rotation.h"
#include <stdio.h>

#define ERROR  1

static void log(const char *message);

static void stderr_log(const char *message);

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "%s", "Incorrect count of arguments");
        return ERROR;
    }
    printf("%s", "program started\n");
    struct image image = {0};
    FILE *maybe_input_file = NULL;
    FILE *maybe_output_file = NULL;
    const char *input_file = argv[1];
    const char *output_file = argv[2];

    enum io_return_code code = open_file(&maybe_input_file, input_file, "r");
    log(io_return_code_string[code]);
    if (code != OPEN_OK)
        stderr_log(io_return_code_string[code]);

    enum read_status read_status = from_bmp(maybe_input_file, &image);
    if (read_status != READ_OK) {
        stderr_log(read_status_string[read_status]);
        close_file(maybe_input_file);
    }
    enum io_return_code closed = close_file(maybe_input_file);
    log(io_return_code_string[closed]);

    struct image rotated = rotate_image(image);
    code = open_file(&maybe_output_file, output_file, "w");

    log(io_return_code_string[code]);

    if (code != OPEN_OK)
        return OPEN_ERROR;
    enum write_status write_status = to_bmp(maybe_output_file, &rotated);

    log(write_status_string[write_status]);
    if (write_status != WRITE_OK)
        return WRITE_ERROR;

    delete_image(&rotated);
    delete_image(&image);
    closed = close_file(maybe_output_file);
    log(io_return_code_string[closed]);
    return 0;
}

static void log(const char *message) {
    printf("%s\n", message);
}

static void stderr_log(const char *message) {
    fprintf(stderr, "%s\n", message);
}
