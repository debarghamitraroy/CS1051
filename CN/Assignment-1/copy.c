/* copy.c */

#include <stdint.h>
#include <stdio.h>

int main() {
    printf("Copying 'source.bin' to 'destination.bin'...\n");

    FILE *input_file, *output_file;
    // Open the source file in binary read mode
    input_file = fopen("source.bin", "rb");
    if (input_file == NULL) {
        printf("Could not open source file.\n");
        return 1;
    }

    // Open the destination file in binary write mode
    output_file = fopen("destination.bin", "wb");
    if (output_file == NULL) {
        printf("Could not open/create destination file.\n");
        fclose(input_file);
        return 1;
    }

    int buffer;

    // Read and write data in chunks of size int (binary)
    while (fread(&buffer, sizeof(int), 1, input_file) == 1) {
        fwrite(&buffer, sizeof(int), 1, output_file);
    }

    fclose(input_file);
    fclose(output_file);

    printf("Copying done.\n");

    return 0;
}
