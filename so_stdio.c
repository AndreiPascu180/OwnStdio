#include "so_stdio.h"
#include "so_handle.h"
#include "utils.h"

static int check_mode(const char *mode);
static int ReadIntoBuffer(SO_FILE *stream);
static int WriteIntoBuffer(SO_FILE *stream);

SO_FILE *so_fopen(const char *pathname, const char *mode)
{
    SO_FILE *so_file = NULL;

    if (check_mode(mode) == SO_TRUE)
    {
        so_file = (SO_FILE *)malloc(sizeof(SO_FILE));
        if (so_file == NULL)
        {
            PRINT_MY_ERROR("malloc failed");
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
                free(so_file);
                return NULL;
            }

#elif defined(_WIN32)
            so_file->fd = CreateFileA(pathname, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
            if (so_file->fd == INVALID_HANDLE_VALUE)
            {
                PRINT_MY_ERROR("CreateFile");
                free(so_file);
                return NULL;
            }

#else
#error "Unknown platform"
#endif

            so_file->_can_read = SO_TRUE;
            so_file->_can_write = SO_FALSE;
            so_file->_can_append = SO_FALSE;
            so_file->_can_update = SO_FALSE;
            so_file->last_operation = 'o';
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
                free(so_file);
                return NULL;
            }

#elif defined(_WIN32)
            so_file->fd = CreateFileA(pathname, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
            if (so_file->fd == INVALID_HANDLE_VALUE)
            {
                PRINT_MY_ERROR("CreateFile");
                free(so_file);
                return NULL;
            }

#else
#error "Unknown platform"
#endif

            so_file->_can_read = SO_TRUE;
            so_file->_can_write = SO_TRUE;
            so_file->_can_append = SO_FALSE;
            so_file->_can_update = SO_TRUE;
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
                free(so_file);
                return NULL;
            }

#elif defined(_WIN32)
            so_file->fd = CreateFileA(pathname, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
            if (so_file->fd == INVALID_HANDLE_VALUE)
            {
                PRINT_MY_ERROR("CreateFile");
                free(so_file);
                return NULL;
            }

#else
#error "Unknown platform"
#endif

            so_file->_can_read = SO_FALSE;
            so_file->_can_write = SO_TRUE;
            so_file->_can_append = SO_FALSE;
            so_file->_can_update = SO_FALSE;
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
                free(so_file);
                return NULL;
            }

#elif defined(_WIN32)
            so_file->fd = CreateFileA(pathname, GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
            if (so_file->fd == INVALID_HANDLE_VALUE)
            {
                PRINT_MY_ERROR("CreateFile");
                free(so_file);
                return NULL;
            }

#else
#error "Unknown platform"
#endif

            so_file->_can_read = SO_TRUE;
            so_file->_can_write = SO_TRUE;
            so_file->_can_append = SO_FALSE;
            so_file->_can_update = SO_TRUE;
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
                free(so_file);
                return NULL;
            }

#elif defined(_WIN32)
            so_file->fd = CreateFileA(pathname, GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
            if (so_file->fd == INVALID_HANDLE_VALUE)
            {
                PRINT_MY_ERROR("CreateFile");
                free(so_file);
                return NULL;
            }

#else
#error "Unknown platform"
#endif

            so_file->_can_read = SO_FALSE;
            so_file->_can_write = SO_TRUE;
            so_file->_can_append = SO_TRUE;
            so_file->_can_update = SO_FALSE;
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
                free(so_file);
                return NULL;
            }

#elif defined(_WIN32)
            so_file->fd = CreateFileA(pathname, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
            if (so_file->fd == INVALID_HANDLE_VALUE)
            {
                PRINT_MY_ERROR("CreateFile");
                free(so_file);
                return NULL;
            }

#else
#error "Unknown platform"
#endif

            so_file->_can_read = SO_TRUE;
            so_file->_can_write = SO_TRUE;
            so_file->_can_append = SO_TRUE;
            so_file->_can_update = SO_TRUE;
        }
    }
    else
    {
        PRINT_MY_ERROR("Invalid mode");
        return NULL;
    }

    so_file->_buf_base = (char *)malloc(sizeof(char) * SO_BUFFER_SIZE);
    so_file->_buf_end = so_file->_buf_base + SO_BUFFER_SIZE;

    so_file->_feof = SO_FALSE;

    so_file->_file_pointer_pos = 0; // pozitia cursorului in fiser!
    so_file->last_operation = 'o';

    return so_file;
}

int so_fclose(SO_FILE *stream)
{

    if (stream == NULL)
        return -1;

    //so_fflush(stream);

    free(stream->_buf_base);

    stream->_buf_end = NULL;

#if defined(__linux__)
    close(stream->fd);
#elif defined(_WIN32)
    CloseHandle(stream->fd);
#else
#error "Unknown platform"
#endif

    free(stream);
    stream = NULL;

    return 0;
}

int so_fgetc(SO_FILE *stream)
{
    int chr;
    int result;

    if (!stream->_can_read || stream->_feof)
    {

        if (stream->_can_read == SO_FALSE && stream->_can_update == SO_TRUE)
        {
            PRINT_MY_ERROR("Fflush needed");

            return SO_EOF;
        }
    }

    if (stream->_can_update)
    {
        /**
         * * Now we are reading so we disable writing until we use Fflush
         */
        stream->_can_write = SO_FALSE;
    }

    if(stream->_buf_base+stream->buffer_offset == stream->_buf_end || stream->_buf_base+stream->buffer_offset == stream->_buf_base){
        int result = ReadIntoBuffer(stream);
        if(result != SO_TRUE){
            PRINT_MY_ERROR("Error reading into buffer");
            return SO_EOF;
        }
    }

    if(stream->_feof == SO_FALSE){
        chr = stream->_buf_base[stream->buffer_offset];
        
        stream->buffer_offset++;
        stream->_file_pointer_pos++;
    }

    if(chr<0){
            PRINT_MY_ERROR("Invalid character");
            return SO_EOF;
        }

    return chr;
}

long so_ftell(SO_FILE* stream) {

	return stream->_file_pointer_pos;
}

static int ReadIntoBuffer(SO_FILE *stream)
{
    int readBytes = 0;

#if defined(__linux__)
    readBytes = read(stream->fd, stream->_buf_base, SO_BUFFER_SIZE);
    if (readBytes == -1)
    {
        PRINT_MY_ERROR("read failed");
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

    stream->_buf_end = stream->_buf_base + readBytes;
    return SO_TRUE;
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