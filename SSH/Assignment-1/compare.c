/* compare.c */

#include <stdint.h>
#include <stdio.h>

int main() {
    printf("Comparing 'source.bin' and 'destination.bin'...\n");

    FILE *f1, *f2;
    unsigned char c1, c2;
    long pos = 0;
    int differences = 0;

    // Open both files in binary read mode
    f1 = fopen("source.bin", "rb");
    if (!f1) {
        printf("Could not open source.bin\n");
        return 1;
    }

    f2 = fopen("destination.bin", "rb");
    if (!f2) {
        printf("Could not open destination.bin\n");
        fclose(f1);
        return 1;
    }

    // Compare byte by byte
    while (1) {
        size_t r1 = fread(&c1, 1, 1, f1);
        size_t r2 = fread(&c2, 1, 1, f2);

        if (r1 == 0 && r2 == 0) {
            break; // reached EOF for both files
        }

        if (r1 != r2) {
            printf("Files differ in length.\n");
            differences++;
            break;
        }

        if (c1 != c2) {
            printf("Difference at byte %ld: source=0x%02X, dest=0x%02X\n", pos,
                   c1, c2);
            differences++;
        }

        pos++;
    }

    fclose(f1);
    fclose(f2);

    if (differences == 0)
        printf("Files are identical.\n");
    else
        printf("Found %d differences.\n", differences);

    return 0;
}
