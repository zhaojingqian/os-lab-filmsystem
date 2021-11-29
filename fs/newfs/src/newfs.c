#include "../include/newfs.h"
// #include "newfs_utils.c"
/******************************************************************************
* SECTION: 宏定义
*******************************************************************************/
#define OPTION(t, p)        { t, offsetof(struct custom_options, p), 1 }

/******************************************************************************
* SECTION: 全局变量
*******************************************************************************/
static const struct fuse_opt option_spec[] = {		/* 用于FUSE文件系统解析参数 */
	OPTION("--device=%s", device),
	FUSE_OPT_END
};

//  struct super 			super;
/******************************************************************************
* SECTION: FUSE操作定义
*******************************************************************************/
static struct fuse_operations operations = {
	.init = newfs_init,						 /* mount文件系统 */		
	.destroy = newfs_destroy,				 /* umount文件系统 */
	.mkdir = newfs_mkdir,					 /* 建目录，mkdir */
	.getattr = newfs_getattr,				 /* 获取文件属性，类似stat，必须完成 */
	.readdir = newfs_readdir,				 /* 填充dentrys */
	.mknod = newfs_mknod,					 /* 创建文件，touch相关 */
	.write = newfs_write,								  	 /* 写入文件 */
	.read = newfs_read,								  	 /* 读文件 */
	.utimens = newfs_utimens,				 /* 修改时间，忽略，避免touch报错 */
	.truncate = newfs_truncate,						  		 /* 改变文件大小 */
	.unlink = newfs_unlink,							  		 /* 删除文件 */
	.rmdir	= newfs_rmdir,							  		 /* 删除目录， rm -r */
	.rename = newfs_rename,							  		 /* 重命名，mv */

	.open = newfs_open,							
	.opendir = newfs_opendir,
	.access = newfs_access
};
/******************************************************************************
* SECTION: 必做函数实现
*******************************************************************************/
/**
 * @brief 挂载（mount）文件系统
 * 
 * @param conn_info 可忽略，一些建立连接相关的信息 
 * @return void*
 */
void* newfs_init(struct fuse_conn_info * conn_info) {
	/* TODO: 在这里进行挂载 */
	int inode_num;
	int data_num;
	int super_blks;
	int map_inode_blks;
	int map_data_blks;
	int inode_blks;
	int is_init = 0;

	struct super_d super_d;
	struct dentry*	root_dentry;
	struct inode*   root_inode;

	/* 下面是一个控制设备的示例 */
	super.fd = ddriver_open(newfs_options.device);
	if(super.fd < 0) {
		return super.fd;
	}

	//* 读取磁盘超级块数据信息
	if(newfs_driver_read(SUPER_OFS, (uint8_t *)(&super_d), sizeof(struct super_d))!=0)
		return -EIO;
	
	//* 未格式化
	//* 进行位图和节点的估计和分配
	if(super_d.magic_num != MAGIC) {
		super_blks = ROUND_UP(sizeof(struct super_d), BLOCK_SZ()) / BLOCK_SZ();

		data_num 	= DISK_SZ() / BLOCK_SZ();
		map_data_blks  = ROUND_UP(ROUND_UP(data_num, UINT8_BITS), BLOCK_SZ()) / BLOCK_SZ();

		inode_num = ROUND_UP(data_num, MAX_BLOCK) / MAX_BLOCK;
		inode_blks = ROUND_UP(inode_num * sizeof(struct inode_d), BLOCK_SZ()) / BLOCK_SZ();
		map_inode_blks = ROUND_UP(ROUND_UP(inode_num, UINT8_BITS), BLOCK_SZ()) / BLOCK_SZ();
	
		super_d.max_ino = inode_num;
		super_d.map_data_blks = map_data_blks;
		super_d.map_inode_blks = map_inode_blks;
		super_d.inode_blks = inode_blks;

		super_d.map_inode_offset = SUPER_OFS + BLKS_SZ(super_blks);
		super_d.map_data_offset = super_d.map_inode_offset + BLKS_SZ(map_inode_blks);
		super_d.inode_offset = super_d.map_data_offset + BLKS_SZ(map_data_blks);
		super_d.data_offset = super_d.inode_offset + BLKS_SZ(inode_blks);

		is_init = 1;
	}


	//* 数据赋值给全局超级块结构体， 方便调用
	super.max_ino = super_d.max_ino;
	super.map_inode = (uint8_t *)malloc(BLKS_SZ(super_d.map_inode_blks));
	super.map_data = (uint8_t *)malloc(BLKS_SZ(super_d.map_data_blks));

	super.map_inode_blks = super_d.map_inode_blks;
	super.map_data_blks = super_d.map_data_blks;
	super.map_inode_offset = super_d.map_inode_offset;
	super.map_data_offset = super_d.map_data_offset;
	super.data_offset = super_d.data_offset;
	super.inode_blks = super_d.inode_blks;
	super.inode_offset= super_d.inode_offset;


	//* 这里是全局超级块两个位图的赋值， 方便调用
	if(newfs_driver_read(super_d.map_inode_offset, (uint8_t *)(super.map_inode), BLKS_SZ(super_d.map_inode_blks)))
		return -EIO;
	if(newfs_driver_read(super_d.map_data_offset, (uint8_t *)(super.map_data), BLKS_SZ(super_d.map_data_blks)))
		return -EIO;

	//* 根目录的创建
	root_dentry = new_dentry("/", DIR);
	if(is_init) {
		root_inode = newfs_alloc_inode(root_dentry);
		newfs_sync_inode(root_inode);
	}
	

	root_inode = newfs_read_inode(root_dentry, ROOT_INO);
	root_dentry->inode = root_inode;
	super.root_dentry = root_dentry;

	return NULL;
}

