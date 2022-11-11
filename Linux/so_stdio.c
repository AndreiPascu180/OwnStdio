#include "so_handle.h"

static int check_mode(const char *mode);

SO_FILE *so_fopen(const char *pathname, const char *mode)
{
    SO_FILE *so_file = NULL;

    if (check_mode(mode) == SO_TRUE)
    {
        so_file = (SO_FILE *)malloc(sizeof(SO_FILE));
        if (so_file == NULL)
        {
            so_file->_ferror = SO_TRUE;
            return NULL;
        }
        /**
         *  * -----------------------------------READ--------------------------------------------*/
        if (strcmp(mode, "r") == 0)
        {

#if defined(__linux__)
            so_file->fd = open(pathname, O_RDONLY);
            if (so_file->fd == -1)
            {
                so_file->_ferror = SO_TRUE;
                free(so_file);
                return NULL;
            }

#elif defined(_WIN32)
            so_file->fd = CreateFileA(pathname,
                                      GENERIC_READ,
                                      FILE_SHARE_READ,
                                      NULL,
                                      OPEN_EXISTING,
                                      FILE_ATTRIBUTE_NORMAL,
                                      NULL);
            if (so_file->fd == INVALID_HANDLE_VALUE)
            {
                so_file->_ferror = SO_TRUE;
                free(so_file);
                return NULL;
            }

#else
#error "Unknown platform"
#endif

            so_file->read_flag = SO_TRUE;
            so_file->write_flag = SO_FALSE;
            so_file->append_flag = SO_FALSE;
            so_file->update_flag = SO_FALSE;
        }
        /**
         *  * -----------------------------------READ+UPDATE--------------------------------------------*/
        else if (strcmp(mode, "r+") == 0)
        {

#if defined(__linux__)
            so_file->fd = open(pathname, O_RDWR);
            if (so_file->fd == -1)
            {
                so_file->_ferror = SO_TRUE;
                free(so_file);
                return NULL;
            }

#elif defined(_WIN32)
            so_file->fd = CreateFileA(pathname,
                                      GENERIC_READ | GENERIC_WRITE,
                                      FILE_SHARE_READ | FILE_SHARE_WRITE,
                                      NULL,
                                      OPEN_EXISTING,
                                      FILE_ATTRIBUTE_NORMAL,
                                      NULL);
            if (so_file->fd == INVALID_HANDLE_VALUE)
            {
                so_file->_ferror = SO_TRUE;
                free(so_file);
                return NULL;
            }

#else
#error "Unknown platform"
#endif

            so_file->read_flag = SO_TRUE;
            so_file->write_flag = SO_TRUE;
            so_file->append_flag = SO_FALSE;
            so_file->update_flag = SO_TRUE;
        }
        /**
         *  * -----------------------------------WRITE--------------------------------------------*/
        else if (strcmp(mode, "w") == 0)
        {

#if defined(__linux__)
            so_file->fd = open(pathname, O_WRONLY | O_TRUNC | O_CREAT, 0644);
            if (so_file->fd == -1)
            {
                so_file->_ferror = SO_TRUE;
                free(so_file);
                return NULL;
            }

#elif defined(_WIN32)
            so_file->fd = CreateFileA(pathname,
                                      GENERIC_WRITE,
                                      FILE_SHARE_WRITE,
                                      NULL,
                                      CREATE_ALWAYS,
                                      FILE_ATTRIBUTE_NORMAL,
                                      NULL);
            if (so_file->fd == INVALID_HANDLE_VALUE)
            {
                so_file->_ferror = SO_TRUE;
                free(so_file);
                return NULL;
            }

#else
#error "Unknown platform"
#endif

            so_file->read_flag = SO_FALSE;
            so_file->write_flag = SO_TRUE;
            so_file->append_flag = SO_FALSE;
            so_file->update_flag = SO_FALSE;
        }
        /**
         *  * -----------------------------------WRITE+UPDATE--------------------------------------------*/
        else if (strcmp(mode, "w+") == 0)
        {

#if defined(__linux__)
            so_file->fd = open(pathname, O_RDWR | O_TRUNC | O_CREAT, 0644);
            if (so_file->fd == -1)
            {
                so_file->_ferror = SO_TRUE;
                free(so_file);
                return NULL;
            }

#elif defined(_WIN32)
            so_file->fd = CreateFileA(pathname,
                                      GENERIC_WRITE | GENERIC_READ,
                                      FILE_SHARE_WRITE | FILE_SHARE_READ,
                                      NULL,
                                      CREATE_ALWAYS,
                                      FILE_ATTRIBUTE_NORMAL,
                                      NULL);
            if (so_file->fd == INVALID_HANDLE_VALUE)
            {
                so_file->_ferror = SO_TRUE;
                free(so_file);
                return NULL;
            }

#else
#error "Unknown platform"
#endif

            so_file->read_flag = SO_TRUE;
            so_file->write_flag = SO_TRUE;
            so_file->append_flag = SO_FALSE;
            so_file->update_flag = SO_TRUE;
        }
        /**
         *  * -----------------------------------APPEND--------------------------------------------*/
        else if (strcmp(mode, "a") == 0)
        {

#if defined(__linux__)
            so_file->fd = open(pathname, O_APPEND | O_WRONLY | O_CREAT, 0644);
            if (so_file->fd == -1)
            {
                so_file->_ferror = SO_TRUE;
                free(so_file);
                return NULL;
            }

#elif defined(_WIN32)
            so_file->fd = CreateFileA(pathname,
                                      FILE_APPEND_DATA,
                                      FILE_SHARE_WRITE,
                                      NULL,
                                      OPEN_ALWAYS,
                                      FILE_ATTRIBUTE_NORMAL,
                                      NULL);
            if (so_file->fd == INVALID_HANDLE_VALUE)
            {
                so_file->_ferror = SO_TRUE;
                free(so_file);
                return NULL;
            }

#else
#error "Unknown platform"
#endif

            so_file->read_flag = SO_FALSE;
            so_file->write_flag = SO_TRUE;
            so_file->append_flag = SO_TRUE;
            so_file->update_flag = SO_FALSE;
        }
        /**
         *  * -----------------------------------APPEND+UPDATE--------------------------------------------*/
        else if (strcmp(mode, "a+") == 0)
        {

#if defined(__linux__)
            so_file->fd = open(pathname, O_APPEND | O_RDWR | O_CREAT, 0644);
            if (so_file->fd == -1)
            {
                so_file->_ferror = SO_TRUE;
                free(so_file);
                return NULL;
            }

#elif defined(_WIN32)
            so_file->fd = CreateFileA(pathname,
                                      FILE_APPEND_DATA | GENERIC_READ,
                                      FILE_SHARE_WRITE | FILE_SHARE_READ,
                                      NULL,
                                      OPEN_ALWAYS,
                                      FILE_ATTRIBUTE_NORMAL,
                                      NULL);
            if (so_file->fd == INVALID_HANDLE_VALUE)
            {
                so_file->_ferror = SO_TRUE;
                free(so_file);
                return NULL;
            }

#else
#error "Unknown platform"
#endif

            so_file->read_flag = SO_TRUE;
            so_file->write_flag = SO_TRUE;
            so_file->append_flag = SO_TRUE;
            so_file->update_flag = SO_TRUE;
        }
    }
    else
    {
        return NULL;
    }

    so_file->_buf_base = (char *)malloc(SO_BUFFER_SIZE * sizeof(char));
    if (so_file->_buf_base == NULL)
    {
        so_file->_ferror = SO_TRUE;
        return NULL;
    }
    so_file->_buf_end = so_file->_buf_base + SO_BUFFER_SIZE;

    so_file->_write_ptr = so_file->_buf_base;
    so_file->_write_end = so_file->_buf_end;

    so_file->_read_ptr = so_file->_buf_base;
    so_file->_read_end = so_file->_read_ptr;

    so_file->_feof = SO_FALSE;
    so_file->_ferror = SO_FALSE;

    so_file->_file_pointer_pos = 0;

    return so_file;
}

