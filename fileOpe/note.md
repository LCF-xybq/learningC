# 文件操作

## 目录

1. 文件的 “管理信息”，包括文件的创建 / 修改日期和它的访问权限。其保存于文件的 inode（节点）中，它是文件系统中的一个特殊的数据块，它同时还包含文件的长度和文件在磁盘上的存放位置。
2. 目录是用于保存其他文件的节点号和名字的文件
3. 目录文件中的每个数据项都是指向某个文件结点的链接，删除文件名就等于删除与之对应的链接
4. 删除一个文件，实质是删除该文件对应的目录项，同时指向该文件的链接数减 1。该文件中的数据可能仍能够通过其他指向同一文件的链接访问到。如果某个文件的链接数为 0, 表示该节点及指向的数据不再被使用，磁盘上的相应位置会被标记为可用空间



## 底层文件访问

### write 系统调用

1. write的作用是把缓冲区 buf的前 nbytes 个字节写入与文件描述符 fildes 关联的文件中，返回实际写入的字节数。

```c
#include <unistd.h>

size_t write(int fildes, const void *buf, size_t nbytes);
```



### read 系统调用

1. read 的作用是从与文件描述符 fildes相关联的文件里读入 nbytes个字节的数据，并把它们放到数据去 buf中，返回实际读入的字节数。

```c
#include <unistd.h>

size_t read(int fildes, const void *buf, size_t nbytes);
```

```c
int main() {
	char buffer[128];
	int nread;
	
	nread = read(0, buffer, 128);
	if (nread == -1) {
		write(2, "read err",  8);
	}
	
	if ((write(1, buffer, nread)) != nread) {
		write(2, "read err", 8);
	}
	exit(0);
}
```

1. 调用

```shell
$ echo hello there | ./simple_read
hello there
$ ./simple_read < words.txt
```



### open 系统调用

1. open 建立了一条到文件或设备的访问路径。如果调用成功，它将返回一个可以被 read、write和其他系统调用使用的文件描述符。

```c
int open(const char *path, int oflags);
int open(const char *path, int oflags, mode_t mode);
```

- O_APPEND	把写入数据追加在文件的末尾
- O_TRUNC    把文件长度设置为 0, 丢弃已有内容
- O_CREAT    如果需要，按参数 mode中给出的访问模式创建文件
- O_EXCL    和 O_CREAT 一起用，确保调用者创建出文件。



### 访问权限的初始值

1. 使用带有 O_CREAT的 open，必须使用有 3 个参数的 open
   1. S_IRUSR
   2. ...
2. 在 mode参数中，被设置的位如果在 umask中也被设置了，那么它就会从文件的访问权限中删除。因此用户可以设置自己的环境



### ioctl 系统调用

1. 它提供了一个用于控制设备及其描述符行为和配置底层服务的接口。

```c
#include <unistd.h>

int ioctl(int fildes, int cmd, ...);
```

1. ioctl 对描述符 fildes 引用的对象执行 cmd 参数中给出的操作。根据特定设备所支持操作的不同，它还可能会有一个可选的第三参数



## 标准 I/O 库

### fopen 函数

```c
#include <stdio.h>
FILE *fopen(const char *filename, const char *mode);
```

1. fopen 打开 filename参数指定的文件，并把它与一个文件流关联起来。mode 参数指定文件的打开方式
2. stdio库在 FILE结构里使用了一个内部缓冲区，只有在缓冲区满时才进行底层系统调用



### fread 函数

```c
#include <stdio.h>

size_t fread(void *ptr, size_t size, size_t nitems, FILE *stream);
```

1. 从一个文件流里读取数据。数据从文件流 stream读到由 ptr指向的数据缓冲区。size 指定每个数据记录的长度，计数器 nitems给出要传输的记录的个数。返回成功读到数据缓冲区里的记录个数（而不是字节数）



### unlink, link 和 symlink 系统调用

```c
#include <unistd.h>

int unlink(const char *path);
int link(const char *path1, const char *path2);
int symlink(const char *path1, const char *path2);
```

1. unlink 系统调用删除一个文件的目录项，并减少它的链接数。
2. 如果一个文件的链接数减少到零，并且没有进程打开它，这个文件就会被删除。
3. 先用 open创建一个文件，然后对其调用 unlink。用来创建临时文件的技巧
4. link 系统调用将创建一个指向已有文件 path1的新链接。新目录项由 path2给出
5. 注意：一个文件的符号链接并不会增加该文件的链接数，所以它不会像普通（硬）链接那样防止文件被删除

