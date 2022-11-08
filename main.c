#include "so_handle.h"
#include "so_stdio.h"

int main()
{
    SO_FILE *file = so_fopen("out.txt", "a+");
    if (file == NULL)
    {
        printf("fail to open file\n");
        return 0;
    }

    int c1 = so_fgetc(file);
    int c2 = so_fgetc(file);
    int c3 = so_fgetc(file);
    int c4 = so_fgetc(file);
    printf("Caracter citit:%c\n", c1);
    printf("Caracter citit2:%c\n", c2);
    printf("Caracter citit3:%c\n", c3);
    printf("Caracter citit4:%c\n", c4);
    so_fflush(file);
    so_fputc(c1,file);
    so_fputc(c2,file);
    so_fputc(c3,file);


    so_fclose(file);
    return 0;
}