int so_fflush(SO_FILE *stream)
{
    if (stream == NULL)
        return SO_EOF;

    // * If we can write
    if (stream->write_flag)
    {

        int bytesToWrite = stream->_write_ptr - stream->_buf_base;
        int bytesWritten = 0;
        int count_total_bytes = 0;
        if (bytesToWrite == 0)
        {
            return 0;
        }
        if (stream->_write_ptr > stream->_buf_end)
        {
            stream->_ferror = SO_TRUE;
            return SO_EOF;
        }
        if (stream->_write_ptr == NULL || stream->_buf_base == NULL)
        {
            stream->_ferror = SO_TRUE;
            return SO_EOF;
        }
#if defined(__linux__)
        do
        {
            bytesWritten = write(stream->fd, stream->_buf_base + count_total_bytes, bytesToWrite - count_total_bytes);
            if (bytesWritten == -1)
            {
                stream->_ferror = SO_TRUE;
                return SO_EOF;
            }
            if (bytesWritten == 0)
            {
                stream->_feof = SO_TRUE;
                return SO_EOF;
            }
            count_total_bytes += bytesWritten;
        } while (count_total_bytes < bytesToWrite);
#elif defined(_WIN32)
        BOOL result;
        while (count_total_bytes < bytesToWrite)
        {
            result = WriteFile(stream->fd,
                               stream->_buf_base + count_total_bytes,
                               stream->_bytesWrite - count_total_bytes,
                               &bytesWritten,
                               NULL);
            if (result != TRUE)
            {
                stream->_ferror = SO_TRUE;
                return SO_EOF;
            }

            count_total_bytes += bytesWritten;
        }
#else
#error "Unknown platform"
#endif

        // memset(stream->_buf_base, 0, SO_BUFFER_SIZE);
    }
    // * If we can update we set again the permissions for reading and writing
    if (stream->update_flag)
    {
        stream->read_flag = SO_TRUE;
        stream->write_flag = SO_TRUE;
    }

    stream->_read_ptr = stream->_buf_base;
    stream->_read_end = stream->_read_ptr;

    stream->_write_ptr = stream->_buf_base;
    stream->_write_end = stream->_buf_end;

    return 0;
}

