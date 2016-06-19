#ifndef __BITRW_H__
#define __BITRW_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
    int fd;

    int curr_pos;
    /* TODO: make it be extendible not just a byte*/
    unsigned char data;

    int first_write;
    int first_read;
} bitrw_data, *bitrw_data_ptr;

int bitrw_init(const char *file_name);
void bitrw_deinit(void);

int bitrw_read(void);
void bitrw_write(int val, int flush);
void bitrw_flush(void);

#ifdef __cplusplus
}
#endif

#endif /* __BITRW_H__ */
