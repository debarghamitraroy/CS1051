#include <stdint.h>
#include <stdio.h>

int main() {
    printf("Copying 'source.bin' to 'destination.bin'...\n");
    FILE *input_file, *output_file;
    input_file = fopen("source.bin", "rb");
    if (input_file == NULL) {
        printf("Could not open source file.\n");
        return 1;
    }
    output_file = fopen("destination.bin", "wb");
    if (output_file == NULL) {
        printf("Could not open/create destination file.\n");
        fclose(input_file);
        return 1;
    }
    int buffer;
    while (fread(&buffer, sizeof(int), 1, input_file) == 1) {
        fwrite(&buffer, sizeof(int), 1, output_file);
    }
    fclose(input_file);
    fclose(output_file);
    printf("Copying done.\n");
    return 0;
}