int so_fseek(SO_FILE *stream, long offset, int whence)
{

    if (whence != SEEK_CUR && whence != SEEK_END && whence != SEEK_SET)
    {
        stream->_ferror = SO_TRUE;
        return SO_EOF;
    }
    int ret;
    ret = so_fflush(stream);
    if (ret != 0)
    {
        stream->_ferror = SO_TRUE;
        return SO_EOF;
    }

#if defined(__linux__)
    ret = lseek(stream->fd, offset, whence); // * System call to change the file pointer position to offset relative to the whence
    if (ret == -1)
    {
        stream->_ferror = SO_TRUE;
        return SO_EOF;
    }
#elif defined(_WIN32)
    ret = SetFilePointer(stream->fd, offset, NULL, whence);
    if (ret == INVALID_SET_FILE_POINTER)
    {
        stream->_ferror = SO_TRUE;
        return SO_EOF;
    }
#else
#error "Unknown platform"
#endif

    stream->_feof = 0;
    stream->_file_pointer_pos = ret; // * Update file pointer position
    return 0;
}

int so_fgetc(SO_FILE *stream)
{
    int chr = 0;
    int result = 0;

    // * If we can't read or we've reached the end of the file
    if (stream->read_flag == SO_FALSE || stream->_feof)
    {
        // * If we can't read AND we can update - Fflush neded!!
        if (stream->read_flag == SO_FALSE && stream->update_flag == SO_TRUE)
        {
            return SO_EOF;
        }
    }

    // * If we can update
    if (stream->update_flag)
    {
        //* Now we are reading so we disable writing until we use Fflush
        stream->write_flag = SO_FALSE;
    }

    //*If the buffer is either empty or full, we need to fill it
    if (stream->_read_ptr == stream->_read_end)
    {
        int readBytes = 0;
        // memset(stream->_buf_base, 0, SO_BUFFER_SIZE);

#if defined(__linux__)
        readBytes = read(stream->fd, stream->_buf_base, SO_BUFFER_SIZE);
        if (readBytes == -1)
        {
            stream->_ferror = SO_TRUE;
            return SO_EOF;
        }
        if (readBytes == 0)
        {
            stream->_feof = SO_TRUE;
            return SO_EOF;
        }
#elif defined(_WIN32)
        BOOL ret = ReadFile(stream->fd, stream->_buf_base, SO_BUFFER_SIZE, &readBytes, NULL);
        if (ret != TRUE)
        {
            stream->_ferror = SO_TRUE;
            return SO_EOF;
        }
        if (ret && readBytes == 0)
        {
            stream->_feof = SO_EOF;
            return SO_EOF;
        }
#else
#error "Unknown platform"
#endif

        stream->_read_ptr = stream->_buf_base;
        stream->_read_end = stream->_buf_base + readBytes;
    }

    if (stream->_feof == SO_FALSE)
    {
        chr = stream->_read_ptr[0];
        stream->_read_ptr++;
        stream->_file_pointer_pos++;
    }

    // if (chr < 0)
    // {
    //     return SO_EOF;
    // }

    return chr;
}

