#include "../include/newfs.h"

//* 文件系统的磁盘读取
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

//* 文件系统的磁盘写回
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

struct inode* newfs_alloc_inode(struct dentry *dentry) {
    struct inode *inode;
    int byte_cursor = 0;
    int bit_cursor  = 0;
    int ino_cursor  = 0;
    int data_cursor = 0;
    int is_find_free_entry  = 0;
    int is_find_free_blk    = 0;

    for(byte_cursor = 0; byte_cursor < BLKS_SZ(super.map_inode_blks); byte_cursor++) {
        for(bit_cursor = 0; bit_cursor < UINT8_BITS; bit_cursor++) {
            if((super.map_inode[byte_cursor] & (0x1 << bit_cursor)) == 0) {
                //* inode位图中找到空闲inode
                super.map_inode[byte_cursor] |= (0x1 << bit_cursor);
                is_find_free_entry = 1;
                break;
            }
            ino_cursor++;
        }
        if(is_find_free_entry) break;
    }

    if(!is_find_free_entry || ino_cursor == super.max_ino) 
        return -ENOSPC;
    //* inode初始化
    inode = (struct inode*)malloc(sizeof(struct inode));
    inode->ino = ino_cursor;
    inode->size = 0;
    inode->dentry = dentry;
    inode->dir_cnt = 0;
    inode->dentrys = NULL;
    // memset(inode->block_pointer, -1, sizeof(inode->block_pointer));
    inode->block_pointer[0] = -1;
    
    // if(IS_FILE(inode)) {
    //* 分配一块数据块
    for(byte_cursor = 0; byte_cursor < BLKS_SZ(super.map_data_blks); byte_cursor++) {
        for(bit_cursor = 0; bit_cursor < UINT8_BITS; bit_cursor++) {
            if((super.map_data[byte_cursor] & (0x1 << bit_cursor)) == 0) {
                //* data位图中找到空闲data块
                super.map_data[byte_cursor] |= (0x1 << bit_cursor);
                is_find_free_blk = 1;
                break;
            }
            data_cursor++;
        }
        if(is_find_free_blk) break;
    }
    if(!is_find_free_blk)
        return -ENOSPC;
    inode->block_pointer[0] = data_cursor;
    // }

    //* 配置dentry
    dentry->inode = inode;
    dentry->ino = inode->ino;

    return inode;
}

struct inode *newfs_read_inode(struct dentry *dentry, int ino) {
    struct inode *inode = (struct inode *)malloc(sizeof(struct inode));
    struct inode_d  inode_d;
    struct dentry *sub_dentry;
    struct dentry_d dentry_d;
    int    dir_cnt = 0;
    int    data = 0;
    //* 读取磁盘inode信息
    if(newfs_driver_read(INO_OFS(ino), (uint8_t *)&inode_d, sizeof(struct inode_d))) {
        printf("**read inode_d error\n");
        return NULL;
    }
    //* 赋值给内存inode
    inode->dir_cnt = 0;
    inode->ino = inode_d.ino;
    inode->size = inode_d.size;
    inode->dentry = dentry;
    inode->dentrys = NULL;
    //* 构建内存索引树，注意inode是在内存中创建，而数据块未创建，是要实时写回的
    if(IS_DIR(inode)) {
        dir_cnt = inode_d.dir_cnt;
        data = inode_d.block_pointer[0];
        for(int i=0; i<dir_cnt; i++) {
            if(newfs_driver_read(DATA_OFS(data) + i * sizeof(struct dentry_d), (uint8_t *)&dentry_d, sizeof(struct dentry_d))) {
                printf("**read dentry_d error\n");
                return NULL;
            }
            sub_dentry = new_dentry(dentry_d.fname, dentry_d.ftype);
            sub_dentry->parent = inode->dentry;
            sub_dentry->ino = dentry_d.ino;
            newfs_alloc_dentry(inode, sub_dentry);

        }
    } 
    // else if (IS_FILE(inode)) {
        inode->block_pointer[0] = inode_d.block_pointer[0];
    // }
    return inode;
}

int newfs_alloc_dentry(struct inode* inode, struct dentry* dentry) {
    if(inode->dentrys == NULL) {
        inode->dentrys = dentry;
    } else {
        dentry->brother = inode->dentrys;
        inode->dentrys = dentry;
    }
    inode->dir_cnt++;
    return inode->dir_cnt;
}

