#include "so_stdio.h"
#include "so_handle.h"
#include "utils.h"

static int check_mode(const char *mode);
static int ReadIntoBuffer(SO_FILE *stream);
static int WriteFromBuffer(SO_FILE *stream);

SO_FILE *so_fopen(const char *pathname, const char *mode)
{
    SO_FILE *so_file = NULL;

    if (check_mode(mode) == SO_TRUE)
    {
        so_file = (SO_FILE *)malloc(sizeof(SO_FILE));
        if (so_file == NULL)
        {
            PRINT_MY_ERROR("malloc failed");
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
                PRINT_MY_ERROR("open");
                so_file->_ferror = SO_TRUE;
                free(so_file);
                return NULL;
            }

#elif defined(_WIN32)
            so_file->fd = CreateFileA(pathname, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
            if (so_file->fd == INVALID_HANDLE_VALUE)
            {
                PRINT_MY_ERROR("CreateFile");
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
                PRINT_MY_ERROR("open");
                so_file->_ferror = SO_TRUE;
                free(so_file);
                return NULL;
            }

#elif defined(_WIN32)
            so_file->fd = CreateFileA(pathname, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
            if (so_file->fd == INVALID_HANDLE_VALUE)
            {
                PRINT_MY_ERROR("CreateFile");
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
            so_file->fd = open(pathname, O_WRONLY | O_TRUNC | O_CREAT, 0664);
            if (so_file->fd == -1)
            {
                PRINT_MY_ERROR("open");
                so_file->_ferror = SO_TRUE;
                free(so_file);
                return NULL;
            }

#elif defined(_WIN32)
            so_file->fd = CreateFileA(pathname, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
            if (so_file->fd == INVALID_HANDLE_VALUE)
            {
                PRINT_MY_ERROR("CreateFile");
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
                PRINT_MY_ERROR("open");
                so_file->_ferror = SO_TRUE;
                free(so_file);
                return NULL;
            }

#elif defined(_WIN32)
            so_file->fd = CreateFileA(pathname, GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
            if (so_file->fd == INVALID_HANDLE_VALUE)
            {
                PRINT_MY_ERROR("CreateFile");
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
                PRINT_MY_ERROR("open");
                so_file->_ferror = SO_TRUE;
                free(so_file);
                return NULL;
            }

#elif defined(_WIN32)
            so_file->fd = CreateFileA(pathname, GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
            if (so_file->fd == INVALID_HANDLE_VALUE)
            {
                PRINT_MY_ERROR("CreateFile");
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
                PRINT_MY_ERROR("open");
                so_file->_ferror = SO_TRUE;
                free(so_file);
                return NULL;
            }

#elif defined(_WIN32)
            so_file->fd = CreateFileA(pathname, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
            if (so_file->fd == INVALID_HANDLE_VALUE)
            {
                PRINT_MY_ERROR("CreateFile");
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
        PRINT_MY_ERROR("Invalid mode");
        return NULL;
    }

    so_file->_read_ptr = so_file->_buf_base;
    so_file->_read_end = so_file->_read_ptr;

    so_file->_write_ptr = so_file->_buf_base;
    so_file->_write_end = so_file->_buf_end;

    so_file->_buf_base = (char *)malloc(sizeof(char) * SO_BUFFER_SIZE);
    so_file->_buf_end = so_file->_buf_base + SO_BUFFER_SIZE;

    so_file->_feof = SO_FALSE;

    so_file->_file_pointer_pos = 0; // pozitia cursorului in fiser!

    return so_file;
}

int so_fclose(SO_FILE *stream)
{
    int err_code1;
    int err_code2;

    if (stream == NULL)
        return -1;

    err_code1 = so_fflush(stream);

    free(stream->_buf_base);

    stream->_read_ptr = NULL;
    stream->_write_ptr = NULL;
    stream->_buf_end = NULL;

#if defined(__linux__)
    err_code2 = close(stream->fd);
#elif defined(_WIN32)
    err_code2 = CloseHandle(stream->fd);
#else
#error "Unknown platform"
#endif

    free(stream);
    stream = NULL;
    if (err_code1 == SO_EOF || err_code2 == SO_EOF)
    {
        stream->_ferror = SO_TRUE;
        return SO_EOF;
    }

    return 0;
}

int so_fflush(SO_FILE *stream)
{
    if (stream == NULL)
        return SO_EOF;

    int ret;
    if (stream->write_flag)
    {

        ret = WriteFromBuffer(stream);
        if (ret != 0)
            return ret;
    }
    if (stream->update_flag)
    {

        stream->write_flag = SO_TRUE;
        stream->read_flag = SO_TRUE;
    }

    stream->_write_ptr = stream->_buf_base;
    stream->_write_end = stream->_buf_end;

    stream->_read_ptr = stream->_buf_base;
    stream->_read_end = stream->_read_ptr;

    return 0;
}

int so_fseek(SO_FILE *stream, long offset, int whence)
{

    if (whence != SEEK_CUR && whence != SEEK_END && whence != SEEK_SET)
    {
        PRINT_MY_ERROR("Invalid whence");
        stream->_ferror = SO_TRUE;
        return SO_EOF;
    }
    long ret;

#if defined(__linux__)
    ret = lseek(stream->fd, offset, whence);
    if (ret == -1)
    {
        PRINT_MY_ERROR("lseek");
        stream->_ferror = SO_TRUE;
        return SO_EOF;
    }
#elif defined(_WIN32)
    ret = SetFilePointer(stream->fd, offset, NULL, whence);
    if (ret == INVALID_SET_FILE_POINTER)
    {
        PRINT_MY_ERROR("SetFilePointer");
        stream->_ferror = SO_TRUE;
        return SO_EOF;
    }
#else
#error "Unknown platform"
#endif

    so_fflush(stream);
    stream->_feof = 0;
    stream->_file_pointer_pos = ret; // actaulizam pozitia pointerului la cursor
    return 0;
}

int so_fgetc(SO_FILE *stream)
{
    int chr;
    int result;

    if (!stream->read_flag || stream->_feof)
    {

        if (stream->read_flag == SO_FALSE && stream->update_flag == SO_TRUE)
        {
            PRINT_MY_ERROR("Fflush needed");
            return SO_EOF;
        }
    }

    if (stream->update_flag)
    {
        /**
         * * Now we are reading so we disable writing until we use Fflush
         */
        stream->write_flag = SO_FALSE;
    }

    /**
     * *If the buffer is either empty or full, we need to fill it
     */
    if (stream->_read_ptr == stream->_read_end)
    {
        int result = ReadIntoBuffer(stream);
        if (result != SO_TRUE)
        {
            PRINT_MY_ERROR("Error reading into buffer");
            return SO_EOF;
        }
    }

    if (stream->_feof == SO_FALSE)
    {
        chr = stream->_read_ptr[0];

        stream->_read_ptr++;
        stream->_file_pointer_pos++;
    }

    if (chr < 0)
    {
        PRINT_MY_ERROR("Invalid character");
        return SO_EOF;
    }

    return chr;
}

int so_fputc(int c, SO_FILE *stream)
{

    int chr;
    int result;

    if (!stream->write_flag || stream->_feof)
    {

        if (stream->write_flag == SO_FALSE && stream->update_flag == SO_TRUE)
        {
            PRINT_MY_ERROR("Fflush needed");
            return SO_EOF;
        }
    }
    /**
     * * We need to seek the end of the file if we are in append mode
     */
    if (stream->append_flag)
    {
        so_fseek(stream, 0, SEEK_END);
    }

    if (stream->update_flag)
    {
        /**
         * * Now we are writing so we disable reading until we use Fflush/fseek
         */
        stream->read_flag = SO_FALSE;
    }

    /**
     * * If the write pointer has gotten to the end of the buffer, we need to empty it into the stream
     */
    if (stream->_write_ptr == stream->_write_end)
    {
        int result = so_fflush(stream);
        if (result != SO_TRUE)
        {
            PRINT_MY_ERROR("Error writing from buffer");
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
    return stream->fd;
}
#elif defined(_WIN32)
HANDLE so_fileno(SO_FILE *stream)
{
    return stream->fd;
}
#else
#error "Unknown platform"
#endif

static int ReadIntoBuffer(SO_FILE *stream)
{
    int readBytes = 0;

#if defined(__linux__)
    readBytes = read(stream->fd, stream->_buf_base, SO_BUFFER_SIZE);
    if (readBytes == -1)
    {
        PRINT_MY_ERROR("read into buffer failed");
        stream->_ferror = SO_TRUE;
        return SO_EOF;
    }
    if (readBytes == 0)
    {
        stream->_feof = SO_TRUE;
        return SO_EOF;
    }
#elif defined(_WIN32)

#else
#error "Unknown platform"
#endif

    stream->_read_ptr = stream->_buf_base;
    stream->_read_end = stream->_buf_base + readBytes;

    return SO_TRUE;
}

static int WriteFromBuffer(SO_FILE *stream)
{
    int bytesToWrite = stream->_write_ptr - stream->_buf_base;
    int bytesWritten = 0;
    int count_total_bytes = 0;
    if (bytesToWrite == 0)
        return 0;
#if defined(__linux__)
    while (bytesWritten < bytesToWrite)
    {
        bytesWritten = write(stream->fd, stream->_buf_base + count_total_bytes, bytesToWrite - count_total_bytes);
        if (bytesWritten == -1)
        {
            PRINT_MY_ERROR("write from buffer failed");
            stream->_ferror = SO_TRUE;
            return SO_EOF;
        }
        if (bytesWritten == 0)
        {
            stream->_feof = SO_TRUE;
            return SO_EOF;
        }
        count_total_bytes += bytesWritten;
    }
#elif defined(_WIN32)
    BOOL result;
    while ()
    {
        result = WriteFile(stream->_hFile,
                           stream->_buffer_base + count_total_bytes,
                           bytesToWrite - count_total_bytes,
                           &bytesWritten,
                           NULL);
        if (result != TRUE)
        {
            PRINT_MY_ERROR("Write-fflush");
            return SO_EOF;
        }

        count_total_bytes += bytesWritten;
    }
#else
#error "Unknown platform"
#endif

    return 0;
}

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