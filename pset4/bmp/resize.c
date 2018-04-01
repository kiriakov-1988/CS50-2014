/**
 * copy.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize n infile outfile\n");
        return 1;
    }

    // remember filenames
    int n = atoi(argv[1]); // узнаем n
    char* infile = argv[2];
    char* outfile = argv[3];
    
    // проверка N от 1 до 100 - включая 1 и 100
    if (n < 1 || n > 100)
    {
        printf("n from 1 to 100\n");
        return 2;
    }

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 3;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 4;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 5;
    }
    
    // копия заголовка и изменение потом значений
    BITMAPFILEHEADER nf = bf;
    BITMAPINFOHEADER ni = bi;
    
    ni.biWidth = bi.biWidth * n;
    ni.biHeight = bi.biHeight * n;
    
    int new_padding =  (4 - (ni.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    ni.biSizeImage = abs(ni.biHeight) * (ni.biWidth * sizeof(RGBTRIPLE) + new_padding); // высоту надо брать по модулю, т.е. положительное !!
    nf.bfSize = 54 + ni.biSizeImage; 
    

    // write outfile's BITMAPFILEHEADER
    fwrite(&nf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&ni, sizeof(BITMAPINFOHEADER), 1, outptr);

    // determine padding for scanlines
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        for (int h = 0; h < n; h++) // цикл для маштобирования  в высоту
        {
            // iterate over pixels in scanline
            for (int j = 0; j < bi.biWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                for (int w = 0; w < n; w++) // цикл для маштобирования  в ширину
                {
                    // write RGB triple to outfile
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }

            if (h < n-1)
            {
                // возвтра указателя на ширину старого рисунка - для дублирования строки
                fseek(inptr, -bi.biWidth * sizeof(RGBTRIPLE), SEEK_CUR);
            }
            else // иначе переход на новую строку в старом файле
            {
                // skip over padding, if any
                fseek(inptr, padding, SEEK_CUR);
            }

            // then add it back (to demonstrate how)
            for (int k = 0; k < new_padding; k++)
            {
                fputc(0x00, outptr);
            }
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
