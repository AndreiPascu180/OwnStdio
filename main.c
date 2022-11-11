#include "so_handle.h"
#include "so_stdio.h"

int main()
{
    // SO_FILE *file = so_fopen("out.txt", "w");
    // if (file == NULL)
    // {
    //     printf("fail to open file\n");
    //     return 0;
    // }

    // char buf[] = "Hello, World!\n";
    // int buf_len = sizeof(buf) - 1;

    int ret = 0;
    // so_fread(&buf, 1, sizeof(buf) - 1, file);
    // ret = so_fseek(file, 0, SEEK_END);

    //ret = so_fwrite(buf, 1, buf_len, file);

    // int c1 = so_fgetc(file);
    // int c2 = so_fgetc(file);
    // int c3 = so_fgetc(file);
    // int c4 = so_fgetc(file);
    // printf("Caracter citit:%c\n", c1);
    // printf("Caracter citit2:%c\n", c2);
    // printf("Caracter citit3:%c\n", c3);
    // printf("Caracter citit4:%c\n", c4);

    // so_fputc(c3,file);

    //so_fclose(file);

    SO_FILE * f1,*f2,*f3;
    FILE* f4,*f5,*f6;

    f1 = so_fopen("out.txt", "r");
    f4 = fopen("out.txt","r");

	f2 = so_fopen("out.txt", "w");
    f5 = fopen("out.txt","w");

	f3 = so_fopen("out.txt", "r");
    f6 = fopen("out.txt","r");

	int target_fd = so_fileno(f2); 

	ret = so_fclose(f3);
    fclose(f4);
	//FAIL_IF(ret != 0, "Incorrect return value for so_fclose: got %d, expected %d\n", ret, 0);

	ret = so_fclose(f2);
    fclose(f5);
	//FAIL_IF(ret == 0, "Incorrect return value for so_fclose: got %d, expected !%d\n", ret, -1);

	ret = so_fclose(f1);
    fclose(f6);
	//FAIL_IF(ret != 0, "Incorrect return value for so_fclose: got %d, expected %d\n", ret, 0);
    return 0;
}