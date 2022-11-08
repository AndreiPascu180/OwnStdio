#include "so_stdio.h"
#include "so_handle.h"
#include "utils.h"

int so_fflush(SO_FILE *stream)
{
    if (stream->last_operation == 'w')
    {
        int count_written = 0;

        while (count_written < stream->buffer_offset)
        {
            int written_size = write(stream->fd,
                                     stream->_buf_base + count_written,
                                     stream->buffer_offset - count_written);

            if (written_size == SO_EOF)
            {
                PRINT_MY_ERROR("fflush failed");
                return SO_EOF;
            }
            count_written += written_size;
        }
        memset(stream->_buf_base, 0, SO_BUFFER_SIZE);
        stream->buffer_offset = 0;
        stream->readChars = SO_BUFFER_SIZE;
    }
    return 0;
}