int so_fputc(int c, SO_FILE *stream)
{

    int chr;
    int result;

    // * If we can't write AND we can update
    if (stream->write_flag == SO_FALSE && stream->update_flag == SO_TRUE)
    {
        // * USER MUST SEEK BEFORE WRITING
        return SO_EOF;
    }

    // * If we can update
    if (stream->update_flag == SO_TRUE)
    {
        //* Now we are writing so we disable reading until we use Fflush/fseek
        stream->read_flag = SO_FALSE;
    }

    //* If the write pointer has gotten to the end of the buffer, we need to empty it into the stream
    if (stream->_write_ptr == stream->_write_end)
    {
        int result = so_fflush(stream);
        if (result != 0)
        {
            stream->_ferror = SO_TRUE;
            return SO_EOF;
        }
    }

    stream->_write_ptr[0] = c;
    stream->_file_pointer_pos++;
    stream->_write_ptr++;
    return c;
}

long so_ftell(SO_FILE *stream)
{

    return stream->_file_pointer_pos;
}

int so_feof(SO_FILE *stream)
{
    return stream->_feof;
}

int so_ferror(SO_FILE *stream)
{
    return stream->_ferror;
}

#if defined(__linux__)
int so_fileno(SO_FILE *stream)
{
    int fd = stream->fd;
    return fd;
}
#elif defined(_WIN32)
HANDLE so_fileno(SO_FILE *stream)
{
    return stream->fd;
}
#else
#error "Unknown platform"
#endif

static int check_mode(const char *mode)
{
    if (strcmp(mode, "r") == 0)
    {
        return SO_TRUE;
    }
    if (strcmp(mode, "w") == 0)
    {
        return SO_TRUE;
    }
    if (strcmp(mode, "a") == 0)
    {
        return SO_TRUE;
    }
    if (strcmp(mode, "r+") == 0)
    {
        return SO_TRUE;
    }
    if (strcmp(mode, "w+") == 0)
    {
        return SO_TRUE;
    }
    if (strcmp(mode, "a+") == 0)
    {
        return SO_TRUE;
    }

    return SO_FALSE;
}

size_t so_fread(void *ptr, size_t size, size_t nmemb, SO_FILE *stream)
{
    if (stream->_feof == SO_TRUE)
        return 0;

    if (size == 0 || nmemb == 0)
        return 0;

    int bytesToRead = size * nmemb;
    int bytesRead = 0;
    char *given_buf = (char *)ptr;
    int c;

    for (int i = 0; i < bytesToRead; i++)
    {
        c = so_fgetc(stream);
        if (stream->_feof == SO_TRUE || stream->_ferror == SO_TRUE)
        {
            return bytesRead / size;
        }
        given_buf[i] = c;
        bytesRead++;
    }

    return bytesRead / size; // * To get the ITEMS read, not the number of bytes read
}

size_t so_fwrite(const void *ptr, size_t size, size_t nmemb, SO_FILE *stream)
{

    if (size == 0 || nmemb == 0)
        return 0;

    int bytesToWrite = size * nmemb;
    int bytesWritten = 0;
    char *given_buf = (char *)ptr;
    char c;
    int result;

    for (int i = 0; i < bytesToWrite; i++)
    {
        c = given_buf[i];
        result = so_fputc((int)c, stream);
        if (stream->_feof == SO_TRUE || stream->_ferror == SO_TRUE)
        { // Not so sure about this one...
            return bytesWritten / size;
        }
        // if (result < 0)
        // {
        //     stream->_ferror = SO_TRUE;
        //     return bytesWritten / size;
        // }
        bytesWritten++;
    }

    return bytesWritten / size; // * To get the ITEMS read, not the number of bytes read
}