/**
 * @brief 卸载（umount）文件系统
 * 
 * @param p 可忽略
 * @return void
 */
void newfs_destroy(void* p) {
	/* TODO: 在这里进行卸载 */
	struct super_d super_d;

	//* 刷写inode和dentry(索引节点回写)
	newfs_sync_inode(super.root_dentry->inode);

	//* 磁盘超级块的更新回写
	super_d.magic_num = MAGIC;
	super_d.max_ino = super.max_ino;
	super_d.map_inode_blks = super.map_inode_blks;
	super_d.map_data_blks = super.map_data_blks;
	super_d.map_inode_offset = super.map_inode_offset;
	super_d.map_data_offset = super.map_data_offset;
	super_d.data_offset = super.data_offset;
	super_d.inode_blks = super.inode_blks;
	super_d.inode_offset= super.inode_offset;

	if(newfs_driver_write(SUPER_OFS, (uint8_t *)&super_d, sizeof(struct super_d)))
		return -EIO;
	//* 索引位图的回写
	if(newfs_driver_write(super_d.map_inode_offset, (uint8_t *)super.map_inode, BLKS_SZ(super_d.map_inode_blks)))
		return -EIO;
	//* 数据位图的回写
	if(newfs_driver_write(super_d.map_data_offset, (uint8_t *)super.map_data, BLKS_SZ(super_d.map_data_blks)))
		return -EIO;

	//* 资源释放
	free(super.map_inode);
	free(super.map_data);

	ddriver_close(super.fd);

	return;
}

/**
 * @brief 创建目录
 * 
 * @param path 相对于挂载点的路径
 * @param mode 创建模式（只读？只写？），可忽略
 * @return int 0成功，否则失败
 */
int newfs_mkdir(const char* path, mode_t mode) {
	/* TODO: 解析路径，创建目录 */
	int is_find, is_root;
	char *fname;
	struct dentry* last_dentry = newfs_lookup(path, &is_find, &is_root);
	struct dentry* dentry;
	struct inode*  inode;
	if(is_find) {
		perror("already exists\n");
		return -EEXIST;
	}
	if(IS_FILE(last_dentry->inode)) {
		perror("not a dir");
		return -ENXIO;
	}

	fname = newfs_get_fname(path);
	dentry = new_dentry(fname, DIR);
	dentry->parent = last_dentry;
	inode = newfs_alloc_inode(dentry);
	newfs_alloc_dentry(last_dentry->inode, dentry);

	return 0;
}

