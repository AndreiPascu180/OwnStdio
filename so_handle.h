#define _CRT_SECURE_NO_WARNINGS
#if defined(__linux__)
#include <stdio.h>
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

#ifdef(__linux__)
    int fd;
#elif defined(_WIN32)
    HANDLE fd;

#else
#error "Unknown platform"
#endif


    char* _read_ptr;    /* Current read pointer */
    char* _read_end;    /* End of get area. */
    char* _read_base;    /* Start of putback+get area. */
    char* _write_base;    /* Start of put area. */
    char* _write_ptr;    /* Current put pointer. */
    char* _write_end;    /* End of put area. */
    char* _buf_base;    /* Start of reserve area. */
    char* _buf_end;    /* End of reserve area. */
    /* The following fields are used to support backing up and undo. */
    char* _save_base; /* Pointer to start of non-current get area. */
    char* _backup_base;  /* Pointer to first valid character of backup area */
    char* _save_end; /* Pointer to end of non-current get area. */
    
    
    int _fileno;

}