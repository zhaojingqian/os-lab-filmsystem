#ifndef _NEWFS_H_
#define _NEWFS_H_

#define FUSE_USE_VERSION 26
#include "stdio.h"
#include "stdlib.h"
#include <unistd.h>
#include "fcntl.h"
#include "string.h"
#include "fuse.h"
#include <stddef.h>
#include "ddriver.h"
#include "errno.h"
#include "types.h"

struct custom_options 	newfs_options;
struct super 			super;
/******************************************************************************
* SECTION: newfs.c
*******************************************************************************/
void* 			   newfs_init(struct fuse_conn_info *);
void  			   newfs_destroy(void *);
int   			   newfs_mkdir(const char *, mode_t);
int   			   newfs_getattr(const char *, struct stat *);
int   			   newfs_readdir(const char *, void *, fuse_fill_dir_t, off_t,
						                struct fuse_file_info *);
int   			   newfs_mknod(const char *, mode_t, dev_t);
int   			   newfs_write(const char *, const char *, size_t, off_t,
					                  struct fuse_file_info *);
int   			   newfs_read(const char *, char *, size_t, off_t,
					                 struct fuse_file_info *);
int   			   newfs_access(const char *, int);
int   			   newfs_unlink(const char *);
int   			   newfs_rmdir(const char *);
int   			   newfs_rename(const char *, const char *);
int   			   newfs_utimens(const char *, const struct timespec tv[2]);
int   			   newfs_truncate(const char *, off_t);
			
int   			   newfs_open(const char *, struct fuse_file_info *);
int   			   newfs_opendir(const char *, struct fuse_file_info *);
/******************************************************************************
* SECTION: newfs_utils.c
*******************************************************************************/
int				   newfs_driver_read(int offset, uint8_t *out_content, int size);
int 			   newfs_driver_write(int offset, uint8_t *in_content, int size);
int 			   newfs_alloc_dentry(struct inode * inode, struct dentry * dentry);
struct inode*  	   newfs_alloc_inode(struct dentry * dentry);
int 			   newfs_sync_inode(struct inode * inode);
struct inode*  	   newfs_read_inode(struct dentry * dentry, int ino);
struct dentry*	   newfs_lookup(const char *path, int *is_find, int *is_root);
int 			   newfs_calc_lvl(const char *path);
char* 			   newfs_get_fname(const char* path);
// char* 			   mystrrchr(const char* string, char ch);

#endif  /* _newfs_H_ */