/**
 * @brief 获取文件或目录的属性，该函数非常重要
 * 
 * @param path 相对于挂载点的路径
 * @param newfs_stat 返回状态
 * @return int 0成功，否则失败
 */
int newfs_getattr(const char* path, struct stat * newfs_stat) {
	/* TODO: 解析路径，获取Inode，填充newfs_stat，可参考/fs/simplefs/sfs.c的sfs_getattr()函数实现 */
	int is_find, is_root;
	struct dentry* dentry = newfs_lookup(path, &is_find, &is_root);
	if(is_find == 0) {
		// perror("not found\n");
		return -ENOENT;
	}
	if(IS_DIR(dentry->inode)) {
		newfs_stat->st_mode = S_IFDIR | DEFAULT_PERM;
		newfs_stat->st_size = dentry->inode->dir_cnt * sizeof(struct dentry_d);
	}
	else if(IS_FILE(dentry->inode)) {
		newfs_stat->st_mode = S_IFREG | DEFAULT_PERM;
		newfs_stat->st_size = dentry->inode->size;
	}
	newfs_stat->st_nlink = 1;
	newfs_stat->st_uid 	 = getuid();
	newfs_stat->st_gid 	 = getgid();
	newfs_stat->st_atime   = time(NULL);
	newfs_stat->st_mtime   = time(NULL);
	//! 不知道赋值的对错
	newfs_stat->st_blksize = BLOCK_SZ();

	if(is_root) {
		newfs_stat->st_size = 0;
		newfs_stat->st_blocks = DISK_SZ() / BLOCK_SZ();
		newfs_stat->st_nlink  = 2;
	}
	return 0;
}

/**
 * @brief 遍历目录项，填充至buf，并交给FUSE输出
 * 
 * @param path 相对于挂载点的路径
 * @param buf 输出buffer
 * @param filler 参数讲解:
 * 
 * typedef int (*fuse_fill_dir_t) (void *buf, const char *name,
 *				const struct stat *stbuf, off_t off)
 * buf: name会被复制到buf中
 * name: dentry名字
 * stbuf: 文件状态，可忽略
 * off: 下一次offset从哪里开始，这里可以理解为第几个dentry
 * 
 * @param offset 第几个目录项？
 * @param fi 可忽略
 * @return int 0成功，否则失败
 */
int newfs_readdir(const char * path, void * buf, fuse_fill_dir_t filler, off_t offset,
			    		 struct fuse_file_info * fi) {
    /* TODO: 解析路径，获取目录的Inode，并读取目录项，利用filler填充到buf，可参考/fs/simplefs/sfs.c的sfs_readdir()函数实现 */
    int is_find, is_root;
	int cur_dir = offset;

	struct dentry *dentry = newfs_lookup(path, &is_find, &is_root);
	struct dentry* sub_dentry;
	struct inode* inode;
	if(is_find) {
		inode = dentry->inode;
		sub_dentry = newfs_get_dentry(inode, cur_dir);
		if(sub_dentry) {
			filler(buf, sub_dentry->fname, NULL, ++offset);
		}
		return 0;
	}
	return -ENOENT;
}

/**
 * @brief 创建文件
 * 
 * @param path 相对于挂载点的路径
 * @param mode 创建文件的模式，可忽略
 * @param dev 设备类型，可忽略
 * @return int 0成功，否则失败
 */
