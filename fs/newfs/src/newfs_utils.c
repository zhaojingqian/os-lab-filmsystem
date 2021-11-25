#include "../include/newfs.h"

int newfs_driver_read(int offset, uint8_t *out_content, int size) {
    int offset_aligned = ROUND_DOWN(offset, IO_SZ());
    int bias           = offset -offset_aligned;
    int size_aligned   = ROUND_UP((size+bias), IO_SZ());
    uint8_t* temp_content   = (uint8_t*)malloc(size_aligned);
    uint8_t* cur            = temp_content;

    ddriver_seek(DRIVER(), offset_aligned, SEEK_SET);
    while(size_aligned != 0) {
        ddriver_read(DRIVER(), cur, IO_SZ());
        cur          += IO_SZ();
        size_aligned -= IO_SZ();
    }
    memcpy(out_content, temp_content+bias, size);
    free(temp_content);
    return 0;
}

int newfs_driver_write(int offset, uint8_t *in_content, int size) {
    int offset_aligned = ROUND_DOWN(offset, IO_SZ());
    int bias           = offset -offset_aligned;
    int size_aligned   = ROUND_UP((size+bias), IO_SZ());
    uint8_t* temp_content   = (uint8_t*)malloc(size_aligned);
    uint8_t* cur            = temp_content;

    newfs_driver_read(offset_aligned, temp_content, size_aligned);
    memcpy(temp_content+bias, in_content, size);
    ddriver_seek(DRIVER(), offset_aligned, SEEK_SET);

    while(size_aligned != 0) {
        ddriver_write(DRIVER(), cur, IO_SZ());
        cur          += IO_SZ();
        size_aligned -= IO_SZ();
    }
    free(temp_content);
    return 0;
}

