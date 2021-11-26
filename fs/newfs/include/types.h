#ifndef _TYPES_H_
#define _TYPES_H_

/****************************************************************/
#define UINT32_BITS         32
#define UINT8_BITS          8

#define MAGIC               0x52415453
#define DEFAULT_PERM        0777
#define SUPER_OFS           0
#define ROOT_INO            0

// #define INODE_PER_FILE    1
#define MAX_BLOCK           4

#define MAX_NAME_LEN        128  
/****************************************************************/

/****************************************************************/
typedef enum file_type {
    FIL,           // 普通文件
    DIR             // 目录文件
} FILE_TYPE;
/****************************************************************/

/****************************************************************/
#define IO_SZ()           512
#define DISK_SZ()         4*1024*1024
#define DRIVER()          (super.fd)
#define BLOCK_SZ()        1024

#define ROUND_DOWN(value, round)  (value % round == 0 ? value : (value / round) * round)
#define ROUND_UP(value, round)    (value % round == 0 ? value : (value / round + 1) * round)

#define BLKS_SZ(blks)             (blks * BLOCK_SZ())
#define ASSIGN_FNAME(psfs_dentry, _fname)\
        memcpy(psfs_dentry->fname, _fname, strlen(_fname))
// #define INO_OFS(ino)              (super.data_offset + ino * BLK_SZ(INODE_PER_FILE + DATA_PER_FILE))
#define INO_OFS(ino)              (super.inode_offset + ino * sizeof(struct inode))
#define DATA_OFS(data)            (super.data_offset + data * BLOCK_SZ())

#define IS_DIR(pinode)            (pinode->dentry->ftype == DIR)
#define IS_FILE(pinode)            (pinode->dentry->ftype == FIL)
/****************************************************************/

/****************************************************************/
struct custom_options {
	const char*        device;
};

struct super {
    int             fd;

    // int             sz_io;
    // int             sz_disk;

    int             max_ino;
    uint8_t*        map_inode;
    int             map_inode_blks;
    int             map_inode_offset;

    uint8_t*        map_data;
    int             map_data_blks;
    int             map_data_offset;

    int             inode_blks;
    int             inode_offset;

    int             data_offset;

    struct dentry*  root_dentry;
    /* TODO: Define yourself */
};

struct super_d {
    uint32_t        magic_num;

    int             max_ino;

    int             map_inode_blks;
    int             map_inode_offset;

    int             map_data_blks;
    int             map_data_offset;

    int             inode_blks;
    int             inode_offset;

    int             data_offset;
};

struct inode
{
    uint32_t            ino;                  // 在inode位图中的下标
    int                 size;                 // 文件已占用空间
    int                 dir_cnt;              // 目录项数量
    struct dentry*      dentry;               // 指向该inode的dentry
    struct dentry*      dentrys;              // 所有目录项  
    int                 block_pointer[MAX_BLOCK];     // 数据块指针
};

struct inode_d {
    uint32_t    ino;

    int         size;
    // int         link;
    FILE_TYPE   ftype;
    int         dir_cnt;
    int         block_pointer[MAX_BLOCK]
    /* TODO: Define yourself */
};

struct dentry {
    char            fname[MAX_NAME_LEN];
    struct dentry*  parent;
    struct dentry*  brother;
    uint32_t        ino;
    FILE_TYPE       ftype;
    // int             valid;
    struct inode*   inode;
};

struct dentry_d {
    char        fname[MAX_NAME_LEN];
    uint32_t    ino;

    FILE_TYPE   ftype;
    // int         valid;
    /* TODO: Define yourself */
};

static inline struct dentry* new_dentry(char * fname, FILE_TYPE ftype) {
    struct dentry *dentry = (struct dentry *)malloc(sizeof(struct dentry));
    memset(dentry, 0, sizeof(struct dentry));
    ASSIGN_FNAME(dentry, fname);
    dentry->ftype   = ftype;
    dentry->ino     = -1;
    // dentry->valid   = 0;
    dentry->inode   = NULL;
    dentry->parent  = NULL;
    dentry->brother = NULL;  
}
/****************************************************************/
#endif /* _TYPES_H_ */