int newfs_mknod(const char* path, mode_t mode, dev_t dev) {
	/* TODO: 解析路径，并创建相应的文件 */
	int is_find, is_root;
	struct dentry *last_dentry = newfs_lookup(path, &is_find, &is_root);
	struct dentry *dentry;
	struct inode *inode;
	char *fname;

	if(is_find == 1) {
		return -EEXIST;
	}
	fname = newfs_get_fname(path);

	if (S_ISREG(mode)) {
		dentry = new_dentry(fname, FIL);
	}
	else if (S_ISDIR(mode)) {
		dentry = new_dentry(fname, DIR);
	}

	dentry->parent = last_dentry;
	inode = newfs_alloc_inode(dentry);
	newfs_alloc_dentry(last_dentry->inode, dentry);
	
	return 0;
}

/**
 * @brief 修改时间，为了不让touch报错 
 * 
 * @param path 相对于挂载点的路径
 * @param tv 实践
 * @return int 0成功，否则失败
 */
int newfs_utimens(const char* path, const struct timespec tv[2]) {
	(void)path;
	return 0;
}
/******************************************************************************
* SECTION: 选做函数实现
*******************************************************************************/
/**
 * @brief 写入文件
 * 
 * @param path 相对于挂载点的路径
 * @param buf 写入的内容
 * @param size 写入的字节数
 * @param offset 相对文件的偏移
 * @param fi 可忽略
 * @return int 写入大小
 */
int newfs_write(const char* path, const char* buf, size_t size, off_t offset,
		        struct fuse_file_info* fi) {
	/* 选做 */
	int is_find, is_root;
	struct dentry *dentry = newfs_lookup(path, &is_find, &is_root);
	struct inode *inode;

	if(is_find == 0) {
		return -ENOENT;
	}

	inode = dentry->inode;

	if(IS_DIR(inode)) {
		return -EISDIR;
	}
	
	if(inode->size < offset) {
		return -ESPIPE;
	}

	int content_offset = DATA_OFS(inode->block_pointer[0]) + offset;
	if(newfs_driver_write(content_offset, buf, size)) {
		printf("**write file error\n");
		return -EIO;
	}
	inode->size = offset+size > inode->size ? offset+size : inode->size;
	return size;
}

/**
 * @brief 读取文件
 * 
 * @param path 相对于挂载点的路径
 * @param buf 读取的内容
 * @param size 读取的字节数
 * @param offset 相对文件的偏移
 * @param fi 可忽略
 * @return int 读取大小
 */
int newfs_read(const char* path, char* buf, size_t size, off_t offset,
		       struct fuse_file_info* fi) {
	/* 选做 */
	int is_find, is_root;
	struct dentry *dentry = newfs_lookup(path, &is_find, &is_root);
	struct inode *inode;

	if(is_find == 0) {
		return -ENOENT;
	}

	inode = dentry->inode;
	if(IS_DIR(inode)) {
		return -EISDIR;
	}

	if(inode->size < offset) {
		return -ESPIPE;
	}

	int content_offset = DATA_OFS(inode->block_pointer[0]) + offset;
	if(newfs_driver_read(content_offset, buf, size)) {
		printf("**read file error\n");
		return -EIO;
	}

	return size;			   
}

/**
 * @brief 删除文件
 * 
 * @param path 相对于挂载点的路径
 * @return int 0成功，否则失败
 */
int newfs_unlink(const char* path) {
	/* 选做 */
	int is_find, is_root;
	struct dentry *dentry = newfs_lookup(path, &is_find, &is_root);
	struct inode *inode;

	if(is_find == 0) {
		return -ENOENT;
	}

	inode =dentry->inode;

	newfs_drop_inode(inode);
	newfs_drop_dentry(dentry->parent->inode, dentry);
	return 0;
}

/**
 * @brief 删除目录
 * 
 * 一个可能的删除目录操作如下：
 * rm ./tests/mnt/j/ -r
 *  1) Step 1. rm ./tests/mnt/j/j
 *  2) Step 2. rm ./tests/mnt/j
 * 即，先删除最深层的文件，再删除目录文件本身
 * 
 * @param path 相对于挂载点的路径
 * @return int 0成功，否则失败
 */
int newfs_rmdir(const char* path) {
	/* 选做 */
	return newfs_unlink(path);
}

