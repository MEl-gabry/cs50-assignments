#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    FILE *image = fopen(argv[1], "r");
    uint8_t bytes[512];
    int jpeg_count = 0;
    char *filename = malloc(9);
    FILE *jpeg;
    while (fread(bytes, sizeof(uint8_t), 512, image) == 512)
    {
        if (bytes[0] == 0xff && bytes[1] == 0xd8 && bytes[2] == 0xff && (bytes[3] & 0xf0) == 0xe0 && jpeg_count == 0)
        {
            jpeg_count++;
            sprintf(filename, "%03i.jpeg", jpeg_count);
            jpeg = fopen(filename, "w");
            fwrite(bytes, sizeof(uint8_t), 512, jpeg);
        }
        else if (bytes[0] == 0xff && bytes[1] == 0xd8 && bytes[2] == 0xff && (bytes[3] & 0xf0) == 0xe0)
        {
            fclose(jpeg);
            jpeg_count++;
            sprintf(filename, "%03i.jpeg", jpeg_count);
            jpeg = fopen(filename, "w");
            fwrite(bytes, sizeof(uint8_t), 512, jpeg);
        }
        else if (jpeg_count > 0)
        {
            fwrite(bytes, sizeof(uint8_t), 512, jpeg);
        }
    }
    fclose(jpeg);
    fclose(image);
    free(filename);
}