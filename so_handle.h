#define _CRT_SECURE_NO_WARNINGS
#define _DEBUG_
#include <stdio.h>
#include "stdio.h"

#if defined(__linux__)
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

#elif defined(_WIN32)
#include <fileapi.h>

#else
#error "Unknown platform"
#endif


//definire valori true/false
#define SO_TRUE 1
#define SO_FALSE 0

//definire buffer
#define SO_BUFFER_SIZE 4096

struct _so_file{

#ifdef __linux__
    int fd;
#elif defined(_WIN32)
    HANDLE fd;

#else
#error "Unknown platform"
#endif

    char* _buf_base;    /* Start of reserve area. */
    char* _buf_end;    /* End of reserve area. */

    int buffer_offset; /*Offset in buffer until where data was written*/

    /* FLAGS */
    int _feof;    /* Set when the pointer reaches the end of the file */
    int _ferror;    /* Set when the file is not opened for reading */

    char last_operation; /*Remember last operation 'r' or 'w'*/
    int _can_read;  /*Set when stream opened for reading*/
    int _can_write; /*Set when stream opened for writing*/
    int _can_append; /*Set for append mode*/
    int _can_update; /*Set for + mode*/

    unsigned long _file_pointer_pos;
    unsigned long readChars;
    unsigned long writtenChars;

};