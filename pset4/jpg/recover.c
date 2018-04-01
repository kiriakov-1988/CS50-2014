/** * recover.c * * Computer Science 50 * Problem Set 4 *
 * Recovers JPEGs from a forensic image */
 
 #include <stdio.h>
 #include <stdlib.h>
 #include <stdint.h>
 
 typedef uint8_t  BYTE;
 
int main(int argc, char* argv[])
{
    // проверка что б не было введено чтото еще
    if (argc != 1)
    {
        printf("Usage: without any file\n");
        return 1;
    }
    
    // открытие файла
    FILE* file = fopen("card.raw", "r");
    if (file == NULL)
    {
        printf("Could not open card.raw\n");
        return 2;
    }
    
    // создание указателя на файл для записи
    FILE* outptr;

    // создание буфера
    BYTE buffer[512]; 
    if (buffer == NULL)
    {
        printf("Could not create buffer\n");
        return 3;
    }
    
    int i = 0; // счетчик файлов и нетолько
    
    // считываем по 512 байт
    while (!feof(file))
    {
        fread(buffer, sizeof(buffer), 1, file);
        
        char outfile[8]; // создание шаблона для названия файла с раширением 
        if (i < 10)              {            sprintf(outfile,"00%d.jpg", i);        }
        else if (i < 100)        {            sprintf(outfile,"0%d.jpg", i);        }  
        else if (i < 1000)       {            sprintf(outfile,"%d.jpg", i);        }   // это лишнее в данном примере, но для полного примера добавлено  
        
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] == 0xe0 || buffer[3] == 0xe1))
        {
            if (i > 0) // закрытие предыдущего файла, если есть
            {
                fclose(outptr);
            }
            
            // создание нового файла для записи
            outptr = fopen(outfile, "a");
            if (outptr == NULL)
            {
                fprintf(stderr, "Create %s.\n", outfile);
                return 4;
            }
            
            i++; // счетчки "созданных/найденных" файлов
        }
        
        if (i > 0) // если уже найден первый файл, то запись
        {
            if (feof(file)) // если дошло до конца, то последний (пустой/лишний) блок не надо записывать (коректно работет только в это месте)
            {
                fclose(outptr);
                break;
            }
            fwrite(buffer, sizeof(buffer), 1, outptr);
        }
    }
    
    // закрытие исходного файла
    fclose(file);
    
    return 0;
}