int so_fclose(SO_FILE *stream)
{
    int err_code1 = 0;
    int err_code2 = 0;

    if (stream == NULL)
        return -1;

    if (stream->write_flag)
    {
        err_code1 = so_fflush(stream);
        if (err_code1 != 0 || stream->_ferror != 0 || stream->_feof != 0)
        {
            stream->_ferror = SO_TRUE;
            if (stream->_buf_base != NULL)
            {
                free(stream->_buf_base);
                stream->_buf_base = NULL;
            }
            if (stream != NULL)
            {
                free(stream);
                stream = NULL;
            }
            return SO_EOF;
        }
    }

    if (stream->_buf_base != NULL)
    {
        // memset(stream->_buf_base, '\0', SO_BUFFER_SIZE);
        free(stream->_buf_base);
        stream->_buf_base = NULL;
    }
    stream->_read_ptr = NULL;
    stream->_read_end = NULL;
    stream->_write_ptr = NULL;
    stream->_write_end = NULL;
    stream->_buf_end = NULL;
    stream->read_flag = 0;
    stream->write_flag = 0;
    stream->append_flag = 0;
    stream->update_flag = 0;
    stream->pid = 0;

#if defined(__linux__)
    err_code2 = close(stream->fd);
#elif defined(_WIN32)
    err_code2 = CloseHandle(stream->fd);
#else
#error "Unknown platform"
#endif

    if (err_code2 == SO_EOF)
    {
        stream->_ferror = SO_TRUE;
        return SO_EOF;
    }

    if (stream != NULL)
    {
        stream->fd = 0;
        free(stream);
        stream = NULL;
    }

    return 0;
}

SO_FILE *so_popen(const char *command, const char *type)
{
    int fds[2];
    int read_mode = 0;
    int write_mode = 0;
    if (strcmp(type, "r") == 0)
    {
        read_mode = SO_TRUE;
    }
    else if (strcmp(type, "w") == 0)
    {
        write_mode = SO_TRUE;
    }
    int bRet = pipe(fds);
    if (bRet < 0)
    {
        printf("Cannot create a pipe!");
        return NULL;
    }
    pid_t pid = fork();
    int fileDescriptor = 0;
    if (pid < 0)
    {
        close(fds[0]);
        close(fds[1]);
        return NULL;
    }
    else if (pid == 0)
    {
        if (read_mode)
        {
            close(fds[0]);
            dup2(fds[1], STDOUT_FILENO);
            close(fds[1]);
        }
        else
        {
            close(fds[1]);
            dup2(fds[0], STDIN_FILENO);
            close(fds[0]);
        }
        int ok;
        ok = execlp("sh", "sh", "-c", command, NULL);
        exit(1);
    }
    else
    {
        if (read_mode)
        {
            close(fds[1]);
            fileDescriptor = fds[0];
        }
        else
        {
            close(fds[0]);
            fileDescriptor = fds[1];
        }
    }
    SO_FILE *so_file = (SO_FILE *)malloc(sizeof(SO_FILE));
    if (so_file == NULL)
    {
        so_file->_ferror = SO_TRUE;
        free(so_file);
        return NULL;
    }

    so_file->fd = fileDescriptor;
    so_file->pid = pid;

    so_file->_buf_base = (char *)malloc(SO_BUFFER_SIZE * sizeof(char));
    if (so_file->_buf_base == NULL)
    {
        so_file->_ferror = SO_TRUE;
        return NULL;
    }
    so_file->_buf_end = so_file->_buf_base + SO_BUFFER_SIZE;

    so_file->_write_ptr = so_file->_buf_base;
    so_file->_write_end = so_file->_buf_end;

    so_file->_read_ptr = so_file->_buf_base;
    so_file->_read_end = so_file->_read_ptr;

    so_file->_feof = SO_FALSE;
    so_file->_ferror = SO_FALSE;

    so_file->_file_pointer_pos = 0;

    so_file->read_flag = read_mode;
    so_file->write_flag = write_mode;
    so_file->append_flag = SO_FALSE;
    so_file->update_flag = SO_FALSE;

    return so_file;
}

int so_pclose(SO_FILE *stream)
{
    pid_t pid = stream->pid;
    if (pid == -1)
    {
        return SO_EOF;
    }

    int ret = so_fclose(stream);
    if (ret != 0)
    {
        return SO_EOF;
    }
    int status;
    ret = waitpid(pid, &status, 0);
    if (ret < 0)
    {
        return ret;
    }
    return status;
}