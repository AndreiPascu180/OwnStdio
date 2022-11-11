# OwnStdio
	A homework project that implements the stdio library.

	In this project the file pointer structure that I chose is defined in so_handle.h.
	I will briefly explain what is the purpose of each member:
- fd is the file descriptor or the HANDLE, depending on the platform running the library
- buf_base is the pointer to the base of the internal buffer that will be used throughout the whole library
- buf_end points to the end of the allocated memory for the buffer
- read_ptr points to an address inside buffer to know until where we have returned characters to the user from the buffered data inside the buf
- read_end points to an address inside buffer to know where we have stopped reading, the end of the inputed data
- write_ptr and write_end are also pointers to an address inside buf_base and have a similar purpose to the read ones: delimitate the memory which has not been flushed yet to the output stream

	Now for the flags used:
- feof is set when end of file is reached
- ferror is set when any error is encountered other than eof
- read_flag,write_flag,append_flag,update_flag are set according to the opening mode of the file (for example a file opened with r+ will have read_flag and update_flag set on 1
- file_pointer_pos is the virtual cursor inside the file and holds the position at a certain moment
- pid holds the pid of the child process born from fork inside the popen function

	The library flow is based on the general rules of the original stdio library and those are in general verified with
the help of the flags.
	In any update mode(r+/w+/a+) both reading and writing and we avoid any conflicts by modifying these flags:
- in fgetc we reset write_flag until fflush is used
- in fputc we reset read_flag until fflush is used
	Fflush sets both reading and writing flags on 1 if the update_flag is 1, otherwise it invalidates the internal
buffer if the write_flag is 1.
	Fread and fwrite are both implemented with the help of fgetc and fputc respectively, since we can use those
functions that have buffering already implemented it was of much help to read/write byte by byte with their help.


# Sources
## Linux
### https://cboard.cprogramming.com/c-programming/172974-how-does-file-struct-work-stdio-h.html - for FILE struct
### http://ftp.gnu.org/gnu/glibc/ - downloaded glibc 2.2.5 and inspected the sources
### https://www.geeksforgeeks.org/input-output-system-calls-c-create-open-close-read-write/
### https://github.com/Th3Venin/stdio-library/blob/master/so_stdio.c
### https://github.com/rkibistu/Own-implementation-stdio.h/blob/master/so_stdio.c
### https://github.com/shawnq8861/System-Programming/tree/master/StdioImplementation
### All the man pages for the functions in stdio - for return values, error cases etc.

## Windows
### https://learn.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-createfilea
### https://learn.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-setfilepointer
### https://learn.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-readfile
### https://learn.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-writefile
