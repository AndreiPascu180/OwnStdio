#include "so_stdio.h"


int _main() {


	SO_FILE* file = so_fopen("out.txt","a+");
	if (file == NULL) {
		printf("so_fopen failed");
		exit(0);
	}


	//so_fclose(file);
} 