#define _CRT_SECURE_NO_WARNINGS
#define _DEBUG_
#include <stdio.h>
#include "so_stdio.h"

#if defined(__linux__)
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>

#elif defined(_WIN32)
#include <fileapi.h>

#else
#error "Unknown platform"
#endif

#define SO_TRUE 1
#define SO_FALSE 0
#define READ_ONLY_FLAG 8    // bits: 1000
#define READ_PLUS_FLAG 13   // bits: 1101
#define WRITE_ONLY_FLAG 4   // bits: 0100
#define WRITE_PLUS_FLAG 13  // bits: 1101
#define APPEND_FLAG 6       // bits: 0110
#define APPEND_PLUS_FLAG 15 // bits: 1111
// definire buffer
#define SO_BUFFER_SIZE 4096

struct _so_file
{
#if defined(__linux__)
    int fd;
#elif defined(_WIN32)
    HANDLE fd;
#else
#error "Unknown platform"
#endif

    char *_read_ptr; /* Current read pointer */
    char *_read_end; /* End of get area. */

    char *_write_ptr; /* Current put pointer. */
    char *_write_end; /* End of put area. */

    char *_buf_base; /* Start of reserve area. */
    char *_buf_end;  /* End of reserve area. */

    /* FLAGS */
    int _feof; /* Set when the pointer reaches the end of the file */
    int _ferror;

    int read_flag;   /*Set when stream opened for reading*/
    int write_flag;  /*Set when stream opened for writing*/
    int append_flag; /*Set for append mode*/
    int update_flag; /*Set for + mode*/

    unsigned long _file_pointer_pos;

    int pid;
};