int newfs_sync_inode(struct inode *inode) {
    struct inode_d  inode_d;
    struct dentry*  dentry_cursor;
    struct dentry_d dentry_d;
    int ino = inode->ino;
    inode_d.ino = ino;
    inode_d.size = inode->size;
    inode_d.ftype = inode->dentry->ftype;
    inode_d.dir_cnt = inode->dir_cnt;
    // memset(inode_d.block_pointer, 0, sizeof(inode->block_pointer));
    // inode_d.block_pointer[0] = inode->block_pointer[0];
    memcpy(inode_d.block_pointer, inode->block_pointer, sizeof(inode_d.block_pointer));
    int offset;

    if(newfs_driver_write(INO_OFS(ino), (uint8_t *)&inode_d, sizeof(struct inode_d))) {
        printf("**write back inode_d error\n");
        return -EIO;
    }

    if(IS_DIR(inode)) {
        dentry_cursor = inode->dentrys;
        offset = DATA_OFS(inode->block_pointer[0]);
        while(dentry_cursor) {
            memcpy(dentry_d.fname, dentry_cursor->fname, MAX_NAME_LEN);
            dentry_d.ftype = dentry_cursor->ftype;
            dentry_d.ino = dentry_cursor->ino;
            if(newfs_driver_write(offset, (uint8_t *)&dentry_d, sizeof(struct dentry_d))) {
                printf("**write back dentrydata error\n");
                return -EIO;
            }
            if(dentry_cursor->inode) {
                newfs_sync_inode(dentry_cursor->inode);
            }

            dentry_cursor = dentry_cursor->brother;
            offset += sizeof(struct dentry_d);
        }
        //* 数据实时写回，不需要最后刷写
    } 
    // else if(IS_FILE(inode)) {
    //     ;
    // }

    return 0;
}

struct dentry *newfs_lookup(const char *path, int *is_find, int *is_root) {
    struct dentry *dentry_cursor = super.root_dentry;
    struct dentry *dentry_ret = NULL;
    struct inode *inode;

    int total_lvl = newfs_calc_lvl(path);
    int lvl = 0;
    int is_hit;
    char *fname = NULL;
    char *path_cpy = (char *)malloc(sizeof(path));
    *is_root = 0;
    strcpy(path_cpy, path);

    if(total_lvl == 0) {
        *is_find = 1;
        *is_root = 1;
        dentry_ret = super.root_dentry;
    }
    fname = strtok(path_cpy, "/");
    while(fname) {
        lvl++;
        if(dentry_cursor->inode == NULL) {
            //* 读取ino对应的dentry到dentry_cursor
            newfs_read_inode(dentry_cursor, dentry_cursor->ino);
        }
        inode = dentry_cursor->inode;
        if(IS_FILE(inode) && lvl < total_lvl) {
            // perror("path is not a dir\n");
            printf("**not a dir\n");
            dentry_ret = inode->dentry;
            break;
        }
        if(IS_DIR(inode)) {
            dentry_cursor = inode->dentrys;
            is_hit = 0;
            while(dentry_cursor) {
                if(memcmp(dentry_cursor->fname, fname, strlen(fname)) == 0) {
                    is_hit = 1;
                    break;
                }
                dentry_cursor = dentry_cursor->brother;
            }

            if(!is_hit) {
                *is_find = 0;
                printf("**not found\n");
                dentry_ret = inode->dentry;
                break;
            }

            if(is_hit && lvl == total_lvl) {
                *is_find = 1;
                dentry_ret = dentry_cursor;
                break;
            }
        }
        fname = strtok(NULL, "/");
    }
    if(dentry_ret->inode == NULL) {
        dentry_ret->inode = newfs_read_inode(dentry_ret, dentry_ret->ino);
    }
    return dentry_ret;
}

int newfs_calc_lvl(const char *path) {
    char *str = path;
    int lvl = 0;
    if(strcmp(path, "/") == 0) {
        return lvl;
    }
    while(*str != NULL) {
        if(*str == '/') {
            lvl++;
        }
        str++;
    }
    return lvl;
}

char* newfs_get_fname(const char* path) {
    char ch = '/';
    char *q = strrchr(path, ch) + 1;
    return q;
}

struct dentry* newfs_get_dentry(struct inode* inode, int cur_dir) {
    struct dentry *dentry_cursor = inode->dentrys;
    int cnt = 0;
    while(dentry_cursor) {
        if(cur_dir == cnt) {
            return dentry_cursor;
        }
        cnt++;
        dentry_cursor = dentry_cursor->brother;
    }
    return NULL;
}
// char* mystrrchr(const char* string, char ch) {
//     char *p = string;
//     while(p+1 != '\n') ++p;
//     while(p[0] != ch) --p;
//     return p;
// }