/**
 * @brief 重命名文件 
 * 
 * @param from 源文件路径
 * @param to 目标文件路径
 * @return int 0成功，否则失败
 */
int newfs_rename(const char* from, const char* to) {
	/* 选做 */
	int is_find, is_root;
	struct dentry *from_dentry = newfs_lookup(from, &is_find, &is_root);
	struct inode *from_inode;
	struct dentry *to_dentry;
	mode_t mode = 0;

	if(is_find == 0) {
		return -ENOENT;
	}
	if(strcmp(from, to) == 0) {
		return 0;
	}

	from_inode = from_dentry->inode;
	if(IS_DIR(from_inode)) {
		mode = S_IFDIR;
	} else if(IS_FILE(from_inode)) {
		mode = S_IFREG;
	}

	int ret = newfs_mknod(to, mode, NULL);
	if(ret) {
		return ret;
	}

	to_dentry = newfs_lookup(to, &is_find, &is_root);
	newfs_drop_inode(to_dentry->inode);
	to_dentry->ino = from_inode->ino;
	to_dentry->inode = from_inode;

	newfs_drop_dentry(from_dentry->parent->inode, from_dentry);
	return ret;
}

/**
 * @brief 打开文件，可以在这里维护fi的信息，例如，fi->fh可以理解为一个64位指针，可以把自己想保存的数据结构
 * 保存在fh中
 * 
 * @param path 相对于挂载点的路径
 * @param fi 文件信息
 * @return int 0成功，否则失败
 */
int newfs_open(const char* path, struct fuse_file_info* fi) {
	/* 选做 */
	return 0;
}

/**
 * @brief 打开目录文件
 * 
 * @param path 相对于挂载点的路径
 * @param fi 文件信息
 * @return int 0成功，否则失败
 */
int newfs_opendir(const char* path, struct fuse_file_info* fi) {
	/* 选做 */
	return 0;
}

/**
 * @brief 改变文件大小
 * 
 * @param path 相对于挂载点的路径
 * @param offset 改变后文件大小
 * @return int 0成功，否则失败
 */
int newfs_truncate(const char* path, off_t offset) {
	/* 选做 */
	int is_find, is_root;
	struct dentry *dentry = newfs_lookup(path, &is_find, &is_root);
	struct inode *inode;

	if(is_find == 0) {
		return -ENOENT;
	}
	inode = dentry->inode;
	if(IS_DIR(inode)) {
		return -EISDIR;
	}
	inode->size = offset;

	return 0;
}


/**
 * @brief 访问文件，因为读写文件时需要查看权限
 * 
 * @param path 相对于挂载点的路径
 * @param type 访问类别
 * R_OK: Test for read permission. 
 * W_OK: Test for write permission.
 * X_OK: Test for execute permission.
 * F_OK: Test for existence. 
 * 
 * @return int 0成功，否则失败
 */
int newfs_access(const char* path, int type) {
	/* 选做: 解析路径，判断是否存在 */
	int is_find, is_root;
	int is_access_ok = 0;
	struct dentry *dentry = newfs_lookup(path, &is_find, &is_root);
	struct inode *inode;

	switch(type) {
		case R_OK:
			is_access_ok = 1;
			break;
		case F_OK:
			if(is_find)
				is_access_ok = 1;
			break;
		case W_OK:
			is_access_ok = 1;
			break;
		case X_OK:
			is_access_ok = 1;
			break;
		default:
			break;
	}
	return is_access_ok ? 0 : -EACCES;
}	
/******************************************************************************
* SECTION: FUSE入口
*******************************************************************************/
int main(int argc, char **argv)
{
    int ret;
	struct fuse_args args = FUSE_ARGS_INIT(argc, argv);

	newfs_options.device = strdup("/home/guests/190110325/ddriver");

	if (fuse_opt_parse(&args, &newfs_options, option_spec, NULL) == -1)
		return -1;
	
	ret = fuse_main(args.argc, args.argv, &operations, NULL);
	fuse_opt_free_args(&args);
	return ret;
}