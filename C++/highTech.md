## Linux系统编程基础

### 程序执行环境

#### 参数列表

##### Linux命令行规范

- 短参数：以单横开头，后跟单一字符，例：`ls -h`
- 长参数：以双横开头，后跟字符串，例：`ls --help`

##### 程序访问参数列表的方法

- 主函数的参数argc和argv
- 程序接受命令行的输入参数，并解释之

```c++
// 编程程序输出命令行参数
#include <iostream>
using namespace std;
int main(int argc, char* argv[])
{
    cout << "The program name is " << argv[0] << "." << endl;
    if( argc > 1)
    {
        cout << "With " << argc - 1 << "args as follows:" << endl;
        for(int i = 1; i < argc; i++)
            cout << argv[i] << endl;
    }
    else
        cout << "With " << argc - 1 << " arguments." << endl;
    return 0;
}
```

##### 选项数组的定义

- 结构体类型option：系统已定义，直接使用即可

```c++
// 头文件："getopt.h"
struct option
{
    // 选项长名称
    const char* name;
    // 该选项是否具有附加参数；0：无；1：有；2：可选
    int has_arg;
    // 指向整数，用于保存val值，设为0
    int * flag;
    //选项短名称
    int val;
}
```

##### 函数`getopt_long()`

- 函数原型：`int getopt_long(int argc, char * const * argv, const char * short_options, const struct option * long_options, int * long_index);`
- 函数返回值为参数短名称，不存在时返回-1
- 如果长选项，第五参数输出该选项在长选项数组中的索引

###### 参数处理方法

- 使用循环处理所有参数
- 如果遇到错误选项，输出错误消息并终止程序执行
- 处理附加参数时，用全局变量optarg传递其地址
- 完成所有处理后，全局变量optind为收个非可选参数的索引

###### 编写程序，接受如下三个选项并执行正确操作

- `-h/--help`：显示程序用法并退出
- `-o filename / --output filename`：执行文件名
- `-v/ --verbose`：输出复杂信息

```c++
#include <iostream>
#include <cstdlib>
#include <getopt.h>

using namespace std;

const char * program_name;

// 输出程序用法
void OutputInfo( ostream & os, int exit_code )
{
    os << "Usage: " << program_name << "options [filename]" << endl;
    os << "-h --help: Display this usage information." << endl;
    os << "-o --output filename: Write output to file." << endl;
    os << "-v --verbose: Print verbose messages." << endl;
    exit(exit_code);
}

int main(int argc, char* argv[])
{
    // 全部短选项的合并字符串，":"表示带有附加参数
    const char * const short_opts = "ho:v";
    const struct option long_opts[] = 
    {
        {"help", 0, NULL, "h"},
        {"output", 1, NULL, 'o'},
        {"verbose", 0, NULL, "v"},
        {NULL, 0, NULL, 0}
    };
    // 参数指定的输出文件名
    const char * output_filename = NULL;
    // 是否显示复杂信息
    int verbose = 0;
    // 保存程序名
    program_name = argv[0];
    // 如果为长选项，第五个参数输出该选项在长选项数组中的索引
    int opt = getopt_long(argc, argv, short_opts, long_opts, NULL);
    while( opt != -1)
    {
        switch(opt)
        {
            case 'h':		// "-h"或"--help"
                OutputInfo(cout, 0);
            case 'o':		// "-o"或"--output"，附加参数由optarg提供
                //OutputInfo()
                output_filename = optarg;
                break;
            case 'v':		// "-v"或"--verbose"
                verbose = 1;
                break;
            case '?':		// 用户输出了无效参数
                OutputInfo(cerr, 1);
            case -1:		// 处理完毕
                break;
            default:		// 未知错误
                abort();
        }
        opt = getopt_long(argc, argv, short_opts, long_opts, NULL);
    }
    return 0;
}
```



#### 环境变量

##### 典型Linux环境变量

- USER：你的用户名
- HOME：你的主目录
- PATH：分号分隔的Linux查找命令的目录列表

##### shell处理

- shell编程时查看环境变量：`echo $USER`
- 设置新的环境变量：`EDITOR=emacs; export=EDITOR`或`export EDITOR=emacs`

环境变量内部定义格式：`VARIABLE=value`

使用`getenv()`函数返回环境变量的值

使用全局变量`environ`处理环境变量

```c++
#include <iostream>
using namespace std;
extern char ** environ;
int main()
{
    char ** var;
    for(var = environ; *var != NULL; ++var)
        cout << *var << endl;
    return 0;
}
```

编写客户端程序，在用户未定义服务器时使用缺省服务器名称

```c++
#include <iostram>
#include <cstdlib>

int main()
{
    char * server_name = getenv("SERVER_NAME");
    if(!server_name)
        // SERVER_NAME环境变量未设置，使用缺省值
        server_name = "server.yours.com";
    cout << "accessing server" << server_name << endl;
    // ...
    return 0;
}
```



#### 程序退出码

程序：结束时传递给操作系统的整型数据

- 实际上是main()函数的返回值
- 其他函数也可以调用exit()函数返回特定退出码
- 退出码的变量名称经常为exit_code
- 应仔细设计程序退出码，确保它们能够区分不同错误

操作系统：响应程序退出码，如果必要，执行后续处理

- shell编程时查看上一次退出码的命令：`echo $?`

#### 系统调用错误处理

##### 实现逻辑

- C程序使用断言，C++程序使用断言或异常处理机制

##### 两个主要问题

- 系统调用：访问系统资源的手段
- 系统调用失败原因：资源不足；因权限不足而被阻塞；调用无效参数，如无效内存地址或文件描述符；被外部事件中断；不可预计的外部原因
- 资源管理：已分配资源必须在任何情况下爱都能正确释放

##### Linux使用整数标识系统调用错误

- 标准错误码为以“E”开头的全大写宏
- 宏`errno`（使用方法类似全局变量）：表示错误码，位于头文件“errno.h”中
- 每次错误都重写该值，处理错误是必须保留其副本
- 函数`strerror()`：返回宏errno对应的错误说明字符串，位于头文件“string.h”中

```c++
// 将指定文件的拥有者改为指定的用户或组：第一个参数为文件名，
// 第二和第三个参数分别为用户和组id，-1表示不改变
rval = chown(path, user_id, -1);
if(rval)
{
    // 必须存储errno，因为下一次系统调用会修改该值
    int error_code = errno;
    // 操作不成功, chown将返回-1
    assert(rval == -1);
    // 检查errno，进行对应处理
    switch(errno_code)
    {
        case EPERM:					// 操作被否决
        case EROFS:					// PATH位于只读文件系统中
        case ENAMETOOLONG:			// 文件名太长
        case ENOENT:				// 文件不存在
        case ENOTDIR:				// path的某个成分不是目录
        case EACCES:				// path的某个成分不可访问
            cerr << "error when trying to change the ownership of" << path;
            cerr << ": " << strerror(error_code) << endl;
        case EFAULT:				// path包含无效内存地址，有可能为bug
            abort();
        case ENOMEM:				// 核心内存不足
            cerr << strerror(error_code) << endl;
            exit(1);
        default:					// 不可预见错误，最可能为程序bug
            abort();
            
    };
}
```



#### 资源管理

##### 必须予以明确管理的资源类型

- 内存、文件描述符、文件指针、临时文件、同步对象等

##### 资源管理流程

- 步骤1：分配资源
- 步骤2：正常处理流程
- 步骤3：如果流程失败，释放资源并退出，否则执行正常处理流程
- 步骤4：释放资源
- 步骤5：函数返回

```c++
char * ReadFromFile(const char * filename, size_t length)
{
    char * buffer = new char[length];
    if(!buffer)
        return NULL;
    int fd = open(filename, O_RDONLY);				// 以只读模式打开
    if(fd == -1)
    {
        delete[] buffer, buffe = NULL;
        return NULL;
    }
    size_t bytes_read = read(fd, buffer, length);
    if(bytes_read != length) {
        delete[] buffer, buffer = NULL;
        close(ld);
        return NULL;
    }
    close(fd);
    return buffer;
}
```



#### 系统日志

日志：系统或程序运行的记录

系统日志进程：syslogd/rsyslogd

- 两者均为守护（daemon）进程，即在后台运行的进程，没有控制终端，也不会接收用户输入，父进程通常为init进程
- 日志文件一般为“/dev/log”，日志信息一般保存在"/var/log/"目录下
- rsyslogd既能接收用户进程输出的日志，也能接收内核日志；在接收到日志信息后，会输出到特定的日志文件中；日志信息的分发可配置

##### 日志生成函数：`syslog()`

- 头文件：“syslog.h”
- 原型：`void syslog(int priority, const char * msg, ...);`
- 可变参数列表，用于结构化输出
- `priority`：日志优先级，设施值（一般默认为LOG_USER）与日志级别的位或
- 日志级别：
  - LOG_EMERG（0，系统不可用）
  - LOG_ALERT（1，报警，需立即采取行动）
  - LOG_CRIT（2，严重情况）
  - LOG_ERR（3，错误）
  - LOG_WARNING（4，警告）
  - LOG_NOTICE（5，通知）
  - LOG_INFO（6，信息）
  - LOG_DEBUG（7，调试）

##### 日志打开函数：`openlog()`

- 原型：`void openlog(const char * ident, int logopt, int facility);`
- 改变`syslog()`函数的默认输出方式，以进一步结构化日志内容
- ident：标志项，指定添加到日志消息的日期和时间后的字符串
- logopt：日志选项，用于配置`syslog()`函数的行为，取值为：
  - `LOG_PID`（在日志消息中包含程序PID）
  - `LOG_CONS`（如果日志不能记录至日志文件，则打印到终端）
  - `LOG_ODELAY`（延迟打开日志功能，直到第一次调用`syslog()`函数）
  - `LOG_NDELAY`（不延迟打开日志功能）的位或
- facility：用于修改`syslog()`函数的默认设施值，一般维持`LOG_USER`不变

##### 日志过滤函数：`setlogmask()`

- 原型：`int setlogmask(int maskpri)`
- 设置日志掩码，大于`maskpri`的日志级别信息被过滤
- 返回值：设置日志掩码钱的日志掩码旧值

##### 日志关闭函数：`closelog()`

- 原型：`void closelog();`

#### 用户信息

##### UID、EUID、GID和EGID

- 每个进程拥有两个用户ID：UID（真实用户ID）和EUID（有效用户ID）
- EUID的目的：方便资源访问，运行程序的用户拥有该程序有效用户的权限
- 组与用户类似

##### 用户信息处理函数

- 获取真实用户ID：`uid_t_getuid();`
- 获取有效用户ID：`uid_t geteuid();`
- 获取真实组ID：`get_t getgid();`
- 获取有效组ID：`get_t getegid();`
- 设置真实用户ID：`int setuid(uid_t uid);`
- 设置有效用户ID：`int seteuid(uid_t euid);`
- 设置实际组ID：`int setgid(gid_t gid);`
- 设置有效组ID：`int setegid(gid_t egid);`

##### 程序示例

```c++
#include <unistd.h>
#include <stdio.h>

int main()
{
    uid_t uid = getuid(), euid = geteuid();
    printf("uid: %d; euid: %d\n", uid, euid);
    return 0;
}
```



### 输入输出

#### 标准输入输出流

标准输入流：stdin/cin

标准输出流：stdout/cout

- 数据有缓冲，在缓冲区满，程序正常退出、流被关闭或强制刷新（fflush()函数）时输出
- 等到缓冲区满后同时打印多个句号：`while(1) { printf("."); sleep(1); }`

标准错误流：stderr/cerr

- 数据无缓冲，直接输出
- 每秒打印一个句号：`while(1) { fprintf( stderr, "."); sleep(1); }`

#### 文件描述符

#####  文件描述符的意义与目的：在程序中代表文件

- 内核为每个进程维护一个文件打开记录表，文件描述符为该文件在表中的索引值

##### 文件描述符为非负整数，范围从0至OPEN_MAX

- 不同操作系统可能具有不同范围，可以同时打开的文件数目不同

##### 文件描述符的缺点

- 非UNIX/Linux操作系统可能没有文件描述符概念，跨平台编程时建议使用C/C++标准库函数和文件流类

##### 预定义的标准输入输出流的文件描述符

- 标准输入流`stdin: STDIN_FILENO(0)`
- 标准输出流`stdout: STDOUT_FILENO(1)`
- 标准错误流`stderr: STDERR_FILENO(2)`

##### 文件描述符的创建

- Linux中凡物皆文件，操作系统使用统一方式管理和维护
- 很多函数都可通过打开文件或设备的方式创建文件描述符

#### I/O函数

##### 基本与高级I/O函数

- 打开关闭函数open()和close()：前者头文件 “fcntl.h”，后者头文件 "unistd.h"
- 读写函数read()和write()：头文件 "unistd.h"
- 读写函数readv()和writev()：头文件 "sys/uio.h"
- 文件发送函数snedfile()：头文件 “sys/sendfile.h”
- 数据移动函数splice()：头文件 “fcntl.h”
- 文件控制函数fcntl()：头文件 “fcntl.h”

##### 读函数read()

- 原型：ssize_t read(int fd, void * buf, size_t count);
- 目的：将count个字节的数据从文件描述符fd所代表的文件中读入buf所指向的缓存区
- 若文件支持定位，读取时从当前文件偏移量处开始
- 返回值：读取的字节数，0表示文件结尾，失败时返回-1并设置errno

##### 写函数write()

- 原型：`ssize_t write(int fd, const void * buf, size_t count);`
- 目的：将count个字节的数据从buf所指向的缓冲区写入文件描述符fd所代表的文件中
- 参数将返回值得意义与read()相同或类似

##### 分散读函数readv()

- 原型：`ssize_t readv( int fd, const struct iovec * iov, int iovcnt);`
- 目的：将数据从文件描述符所代表的的文件中读到分散的内存块中
- 参数：fd为文件描述符；iov为写入的内存块结构体数组，每个数组元素只有内存基地址iov_base和内存块长度iov_len两个字段；iovcnt为读取的元素个数
- 返回值：读取的内存块数，失败时返回-1并设置errno

##### 集中写函数writev()

- 原型：`ssize_t writev(int fd, const struct iovec * iov, int iovcnt);`
- 目的：将数据从分散的内存中写入文件描述符所代表的文件中
- 参数与返回值的意义与readv()相同或类似

##### 文件发送函数sendfile()

- 原型：`ssize_t sendfile(int out_fd, int in_fd, off_t * offset, int count);`
- 目的：在两个文件描述符所代表的文件间直接传递数据，以避免内核缓存区和用户缓存区之间的数据拷贝，提升程序效率；为网络文件传输而专门设计的函数
- 参数：out_fd为目的文件描述符；in_fd为源文件描述符；offset指定读取时的偏移量，为NULL表示从默认位置开始读取；count为传输的字节数
- 返回值：传输的字节数，失败时返回-1并设置errno

###### 注意事项

- in_fd必须为支持类似mmap()函数的文件描述符，即必须代表真实的文件，不能为套接字和管道；out_fd必须为套接字

##### 数据移动函数splice()

- 原型：`ssize_t splice(int fd_in, loff_t * off_in, int fd_out, loff_t * off_out, ssize_t len, unsigned int flags);`
- 目的：在两个文件描述符所代表的文件间移动数据
- 参数：fd_in为源文件描述符，off_in为输入数据偏移量，若fd_in为管道，则off_in必须设置为NULL；fd_out与off_out的意义类似；len为传输的字节数；flags控制数据如何移动，其取值为`SPLICE_F_MOVE`（新内核无效果）、`SPLICE_F_NONBLOCK`（非阻塞）、`SPLICE_F_MORE`（还有后续数据）和`SPLICE_F_GIFT`（无效果）的位或
- 返回值：传输的字节数，0表示无数据移动，失败时返回-1并设置errno

##### 数据移动函数tee()

- 原型：`ssize_t tee(int fd_in, int fd_out, ssize_t len, unsigned int flags);`
- 目的：在两个文件描述符所代表的的管道间移动数据
- 参数：含义与splice()相同
- 返回值：传输的字节数，0表示无数据移动，失败时返回-1并设置errno

###### 注意事项

- fd_in和fd_out必须为管道文件描述符

##### 文件控制函数fcntl()

- 原型：int fcntl( int fd, int cmd, ...)
- 目的：对文件描述符所代表的文件或设备进行控制操作
- 参数：fd为文件描述符；cmd为控制命令
- 返回值：失败时返回-1并设置errno

###### 常用操作

- 复制文件描述符：`F_DUPFD/F_DUPFD_CLOEXEC`，第三个参数型式long，成功时返回新创建的文件描述符
- 获取或设置文件描述符的标志：`F_GETFD/F_SETFD`，第三个参数前者无，后者型式long，成功时前者返回fd的标志，后者0
- 获取或设置文件描述符状态标志：`F_GETFL/F_SETFL`，第三个参数前者无，后者型式long，成功时前者返回fd的状态标志，后者0
- 获取或设置SIGIO和SIGURG信号的宿主进程PID或进程组的GID；`F_GETOWN/F_SETOWN`，第三个参数前者无，后者型式long，成功时前者返回信号的宿主进程的PID或进程组的GID，后者0
- 获取或设置信号：`F_GETSIG/F_SETSIG`，第三个参数前者无，后者型式long，成功时前者返回信号值，0表示SIGIO，后者0
- 获取或设置管道容量：`F_GETPIPE_SZ/F_SETPIPE_SZ`，第三个参数前者无，后者型式long，成功时前者返回管道容量，后者0

#### 临时文件

##### 使用临时文件时注意事项

- 程序多个进程可能同时运行，他们可能应该使用不同的临时文件
- 必须小心设置文件属性，未授权用户不应具有临时文件访问权限
- 临时文件的生成应该外部不可预测，否则系统容易受到攻击

##### Linux临时文件函数mkstemp()

- 创建名称唯一的临时文件，使用“XXXXXX”作为模板，返回文件描述符
- 如果不希望外界看到临时文件，创建临时文件后应调用unlink()函数将其从目录项中删除，但文件本身仍存在
- 文件采用引用计数方式访问；本程序未结束，可用文件描述符访问该文件；文件引用计数降为0，系统自动删除临时文件

```c++
#include <cstdlib>
#include <cstring>
#include <unistd.h>

// 向临时文件写入数据
int WriteToTempFile(char * buffer, size_t length)
{
    // 创建临时文件， "XXXXXX" 将在生成时被替换，以保证文件名唯一性
    char temp_filename[] = "/tmp/temp_file.XXXXXX";
    int fd = mkstemp(temp_filename);
    // 取消文件链接，不显示该临时文件；关闭文件描述符后，临时文件被删除
    unlink(temp_filename);
    // 向临时文件中写入数据
    write( fd, &length, sizeof(length) );
    write( fd, buffer, length );
    // 返回临时文件的文件描述符
    return fd;
}
// 从临时文件读取数据
char * ReadFromTempFile(int fd, size_t * length)
{
    // 定位到文件开头
    lseek( fd, 0, SEEK_SET );
    // 读取数据，第一个read是读取文件的数据长度，第二个读取的文件数据读入缓冲buffer中
    read( fd, length, sizeof(*length) );
    char * buffer = new char[*length];
    read( fd, buffer, *length );
    // 关闭文件描述符，临时文件将被删除
    close( fd );
    return buffer;
}
```



### 文件系统

#### 实际文件系统

- ext、ext2、ext3、ext4

##### 实际文件系统：组成与功能描述

- 引导块、超级块、索引结点区、数据区
- 引导块：在文件系统开头，通常为一个扇区，存放引导程序，用于读入并启动操作系统
- 超级块：用于记录文件系统的管理信息，不同的文件系统拥有不同的超级块
- 索引结点区：一个文件或一个目录占据一个索引结点，首索引结点为该文件系统的根结点，可以利用根结点将一个文件系统挂在另一个文件系统的非叶结点上
- 数据区：用于存放文件数据或者管理数据

#### 虚拟文件系统VFS

- VFS的特点：只存于内存中，充当实际文件系统与操作系统之间的接口，提供实际文件系统的挂载，并管理实际文件系统
- VFS的构造：系统初始化时构造VFS目录树，建立其数据结构；每个实际文件系统使用`struct file_system_type`结构存储为结点，并形成链表
- VFS的意义与目的：支持多种不同的文件系统，内核以一致的方式处理这些文件系统，从而对用户透明

#### 特殊文件系统/proc

- 从/proc文件系统中抽取信息
- Linux内核的窗口，只存于内存中，并不占用磁盘空间

##### 典型信息

- 进程信息：进程项、进程参数列表、进程环境、进程可执行文件、进程文件描述符、进程内存统计信息等
- 硬件信息：CPU信息、设备信息、PCI总线信息、串口信息等
- 内核信息：版本信息、主机名与域名信息、内存使用等
- 设备、挂载点与文件系统

### 设备

#### 设备类型

##### 设备文件的性质

- 设备文件不是普通的磁盘文件
- 读写设备的数据需要与相应的设备驱动器通信

##### 设备文件的类型

- 字符设备：读写串行数据字节流，如串口、终端等
- 块设备：随机读写固定尺寸数据，如磁盘设备

##### 说明

- 磁盘挂载到文件系统后，使用文件和目录模式操作
- 程序一般不用块设备，内核实现文件系统时使用块设备操作文件

#### 设备号

##### 大设备号（major device number）

- 指定设备对应那个设备驱动器
- 对应关系由内核确定

##### 小设备号（minor device number）

- 区分由设备驱动器控制的单个设备或设备的某个组件

##### 示例

-  3号主设备为IDE控制器，IDE控制器可以连接多个设备（磁盘、磁带、CD-DVD驱动器等）
- 主设备的小设备号为0，而从设备的小设备号为64
- 主设备单独分区的小设备号从0至63，从设备单独分区的小设备号从64开始

#### 设备项

##### 设备项：与文件类似

- 可以使用mv、rm命令移动或删除
- 如果设备支持读写，cp命令可以从（向）设备读取（写入）数据

##### mknod系统调用：创建设备项（文件系统结点）

- 原型：`int mknod( const char * pathname, mode_t mode, dev_t dev );`
- 参数：pathname为设备项包含路径的名称；mode为设备的使用权限与结点类型；当文件类型为`S_IFCHR`或`S_IFBLK`时，dev表示设备的大小设备号，否则忽略
- 设备项仅仅是与设备通信的门户，在文件系统中创建设备项并不意味着设备可用
- 只有超级用户才可以创建设备项

#### 设备目录

操作系统已知的设备目录：/dev

##### 示例

- 硬盘hda为块设备

- 硬盘有一个分区hda1

  ```shell
  % ls -l /dev/hda /dev/hda1
  ```

  

#### 硬件设备

#### 特殊设备

##### `/dev/null`：哑设备

- 任何写入哑设备的数据被抛弃
- 从哑设备读取不到任何数据，例如`cp /dev/null empty-file`命令将创建一个长度为0的空文件

##### `/dev/zero`：零设备

- 行为类似文件，长度无限，但内容全部为0

##### `/dev/full`：满设备

- 行为类似文件，没有空闲空间存储任何数据
- 对满设备的写入总是失败，并将errno设为ENOSPC

##### 随机数设备

###### `/dev/random`和`/dev/urandom`：随机数设备

- C语言的rand()函数生成伪随机数

###### 随机数设备原理

- 人为的行为无法预测，因而是随机的
- Linux内核测量用户的输入活动（如键盘输入和鼠标操作）的时间延迟作为随机数

###### 两者区别

- `/dev/random`：在用户没有输入操作时，阻塞随机数读取进程（没有数据可读取）
- `/dev/urandom`：永不阻塞；在用户没有输入操作时，生成伪随机数代替

#### 设备控制与访问

##### 设备访问

- 像文件一样操作设备

- 示例：想并口设备发送数据

  ```c++
  int fd = open("/dev/lp0", O_WRONLY);
  write( fd, buffer, buffer_length);
  close(fd);
  
  ```

##### 控制硬件设备的函数：ioctl()

- 第一个参数为文件描述符，指定想要控制的设备；第二个参数为控制命令码，指定想要实施的操作

```c++
#include <fcntl.h>
#include <linux/cdrom.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
int main(int argc, char* argv[])
{
    int fd = open(argv[1], O_RDONY);					// 打开参数所表示的设备
    ioctl( fd, CDROMEJECT );							// 弹出CD-ROM
    close(fd);
    return 0;
}
```



### 库

#### 静态库（Archives）

- 后缀一般为 “*.a”
- 使用两目标文件创建单一静态库的编译与链接命令：`ar cr libtest.a test1.o test2.o`
- 链接器搜索静态库时，连接所有已引用而为处理的符号
- 将静态库的链接放置在命令行尾部，确保其引用被正确解析

#### 动态库（Shared Object）

- 共享目标库（类似Windows的DLL），后缀一般为“*.so”
- 编译命令：`g++ -shared -fPIC -o libtest.so test1.o test2.o`
- PIC：位置无关代码（Position-Independent Code）
- 编译器首先链接动态库，其次才是静态库
- 如果要强制链接静态库，编译使用-static选项

#### 标准库与库相关性

##### C标准库：libc

- 数学库单独：libm；需要调用数学函数时，显示链接数学库：`g++ -o compute compute.c -lm`

##### C++标准库：libstdc++

- 编译C++11程序，使用`g++-4.8 -std=c++11`；对于Code::Blocks等集成开发环境，在编译器设置对话框中选中相应的C++11选项

##### 库的相关性

- 链接时需要注意交叉引用被正确解析，例如：libtiff库需要libjpeg库（jpeg图像处理）和libz库（压缩处理）
- 独立库链接：`g++ -static -o tifftest tifftest.c -ltiff -ljpeg -lz`
- 相关库链接：`g++ -o app app.o -la -lb -la`

#### 动态库的装载与卸载

##### 动态库装载函数dlopen()：头文件“dlfun.h”

- 原型：`void * dlopen( const char * filename, int flag );`
- 参数：filename为动态库名称；flag为装载模式，必须为`RTLD_LAZY`或`RTLD_NOW`两者之一，并可与其他装载标识（如`RTLD_GLOBAL`、`RTLD_LOCAL`）组合
- 返回值：类型为`void *`，用以标识动态库句柄；调用失败返回NULL
- 示例：`dlopen("libtest.o", RTLD_LAZY);`

##### 函数查找与装载函数dlsym()

- 原型：`void * dlsym(void * handle, const char * symbol );`
- 参数：handle为动态句柄；symbol为函数名称字符串
- 返回值：目标函数装载在内存中的基地址

##### 动态库卸载函数dlclose()

- 原型：`int dlclose(void * handle)`;
- 参数：hanle为动态库句柄
- 返回值：成功时为0，其它为错误

##### 动态库错误处理函数dlerror ()

- 原型：`char * dlerror();`
- 返回值：其它三个函数调用时最后一次产生的错误描述字符串

##### 调用动态库中的函数，设函数名为g

- 混合C/C++编码时，C函数应封装与`extern "C" { .. }`块中，确保名解析正确工作（C不支持函数重载）
- 连接选项：“-ldl”

```c++
void * handle = dlopen("libtest.o", RTLD_LAZY);
// 声明函数指针指向动态库中的函数，按被调用函数的名称查找
void( *test() )() = dlsym( handle, "g" );
(*test)();		// 使用函数指针调用动态库中的函数
dlclose( handle );
```



### makefile文件

make命令：负责C/C++程序编译与链接

- make根据指定命令进行建构
- 建构规则文件：GNUmakefile、makefile、Makefile

#### makefile文件格式

##### makefile语法

- 基本语法、变量、条件判断、循环、函数

##### makefile文件基本格式

```makefile
target ... : prerequisites ...
[Tab键]		commands
```

##### makefile文件规则

- makefile文件由一系列规则构成
- 规则的目的：构建目标的先决条件是什么以及如何构建目标
- 如果未指定目标，缺省执行第一个目标
- 若prerequisites中有一个以上的文件比target文件更新，执行commands所定义的命令

##### target：目标

- 通常为编译器的文件名，以指定要建构的对象，也可以是执行文件，还可以是标签（操作名称，伪目标）
- 可以为单一目标，也可以为空格分隔的多个目标
- 每个目标都定义一组处理规则，和其相关规则构成规则链

##### prerequisites：先决条件

- 为生成该目标所需要的先决条件或目标（前置条件）
- 一般为空格分隔的文件名，指定目标是否重建的判断标准，即只要有一个先决条件不存在或有过更新，就重建目标
- 若目标先决条件本书需要重建，则匹配该先决条件的目标，执行器对应的命令

##### commands：命令

- 由一行或多行shell命令组成，命令前有Tab键
- 指示如何构建目标，一般为生成目标文件
- 每行命令都在单独的进程中执行，彼此没有继承关系，不能简单传递数据；解决办法：用分号将多余命令数学在单行（此时可用“\”折行），或者为该条规则添加指示".ONESHELL:"

#### 伪目标：操作名称，而不是文件名

- 删除编译后的二进制目标文件，例如：

  ```makefile
  clean:
  	rm -f *.o
  ```

- 执行命令时须指定伪目标：`$ make clean`
- 若当前目录下有clean文件，则此规则不会被执行；此时可用“.PHONY: ckean” 明确指示clean为伪目标；make将跳过文件检查，执行其对应的命令
- 执行清除任务的伪目标一般放置在脚本的最后

##### 伪目标惯例

- all：所有目标的目标，一般编译所有的目标，对同时编译多个程序极为有用
- clean：删除由make创建的文件
- install：安装以编译好的程序，主要任务是完成目标执行文件的拷贝
- print：列出改变过的源文件
- tar：打包备份源程序，形成tar文件
- dist：创建压缩文件，一般将tar文件压缩成Z文件或gz文件
- TAGS：更新所有的目标，以备完整地重编译使用
- check和test：一般用来测试makefile的流程

示例：假设程序主文件“main.c”，使用library库

```makefile
# 注释行
prog : main.o library.o
	cc -o prog main.o library.o
main.o : main.c library.h
	cc -c main.c
library.o : library.c library.h
	cc -c library.c
.PHONY : clean
clean:
	rm main.o library.o
```

#### makefile文件语法

##### 行解析：命令按行解析

- 命令行的行首字符为Tab键，其他行的行首字符不得为Tab键，但可以使用多个空格缩进

##### 换行：命令太长时，行尾用“\”换行

##### 注释：行首字符为“#”的文本行

##### 关闭回显：在行首字符后和命令前添加“@”

- 未关闭回显时，make会首先回显（打印）命令，然后执行命令
- 通常仅在注释和纯显示的echo命令前使用此功能

##### `include filename`：包含其他文件

- 处理模式与C/C++类似
- 行首加"-"；忽略文件包含错误

##### 通配符

- “\*”（任意数目的任意字符），例如“*.c”表示所有C源文件
- “?”（任意一个字符），例如“?.c”表示所有单字符文件名的C源文件
- “[abc]”（存在括号内的某个字符），例如“lib[abc].c”表示第四个字符为“a”、“b”或“c”
- "[0-9]"（存在该集合中的某个字符），例如”lib[0-9].c“表示第四个字符为0~9之间的数字（包含数字0和9）
- “\[^abc]”（存在非括号内的某个字符），例如“lib\[^abc].c”表示第四个字符不是“a”、“b”或“c”

##### 变量

- 基本变量定义：`var_name = value`
- `$(变量名称)`：引用变量（中间无多余空格）；shell变量用“$$”，例如“`@echo $$HOME`”
- 变量在使用时展开，形式上类似宏替换
- 变量的使用场合：目标、先决条件、命令、新的变量

##### 内置变量

- `$(CC)`：当前使用的编译器：`$(MAKE)`：当前使用的make工具

##### 自动变量

- `$@`：当前目标；`$<`：当前目标的收个先决条件；`$?`：比目标更新的所有先决条件；`$^`：所有先决条件；`$(@D)`和`$(@F)`：`$@`的目录名和文件名；`$(<D)`和`$(<F)`：`$<`的目录名和文件名

```makefile
# makefile 样本
objs = main.o library.o

prog:$(objs)
	$(CC) -o prog $(objs)
	@echo "Constructed"
main.o : main.c library.h
	$(CC) -c main.c
library.o : library.c library.h
	$(CC) -c library.c

.PHONY : clean
# 删除所有文件，除了源文件，包括*~所代表的的备份文件
clean:
	rm -f prog $(objs) *~
```

##### 变量定义格式

- var_name = value：在执行时扩展，允许递归，可以使用后续代码中出现的值
- var_name := valie：在定义时扩展，不允许递归，使用右侧的现值，不能使用后续代码中出现的值
- var_-name ?= value：只有在该变量为空时才设置值，否则维持原值
- var_name += value：将值追加到变量的尾部；若变量为定义，则“+=”自动解释为“=”；若变量已定义，则“+=”继承上次的操作符，并追加新值

##### 多行变量

```makefile
define var_name
	@echo "One"
	@echo "Two"
endef
```

- define和endef行首字符不能为Tab键，对齐时可使用空格
- 引用：`$(var_name)`
- 多行变量主要用于定义命令包，使用多行变量要小心，展开时有可能导致脚本错误

##### 目标变量：类似局部变量，仅对本目标规则链有效

- `target ... : var_name = =value`：定义目标变量

##### 静态模式：以“%”通配符

```makefile
target ... : target-pattern : prequisites ...
[Tab键]commands
```

- 目的：用于处理模式相同的多目标
- 示例：每个目标的文件以".o"结尾，先决条件为对应的".c"

```makefile
objs = main.o library.o
$(objs):%.o:%.c
	$(CC) -c $(CFLAGS) $< -o $@
main.o : main.c
	$(CC) -c $(CFLAGS) main.c -o main.o
library.o : library.c
	$(CC) -c $(CFLAGS) library.c -o library.o
```

##### 条件判断基本格式

```makefile
conditional-directive
	text-if-true
endif

conditional-directive
	text-if-true
else
	text-if-false
	
```

##### 可用的条件判断

- 判断两个参数是否相等：`ifeq( arg1, arg2)`、`ifeq 'arg1' 'arg2'`、`ifeq "arg1" "arg2"`
- 判断两个参数是否不等：ifneq（具体格式与ifeq相同）
- 判断某个变量是否已定义：`ifdef variable_name`
- 判断某个变量是否为定义：`ifndef variable_name`

##### 循环：可以在makefile中使用shell循环

```makefile
rulefor:
	for filename in `echo $(objs)`;\
	do \
		rm -f $$filename; \
	done
```

###### 注意事项

- 循环为shell循环，为保证多行命令在同一个进程下执行，必须合并成单条命令并在行尾添加分行标识
- 作作为为可以使用反引号执行命令，所获得的结果集合可以循环的处理集合
- filename本身是shell变量，需使用“$$”引用

##### 函数：像变量一样使用“$()”标识

- `$(function arg1, arg2, ...)`：函数使用，函数名为function，分隔的参数列表，函数参数前后不能有多余的空格
- `$(subst from, to, text)`：make的字符串替换函数，将text中的字符串替换为to，返回替换后的字符串

```makefile
comma := ,
# 定义空值
empty :=
# 定义空格
space := $(empty) $(empty)
foo := a b c
# 将 “a b c” 替换为 “a, b, c”
bar := $(subst $(space), $(comma), $(foo))
```





### 编程实践

#### 第一题

12.1：编写程序，通过随机数设备读取随机数，重新完成习题6.3以及后续练习题7.2。

#### 第二题

12.2：编程程序，测试临时文件的读写访问。

#### 第三题

12.3：编写程序，查看CPU信息和进程信息。信息越全越好，本体将作为课程大作业“Web服务器”的服务

#### 第四题

12.4：为习题12.3编写makefile文件

## 进程

### 进程基本概念

#### 进程的定义

- 进程是描述程序执行过程和资源共享的基本单位
- 主要目的：控制和协调程序的执行

#### 进程相关函数

- 用户与组ID函数：参阅上一讲
- 创建进程：system()、fork()、exec()
- 终止进程：kill()
- 等待进场终止：wait()、waitpid()

#### 进程组

- 定义：由一个或多个相关联的进程组成，目的是为了进行作业控制
- 进程组的主要特征：信号可以发送给进程组中的所有进程，并使该进程组中的所有进程终止，停止或继续运行
- 每个进程都属于某个进程组

#### 进程组函数

- 获取进程组ID：`pid_t getpgid(pid_t pid);`
  - 返回pid进程的进程组ID；若pid为0，则返回当前进程的进阶组ID；出错时返回-1，并设置errno值

- 设置进程组ID：`int setpgid( pid_t pid, pig_t pgid);`
  - 若pid为0，则使用调用者PID；若gpid为0，则将pid进程的进程PID设为进程组ID；成功时返回0，出错时返回-1，并设errno值

#### 会话（session）

- 会话为一个或多个进程组的集合，包括登录用户的全部活动，并具有一个控制终端
- 登录进程为每个用户创建一个会话，用户登录shell进程会成为会话首领，其PID设为会话ID
- 非会话首领进程通过调用setsid()函数创建新会话，并成为首领

#### 进程组函数

- 获取会话ID：`pid_t getsid(pid_t pid);`
  - 返回pid进程的会话ID；若pid为0，则返回当前进程的会话ID；成功时返回会话ID，出错时返回-1，并设置errno值
- 设置会话ID：`pid_t setsid();`
  - 成功时返回新创建的会话ID，出错时返回-1，并设errno值

### 信号

#### 信号（signal）：进程通讯机制

- 信号是发送给进程的特殊异步消息
- 当进程接收到信息时立即处理，此时并不需要完成当前函数调用设置当前代码行
- Linux系统中又有多种信号，各具有不同的意义；系统以数字表示不同信号，程序一般以名引用之

#### 系统信号

- 缺省处理逻辑：终止进程，生成内核转储文件
- 使用“kill -l”命令可查看操作系统支持的信号列表，不同的系统可能有所不同

#### 进程间发送的信号

- `SIGTERM`、`SIGKILL`：终止进程信号，前者是请求（接收信号的进程可以忽略之），后者是强制
- `SIGUSR1`、`SIGUSR2`：用户自定义信号，可用于向进程发送命令

#### 信号处理

- 进程接收到信号后，根据信号配置进行处理
- 缺省配置：在程序没有处理时，确定信号该如何处理
- 程序处理信号的方式：按照信号处理例程的所提供的函数指针来调用它所指定那个函数，函数指针型式是固定的

##### sigaction()函数：设置信号配置

- 原型：`int sigaction( int signum, const struct sigaction * act, struct sigaction * oldact);`
- signum为信号编号，act和oldact分别为指向信号结构体`struct sigaction`的指针，前者为新配置，后者为需要保护老配置

##### 信号结构体`struct sigaction`

- 最重要的成员为`sa_handler`，其其取值为`SIG_DEF`（使用信号缺省配置）、`SIG_IGN`（忽略该信号）或指向信号处理例程的函数指针（以信号编号为参数，无返回值）

##### 处理信号时的注意事项

- 信号时异步操作，当处理信号时，主程序非常脆弱
- 信号处理例程应尽可能短小，它甚至有可能会被新信号所中断
- 尽量不要在信号处理例程中实施I/O操作，也不要频繁调用系统函数或库函数
- 在信号处理例程中进行复杂的赋值操作也是危险的，它可能不是原子操作，因而有可能在执行期间被中断
- 如果需要赋值，使用`sig_ayomic_t`类型的全局变量（在Linux中等价于int，亦即允许整数或指针赋值，更大尺寸数据不允许）

#### 信号处理

```c++
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>
sig_atomic_t sigusrl_count = 0;
extern "C" { void OnSigUsrl( int signal_number ) { ++sigusrl_count; } }
int main()
{
    std::cout << "pid:" << (int)getpid() << std::endl;
    struct sigaction sa;
    memset( &sa, 0, sizeof(sa) );
    sa.sa_handler = &OnSigUsrl;
    sigaction( SIGUSRl, &sa, NULL);
    sleep( 100);		// 在终端中输入kill -s SIGUSRl pid, 信号计数器将递增
    std::cout << "SIGUSRl counts:" << sigusrl_cout << std::endl;
    return 0;
}
```



### 进程管理

#### 进程创建

##### system()函数：用于在程序中执行一条命令

- 原型：`int system( const char * cmd);`
- 在Bourne shell中，系统后创建一个子进程运行被调命令；返回值为shell的退出状态；如果shell不能运行，返回127；如果发生其他错误，返回-1
- 示例：`int ret_val = system("ls -l /");`

##### for()函数：创建当前进程的副本作为子进程

- 原型：`pid_t fork()`
- 返回值0（新创建的子进程）和子进程的PID（父进程）

##### 使用fork()函数创建进程副本

```c++
#include <iostream>
#include <sys/types.h>
#include <unistd.h>
using namespace std;
int main()
{
    cout << "The main program process, with id " << (int)getpid() << endl;
    if( child_pid != 0)
    {
    	cout << "This is the parent process, with id " << (int)getpid() << endl;   
    	cout << "the child's process ID is " << (int)child_pid << endl;
    }
    else
    	cout << "This is the child process, with id " << (int)getpid() << endl;
    return 0;
}

```

##### exec()函数原型

- `itn execl( const char* path, const char * arg, ...);`
- `int execlp( const char* path, const char * arg, ...);`
- `int execle( const char* path, const char * arg, ..., char * const envp[] );`
- `int execv( const char * path, char * const argv[] );`
- `int execvp( const char * file, char * const argv[] );`
- `int execvpe( const char * file, char * const argv[], char * const envp[] );`

##### exec()函数说明

- 函数名称中包括字母“p”（execvp、execlp）：接受程序名作为参数，在当前执行路径中按照程序名查找；不包含字母“p”的，必须提供程序的完整路径
- 函数名称中包含字母“v”（execv、execvp、execve）：接受以NULL结尾的字符串数组格式的参数列表
- 函数名称中包括字母“l”（execl、execlp、execle）：接受C格式的可变参数列表
- 函数名称中包括字母“e“（execve、execle）：接受一个附加的环境参数列表，参数格式为NULL结尾的字符串数组，且字符串的格式为”VARIABLE=value“

##### 基本模式：在程序调用fork()创建一个子进程，然后调用exec()在子进程中执行命令

```c++
#include <iostream>
#include <cstdlib>
#include <sys/types.h>
#include <unistd.h>
int spawn( char * program, char ** args );
int main ()
{
    char * args[] = {"ls", "-l", "/", NULL};
    spawn("ls", args);
    cout << "Done!\n";
    return 0;
}

// 创建一个子进程运行新程序
// program为程序名，arg_list为程序的参数列表；返回值为子进程id
int spawn( char * program, char ** args)
{
    pid_t child_pid = fork();			// 复制进程
    if( child_pid != 0 )				// 此为父进程
        return child_pid;
    else
    {
        execvp( program, args );		// 执行程序，按路径查找
        // 只有发生错误时，该函数才返回
        std::err << "Error occurred when executing execvp.\n";
        abort();
    }
}
```



#### 进程调度

##### 进程调度策略：先进先出，时间片轮转，普通调度，批调度，搞优先级抢先

- 子进程与父进程的调度没有固定顺序；不能假设子进程一定会在父进程之后执行，也不能假设父进程一定在子进程之后执行

##### 进程调度策略函数：头文件“sched.h”

- 获取进程调度策略：`int sched_getscheduler( pid_t pid );`
- 设置进程调度策略：`int sched_setscheduler( pid_t pid );`
- 获取进程调度参数：`int sched_getparam( pid_t pid, struct sched_param * sp);`
- 设置进程调度参数：`int shced_setparam( pid_t pid, const struct sched_param * sp );`

##### 进程优先级调整：头文件“sys/time.h”和“sys/resource.h”

- 改变进程优先级：`int nice( int inc );`（头文件 “unistd.h”）
- 获取进程优先级：`int getpriority( int which, int who );`
- 设置进程优先级：`int setpriority( int which, int who, int prio );`

##### 处理器亲和性：头文件“sched.h”

- 获取进程的处理器亲和性：`int sched_getaffinity( pid_t pid, size_t cpusetsize, cpu_set_t * mask );`
- 设置进程的处理器亲和性：`int sched_setaffinity( pid_t pid, size_t cpusetsize, cpu_set_t * mask );`

#### 进程终止

##### 终止进程函数：kill()

- 头文件“sys/types.h”和“signal.h”
- 原型：`int kill(pid_t pid, int sig );`
- 函数参数：pid为子进程ID，sig应为进程终止信号`SIGTERM`

##### 等待进程结束函数：wait()

- 原型：`pid_t wait(int * status );, pid_t pid, int * status, int options);`
- 阻塞主调进程，直到一个子进程结束
- `WEXITSTATUS`宏：查看子进程的退出码
- `WIFEXITED`宏：确定子进程的退出状态是正常退出，还是未处理信号导致的意外死亡

```c++
#include <iostream>
#include <cstdlib>
#include <sys/types.h>
#include <sys/wait.h>		// 必须包括此头文件，否则与wait共同体冲突
#include <unistd.h>
int spawn( char * program, char ** arg_list);
int main()
{
    char * arg_list = {"ls", "-l", "/", NULL};
    spawn("ls", arg_list);
    int child_status;
    wait( &child_status);	// 等待子进程结束
    if( WIFEXITED( child_status ))	// 判断子进程是否正常退出
        cout << "Exited normally with " << WEXITSTATUS(child_status) << endl;
    else
        cout << "Exited abnormally." << endl;
    cout << "Done!\n";
    return 0;
}
```



#### 僵尸进程

##### 子进程已结束，但父进程未调用wait()函数等待

- 子进程已终止，但没有被正确清除，成为僵尸进程

##### 清除子进程手段

- 父进程调用wait()函数可确保子进程被清除
- 即使子进程在父进程调用wait()函数前已死亡（成为僵尸），其退出状态也可以被抽取出来，然后被清除
- 未清除的子进程自动被init进程收养

```c++
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
int main()
{
    pid_t child_pid;
    child_pid = fork();
    if( child_pid > 0 )			// 父进程，速度睡眠六十秒
        sleep(60);
    else						// 子进程，立即退出
        exit(0);
    return 0;
}
```

#### 子进程异步清除

`SIGCHLD`信号：子进程终止时，向父进程自动发送，编写此信号处理例程，异步清除子进程

```c++
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
sig_atomic_t_child_exit_status;
extern "C" {
    void CleanUp( int sig_num )
    {
        int status;
        wait( &status );			// 清除子进程
        child_exit_status = status; // 存储子进程的状态
    }
}

int main ()
{
    // 处理SIGCHLD信号
    struct sigaction sa;
    memset( &sa, 0, sizeof(sa) );
    sa.sa_handler = &CleanUp;
    sigaction( SIGCHLD, &sa, NULL );
    
    // 正常处理代码在此，例如调用fork()创建子进程
    
    return 0;
}
```



#### 守护进程

- 创建新进程：新进程将成为未来的守护进程
- 守护进程的父进程退出：保证祖父进程确认父进程已结束，且守护进程不是组长进程
- 守护进程创建新进程组合新会话：并成为两者的首进程，此时刚创建的新会话还没有关联控制终端
- 改变工作目录：守护进程一般随系统启动，工作目录不应该继续使用继承的工作目录
- 重设文件权限掩码：不需要继承文件权限掩码
- 关闭所有文件描述符，不需要继承任何打开的文件描述符
- 标准流重定向到/dev/null

```c++
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/fs.h>

int main()
{
    pid_t pid = fork();
    if( pid == -1 )
        return -1;
    else if	( pid != 0)
        exit( EXIT_SUCCESS );
    // 子进程
    if( setsid() == -1 )
        return -2;
    // 设置工作目录
    if( chdir("/") == -1 )
        return -3;
    // 重设文件权限掩码
    umask(0);
    // 关闭文件描述符
    for( int i = 0; i < 3; i++ )
        close(i);
    // 重定向标准流
    open("/dev/null", O_RDWR );		// stdin
    dup(0);							// stdout
    dup(0);							// stderr
    
    // 守护进程的实际工作代码在此
    return 0;
}
```

##### 守护进程创建函数daemon()

- 实现了前述功能，减轻编写守护进程的负担
- 原型：`int daemon( int nochdir, int noclose);`
- 参数：若nochdir非0，不更改工作目录；若noclose非0，不关闭所有打开的文件描述符
- 返回值：成功时返回0， 失败时返回-1，并设置errno值

### 进程间通信

#### 管道

管道：相关进程间的顺序通信

##### 管道的性质与意义

- 管道是允许单项通信的自动同步设备（半双工）
- 数据在写入端写入，在读取端读取
- 管道为串行设备，数据的读取顺序与写入顺序完全相同

##### 管道的用途

- 只能用于有亲缘关系的进程，例如父进程和子进程之间通信

##### 注意事项

- 管道的数据容量有限，一般为一个内存页面
- 如果写入速度超过读取速度，写入进程将阻塞，直到容量有空闲
- 如果读取速度超过写入数据，读取进程将阻塞，直到管道有数据

##### pipe函数：创建管道

- 头文件："unistd.h"和“fcntl.h”
- 原型：`int pipe( int pipefd[2] );`
- 参数：一个包括两个元素的整数数组，元素类型为文件描述符，0号元为读取文件描述符，1号元写入文件描述符
- 返回值：成功时返回0，不成功时返回-1，并设置errno值

```c++
int pipe_fds[2];
int read_fd;
int write_fd;
pipe( pipe_fds );
read_fd = pipe_fds[0];
write_fd = pipe_fds[1];
```

##### 管道通信

```c++
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

const int buf_size = 4096;

// 向stream中写入count次msg
void Write( cosnt char * msg, int count, FILE * stream )
{
    for(; count > 0; --count)
    {
        fprintf( stream, "%s\n", msg );
        fflush( stream );
        sleep(1);
    }
}

// 从stream中读取数据
void Read( File * stream )
{
    char buf[buf_size];
    // 一直读取到流的尾部
    while( !feof(stream) && !ferror(stream) && fgets(buf, sizeof(buf), stream) != NULL)
    {
        fprintf( stdout, "Data received: \n");
        fputs( buf, stdout );
    }
}

int main()
{
    int fds[2];
    pipe( fds );				// 创建管理
    pid_t pid = fork();			// 创建子进程
    if (pid == 0) {				// 子进程
        close(fds[1]);			// 只读取，关闭管道写入端
        // 将文件描述符转换为FILE*，以方便C/C++标准库函数处理
        FILE* stream = fdopen(fds[0], "r");
        Read(stream);			// 从流中读取数据
        close( fds[0] );		// 关闭管道读取端
    }
    else if( pid > 0 ) {		// 父进程
        char buf[buf_size];		// 数据缓冲区，末尾封装两个'\0'
        for(int i = 0; i < buf_size-2; i++)
            buf[i] = 'A' + i % 26;
        buf[buf_size-1] = buf[buf_size-2] = '\0';
        close(fds[0]);			// 只写入，关闭管道读取端
        FILE* stream = fdopen( fsd[1], "w");
        Write( buf, 3, stream );
        close( fsd[1] );		// 关闭管道写入端
    }
    return 0;
}
```

##### 管道重定向

###### 等位文件描述符

- 共享文件的文件位置和状态标志设置

###### dup()函数：将两个文件描述符等位处理

- 原型：`int dup(int oldfd); int dup2( int oldfd, int newfd); `
- 参数：创建oldfd的一份拷贝，单参数版本选择数值最小的未用文件描述符作为新的文件描述符；双参数版本使用newfd作为新的文件描述符，拷贝前尝试关闭newfd
- 返回值：成功时返回新文件描述符，失败时返回-1，并设errno值
- 示例：`dup2( fd, STDIN_FILENO )`关闭标准输入流，然后作为fd的副本重新打开

```c++
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
const int buf_size = 4096;
int main()
{
    int fds[2];
    pipe(fds);				// 创建管道
    pid_t pid = fork();
    if( pid == (pid_t)0 )	// 子进程
    {
        close(fds[0]);		// 关闭管道读取端
        dup2(fsd[1], STDOUT_FILENO);	// 管道挂接到标准输出流
        char * args[] = {"ls", "-l", "/", NULL};	// 使用“ls”命令替换子进程
        execvp(args[0], args);
    }
    else
    {
        close(fds[1]);		// 关闭管道写入端
        char buf[buf_size];
        FILE * stream = fdopen(fds[0], "r");		// 以读模式打开管道读取端，返回文件指针
        fprint( stdout, "Data received:\n");		// 已读取模式打开管道读取端，返回文件指针
        // 在流末结束，未发生读取错误，且能从流中正常读取字符串时，输出读取到的字符串
        while( !feof(stream) && !ferror(stream) && fgets(buf, sizeof(buf), stream) != NULL )
        {
            fputs( buf, stdout );
        }
        close(fds[0]);		// 关闭管道读取端
        waitpid( pid, NULL, 0); // 等待子进程结束
    }
    return 0;
}
```



#### 进程信号量

进程信号量：进程间通信的同步控制机制

##### 进程信号量：System V信号量

- 可以使用同步机制确定进程的前后执行关系
- 头文件：“`sys/types.h`”、“`sys/ipc.h`”和“`sys/sem.h`”

##### 信号量的定义

- 信号量是一类特殊的计数器，其指为非负整数，用于进程或线程同步

##### 信号量的操作

- 等待（wait）操作（P）：信号量的值递减1后返回；如果值为0，则阻塞操作，直到信号量值为正（其他进程或线程释放了信号量），然后递减1后返回。
- 发布（post）操作（V）：信号量的值递增1后返回；如果信号量值原为0，则其中一个等待该信号量的进程或线程取消阻塞

##### Linux信号量实现：两个版本

- 进程信号量多用于进程同步，POSIX标准实现多用于线程同步

##### 使用进程信号量时的注意事项

- 每次创建和管理进程信号量不是一个，而是一个集合（数组），该集合可能包含多个进程信号量
- 使用键值Key关联进程信号量集，但进程信号量集本身由进程信号量的标识符semid标识，函数调用几乎总是使用semid——可以这么理解：semid对内，key对外

##### 获取进程信号量

###### semget()函数：创建或获取进程信号量集

- 原型：`int semget( key_t key, int nsems, int semflg );`
- 参数：key为键值，多个进程可以通过访问统一进程信号量；nsems为需要为需要创建的进程信号量集的进程信号量元素个数（不是进程信号量的信号数），semflg为访问标志
- 返回值：成功时返回进程信号量集的标识符，失败时返回-1，并设置errno值
- 要获取已分配的进程信号量集，使用原先键值查询，此时进程信号量集的元素个数可设置为0
- 键值`IPC_PRIVATE`用于创建当前进程的私有进程信号量集
- 使用`IPC_CREAT`和`IPC_EXCL`创建进程信号量集，后者要求创建新的唯一的进程信号量集，若其存在，则出错

##### 控制进程信号量

###### 控制和管理进程信号量集

- 原型：`int semctl( int semid, int semnum, int cmd, ...);`
- 参数：semid为进程信号量集的标识符，semnum为进程信号量的元素下标，cmd为指定操作，第四个参数arg可有可无，与cmd无关
- 返回值：成功时与cmd有关，失败时返回-1，并设置errno值
- 调用semctl()函数的进程的有效用户ID必须与分配进程信号量集的用户权限匹配

##### 释放（删除）进程信号量集：IPC_RMID

- 最后一个使用进程信号量的进程负责清除进程信号量集
- 进程信号量集释放后，内存自动释放
- 调用说明：cmd为IPC_RMID，semnum被忽略，arg不需要；如果需要arg，定义`union_semun`类型的变量并作为参数，部分系统可能未定义`union semun`类型，需按如下格式补充定义：

```c++
union semun
{
    int							val;			// 供SETVAL使用的值
    struct semid_ds*			buf;			// 供IPIC_STAT、IPC_SET使用的缓冲区
    unsigned short int *		array;			// 供GETALL、SETALL使用的数组
    struct seminfo *			__buf;			// 供IPC_INFO使用的缓冲区
};
```

##### 初始化进程信号量集：SETALL

- 第一个 参数semid为进程信号量集的标识符，第二个参数semnum为0，第三个参数cmd为SETALL，第四个参数arg必须为union semun类型的数据对象
- `union semun`的array字段：指向无符号短整型数组首元素的指针，该数组保存进程信号量集的所有信号量的信号数

##### 其它常用命令参数

- `IPC_STAT`/`IPC_SET`（获取或设置进程信号量信息）、`GETALL`（获取全部信号量的信号数）、`GETVAL`/`SETVAL`（获取或设置单个信号量的信号数）等

##### 获取与释放

```c++
// 获取与key关联的二元信号量集，必要时会分配之
int AcquireBinarySemaphore( key_t key, int sem_flags )
{
    return semget( key, 1, sem_flags );
}
// 释放二元信号量集，单一元素
int ReleaseBinarySemaphore( int semid )
{
    union semun ignored;
    return semctl( semid, 1, IPC_RMID, ignored );
}
// 初始化二元信号量集，单一元素，信号量初始化值为1
int InitializeBinarySemaphore( int semid )
{
    unsigned short int values[1] = { 1 };
    union semun needed = { .array = values; };
    return semctl( semid, 0, SETALL, needed );
}
```

##### 等待与发布

###### 等待与发布进程信号量函数semop()

- 原型：`int semop( int semid, struct sembuf * sops, size_t nsops );`
- 参数：`semid`为待操作的进程信号量集的标识符；sops为操作数组，nsops为操作数组的元素个数
- 返回值：成功时为进程信号量集的标识符，失败时返回-1，并设置errno值

###### `struct sembuf`类型的成员

- sem_num：需要操作的进程信号量集中的信号量元素下标
- sem_op：指定信号量操作的整数（递增或递减信号量的信号数）
  - 如果sem_op为正数，则立即加到信号量上（V操作）
  - 如果sem_op为负数，则从信号量上减去（P操作）
  - 如果会是结果为负数，则阻塞进程，直到信号量的信号数不小于sem_op的绝对值
  - 如果sem_op为0，则阻塞进程，知道信号量的信号数为0
- sem_flg：指定IPC_NOWAIT则不阻塞进程，指定SEM_UNDO则在进程退出时取消操作

```c++
// P原语：等待二元信号量，信号数非正时阻塞

int WaitBinarySemaphore( int semid )
{
    struct sembuf ops[1];
    ops[0].sem_num = 0;
    ops[0].sem_op = -1;
    ops[0].sem_flg = SEM_UNDO;
    return semop( semid, ops, 1 );
}
// V原语：发布二元信号量，增加信号数后立即返回
int PostBinarySemaphore( int semid )
{
    struct sembuf ops[1];
    ops[0].sem_num = 0;
    ops[0].sem_op = 1;
    ops[0].sem_flg = SEM_UNDO;
    return semop( semid, ops, 1 );
}
```



#### 共享内存

共享内存：允许多个进程读写同一片内存区域

##### 共享内存的意义：快捷方便地本地通信机制

- 头文件：“sys/ipc.h”和“sys/shm.h”

##### 共享内存编程原则

- 系统没有对共享内存操作提供任何缺省的同步行为
- 如果需要，程序员自主设计同步策略：使用进程信号量

##### 共享内存使用过程

- 某个进程分配一个内存段，其它需要访问该内存段的进程连接（attach）该内存段
- 完成访问后，进程拆卸（detach）该内存段
- 某个时刻，一个进程释放该内存段

##### Linux内存模型（15:45）

- 每个进程的虚拟地址空间按页（page）编址，页缺省为4096字节（不同硬件架构和操作系统可能不同，使用getpagesize()函数获取系统值）
- 每个进程维持从内存地址到虚拟页面地址的映射
- 多个进程可能使用同一虚拟页面，同样的数据在不同进程中的地址并不需要相同
- 分配新的共享内存段将创建虚拟内存页面，其他进程连接该共享内存段即可访问
- 共享内存段的分配只有由一个进程负责，释放也同样。

##### shmget()函数：获取分配一段共享内存

- 原型：`int shmget(key_t key, size_t size, int shmflg);`
- 参数：key为内存段整数键值，size为内存段分配的字节数（圆整至4096字节整数倍），shmflg为创建共享内存段的位标志

##### 键值参数key

- 其他进程通过键值key访问该内存段，任意设定的键值可能和其它进程的共享内存段键值冲突，使用`IPC_PRIVATE`以确保无冲突

##### 创建标志：`IPC_CREAT`（创建）、`IPC_EXCL`（独占）

- 后者与前者合并使用，如果键值已使用，则创建失败
- 如果未设`IPC_EXCL`，则在键值已经存在时，返回其代表的共享内存段，而不是创建一个新的共享内存段

##### 获取共享内存

###### 位标志参数

- 模式标志：以9位数字表示宿主，组用户和其他人的访问控制权
- 常数位于头文件“sys/stat.h”

###### 返回值：共享内存daunt的标识符

###### 常用模式常数

- `S_IRUSR`和`S_IWUSR`分别表示共享内存段宿主的读写权限
- `S_IRGRP`和`S_IWGRP`分别表示共享内存段组用户的读写权限
- `S_IROTH`和`S_IWOTH`分别表示共享内存段其他人的读写权限

###### 调用示例

- `int seg_id = shmget( shm_key, getpagesize(), IPC_CREAT | S_IRUSR | S_IWUSER );`

##### 连接与拆卸共享内存

###### shmat()函数：连接共享内存

- 原型：`void * shmat( int shmid, const void * shmaddr, int shmflg );`
- 参数：shmid为共享内存段标识符（shmget()的返回值），shmaddr为指针，指向共享内存段的映射地址，如果传递NULL，Linux自动选择合适地址，shmflg为连接标志
- 返回值：成功时返回所连接的共享内存段的地址

###### 连接标志

- `SHM_RND`：shmaddr指定的映射地址向下圆整到页面尺寸的整数倍；如果未指定，则传递shmaddr时必须手工对齐页面地址
- `SHM_RDONLY`：共享内存段组只读

###### shmdt()函数：拆卸共享内存段

- 原型intshmdt( const void * shmaddr);

```c++
#include <stdio.h>
#include <sys/shm.h>
#include <sys/stat.h>
int main ()
{
    struct shmid_ds shmbuf;
    int seg_size;
    const int shared_size = 0x6400;
    // 分配共享内存段
    int seg_id = shmget(IPC_PRIVATE, shared_size, IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);
    // 连接共享内存段
    char * shared_mem = (char *)shmat( seg_id, 0, 0);
    printf("Shared memory attached at %p\n", shared_mem );
    // 获取段尺寸信息
    shmctl( seg_id, IPC_STAT, &shmbuf );
    srg_size = shmbuf.shm_segsz;
    pritnf("Segment size: %d\n", seg_size);
    // 向共享内存区段写入字符串
    sprintf(shared_mem, "Hello, world. ");
    // 拆卸共享内存区段
    shmdt( shared_mem );
    
    // 在不同的地址处理重新连接共享内存区段
    shared_mem = ( char* )shmat( seg_id, (void*) 0x5000000, 0);
    printf("Shared memory reattached at %p \n", shared_mem );
    // 获取共享内存区段中的信息并打印
    printf("%s\n", shared_mem);
    // 拆卸共享内存区段
    shmdt( shared_mem );
    // 释放共享内存区段，与semctl类似
    shmctl( sed_id, IPC_RMID, 0);
    return 0;
}
```



#### 映射内存

映射内存：与共享内存意义相同，但与文件相关联

##### mmap()函数：头文件“sys/mman.h”

- 映射共享文件到内存；文件被分割成页面大小装载；使用内存读写操作访问文件，速度更快；对映射内存的读写自动反映到文件中
- 原型：`void * mmap( void * addr, size_t length, int prot, int flags, int fd, off_t offset);`

###### 函数参数

- addr：映射目的地的内存地址，NULL表示由Linux自动选择合适的内存地址
- length：映射内存的大小，以字节为单位
- prot：指定映射内存的保护权限，为`PROT_READ`（允许读取）、`PROT_WRITE`（允许写入）、`PROT_EXEC`（允许执行）或以上三者的组合
- flags：附加选项标志；为MAP_FIXED（如果指定此标志，则Linux使用用户指定的地址映射文件，地址本身必须页对齐）、MAP_PRIVATE（内存写入不回写至外部文件，本进程保留写入的文件副本）、MAP_SHARED（内存写入立即反映到映射文件中）；MAP_PRIVATE与MAP_SHARED不能混用
- fd：待映射文件的文件描述符
- offset：指定映射数据在文件中的偏移量

###### 函数返回值

- 成功调用时返回映射内存的基地址，失败时返回MAP_FAILED

##### munmap()函数：释放映射内存

- 原型：`int * munmap(void * addr, size_t length );`
- 参数：addr为映射内存的基地址；length为映射内存的大小
- 返回值：成功时返回0，失败时返回-1并设errno值

##### msync()函数：映射内存同步

- 原型：`int msync( void * addr, size_t length, int flags );`
- 参数：addr为映射内存基地址，length为映射内存大小，flags为同步标志：
  - MS_ASYNC：数据更新被调度，但函数返回前并不一定会被执行
  - MS_SYNC：参数更新立即执行，在完成前调用进程被阻塞
  - MS_INVALIDATE：通知其它进程数据已无效，并自动提供新数据
  - MS_ASYNC与MS_SYNC不能混用
- 返回值：成功时返回0， 失败时返回-1并设errno值

```c++
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <wait.h>
#include <iostream>
#include <iomanip>
const int mapped_size = 4096;
const int mapped_count = mapped_size / sizeof(int);
int main( int argc, char * const argv[] )
{
    // 打开文件作为内存映射的对象，确保文件尺寸足够存储2014个整数
    int fd = open(argv[1], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    lseek( fd, mapped_size - 1, SEEK_SET );
    write( fd, "", 1);
    lseek(fd, 0, SEEK_SET );
    int *base = (int *)mmap(0, mapped_size, PROT__READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, fd, 0);
    close( fd );				// 创建映射内存后，关闭文件的文件描述符
    pid_t pid = fork();
    if( pid == (pid_t)0)		// 子进程写入数据
    {
        // 写入数据0 ~ 1023
        for( int i = 0, *p = base; i < mapped_count; *p++ = i++)
            ;
        munmap( base, mapped_size );
    }
    else if( pid > (pid_t)0 )	// 父进程读取数据
    {
        sleep(10);				// 等待10秒
        for(int i = 0, *p = base; i < mapped_count; i++, p++)
            std::cout << std::setw(5) << *p << "";
        std::cout << std::endl;
        munmap( base, mapped_size );
    }
    return 0;
}
```



#### 消息队列

消息队列：在进程间传递二进制块数据

- 数据块具有类别信息，接收方可根据消息类别有选择地接受
- 头文件：“`sys/type.h`”、“`sys/ipc.h`”、“`sys/msg.h`”

##### msgget()函数：创建或获取消息队列

- 原型：`int msgget( ket_t key, int msgflg );`
- 参数：key为键值，标识全局唯一的消息队列；msgflg为创建标志，与semget()标志相同
- 返回值：成功时返回正整数作为消息队列的标识符，失败时返回-1，并设errno值
- 如果用于创建消息队列，相关内核数据结构`struct msqid_ds`将被创建并初始化

##### msgsnd()函数：将消息添加到消息队列中

-  原型：`int msgsnd( int msqid, const void * msg_ptr, size_t msg_sz, int msgflg );`
- 参数：msqid为msgget()返回的消息队列标识符；msg_ptr指向准备发送的消息，msg_sz为消息数据长度；msgflg控制消息发送行为，一般仅支持IPC_NOWAIT标志，即以非阻塞的方式发送消息
- 返回值：成功时，返回0，失败时返回-1，并设errno值

##### 消息缓冲区结构

- msg_ptr指向的数据结构如下

  ```c++
  struct msgbuf
  {
      long int mtype;
      char mtext[512];
  };
  ```

- mtype为消息类别，必须为正整数
- mtext为消息数据，msg_sz为其实际长度

##### msgrcv()函数：从消息队列中获取消息

- 原型：`int msgrcv( int msqid, void * msg_ptr, size_t msg_sz, long int msgtype, int msgflg);`
- 参数：msqid为msgget()返回的消息队列标识符；msg_ptr用于存储接收的消息，msg_sz为消息数据长度；msgtype为消息类别；msgflg控制消息发送行为，可以为IPC_NOWAIT、MSG_EXCEPT（msgtype大于0时，读取第一个非msgtype类别的消息）和MSG_NOERROR的位或
- 返回值：成功时返回0，失败时返回-1，并设errno值
- 消息类别msgtype说明：为0则读取队列第一条消息，大于0则读取队列第一条类别为msgtype的消息，小于0则读取队列中第一个类别比msgtype绝对值小的消息

##### msgctl()函数：控制消息队列的某些属性

- 原型：`int msgctl( int msqid, int cmd, struct msqid_ds * buf);`
- 参数：msqid为msgget()返回的消息队列标识符；cmd指定要执行的命令，支持的命令有：
  - IPC_STAT
  - IPC_SET
  - IPC_RMID
  - IPC_INFO
  - MSG_INFO
  - MSG_STAT
  - buf 的意义与cmd参数有关
- 返回值：成功时返回值取决于cmd参数，失败时返回-1，并设置errno值

#### 套接字

套接字：支持无关进程，设置不同计算机进行通讯



### 进程池

#### 动机：为什么需要引入进程池

- 进程需要频繁创建子进程，以执行特定任务
- 动态创建子进程的过程效率低，客户响应速度较慢
- 动态创建的子进程一般只为单一客户提供服务，当客户较多时，系统中会存在大量子进程，进程切换的开销过高
- 动态创建的子进程为当前进程的完整映像，当前进程必须谨慎地管理系统资源，以防止子进程不适当地复制这些资源

#### 什么是进程池？

- 主进程预先创建一组子进程，并统一管理
- 子进程运行同样代码，具有同样属性，个数多与CPU数目一致，很少超过CPU数目的两倍

#### 进程池的工作原理是什么？

- 主进程充当服务器，子进程充当服务员，按照服务器的需要提供服务
- 在任务到达时，主进程选择一个子进程进行服务
- 相对于动态创建子进程，选择的代价显然更小——这些子进程未来还可以被复用
- 存在多种选择子进程的策略，如随机选择或轮值制度，如共享单一任务队列，还可以使用更加智能化的负责平衡技术
- 父子进程之间应具有传递消息的通道，如管道。共享内存、消息队列等，也可能需要同步机制

### 编程实践

#### 第一题

13.1 编写程序，调用fork()创建子进程，使用二元进程信号量进行同步。提示：在创建子进程前，使用IPC_PRIVATE创建新的二元进程信号量，其创建的进程信号量并不是该进程私有的，子进程可以用过复制的semid访问该二元进程信号量。父进程在等待子进程结束后释放该二元进程信号量

#### 第二题

13.2 编程实现进程池类ProcessPool。提示：（1）进程池应实现为类模板，从而可以针对不同的任务类别构造不同的进程池；（2）每个任务类别的进程池应实现为单子类；（3）可以统一事件源，即统一管理同类的任务序列，典型的策略是实现父子进程通信的信号管道；（4）调度算法随意。

## 线程

### 线程基本概念

#### 线程的定义

- 线程是比进程更小的程序执行单元
- 多个线程可共享全局数据，也可使用专有数据

#### Linux线程支持史

- 1996年，LinuxThreads：基本符合POSIX标准，但效率低下，问题多多
- 2003年，内核2.6：提供线程支持库NPTL（Native POSIX Thread Library for Linux）

#### 内核线程

- 操作系统内核支持多线程调度与执行
- 内核线程使用资源较少，仅包括内核栈和上下文切换时需要的保存寄存器内容的空间

#### 轻量级进程

- 由内核支持的独立调度单元，调度开销小于普通的进程
- 系统支持多个轻量级进程同时运行，每个都与特定的内核线程相关联

#### 用户线程

- 建立在用户空间的多个用户级线程，映射到轻量级进程后调度执行
- 用户线程在用户空间创建、同步和销毁，开销较低
- 每个线程具有独特的ID

#### 使用说明

- 线程功能不属于C/C++标准库，连接时需要用`-pthread`选项
- 线程功能属于C++11标准库，可用C++11提供的thread类定义线程对象，C++11标准库同时提供基本的线程同步机制

#### 进程与线程的比较

- 线程空间不独立，有问题的线程会影响到其他线程；进程空间独立，有问题的进程一般不会影响其他进程
- 创建进程需要额外的性能开销
- 线程用于开发细颗粒并行性，进程用于开发粗颗粒度并行性
- 线程容易共享数据，进程共享数据必须使用进程间通讯机制

### 线程管理

#### 线程创建

##### 线程创建函数

- 头文件：“pthread.h”
- 原型：`int pthread_create(pthread_t *thread, const pthread_attr_t* attr, void * ( *start_routine)(void *), void *arg);`

##### 线程创建流程

- 定义指向pthread_t对象的指针对象，pthread_t对象用于存储新线程的ID
- 定义指向线程属性`pthread_attr_t`对象的指针对象；线程属性对象控制线程与程序其他部分（可能是其它线程）的交互；如果传递NULL，则使用缺省属性构造新线程
- 定义指向线程函数的指针对象，使其指向固定格式的线程函数
- 实现线程函数；线程函数的参数和返回值均为哑型指针；需要传递多个参数时，打包成单个void\*型的指针对象
- 线程退出时使用返回值将数据传递给主调线程；多个结果同样可以打包传递

##### 线程创建说明

- `pthread_create()`函数在线程创建完毕后立即返回，它并不等待线程结束
- 原线程与新线程如何执行与调度有关，程序不得依赖线程先后执行的关系
- 可以使用同步机制确定线程的先后执行关系

##### 线程退出方式

- 线程函数结束执行
- 调用`pthread_exit()`函数显示结束
- 被其他线程撤销

```c++
#include <pthread.h>
#incldue <iostream>
void * PrintAs( void* unused )
{
    while( true )	std::cerr << 'a';
    return NULL;
}

void* PrintZs( void* unused)
{
    while( true )
        std::cerr << 'z';
    return NULL;
}
int main()
{
    pthread_t thread_id;
    pthread_create(&thread_id, NULL, &PrintAs, NULL);
    printZs(NULL);
    return 0;
}
```

#### 线程函数从参数

```c++
#include <pthread.h>
#include <iostream>

class InfoPrinted
{
    public:
	    InfoPrinted( char c, int n): _c(c), _n(n) { }
    	void Show() const { for(int i = 0; i < _n; i++) std::cerr << _c; }
    private:
    	char _c;
    	int _n;
};

void* PrintInfo( void* info )
{
    InfoPrinted* p = reinterpret_cast<InfoPrinted*>(info);
    if(p) p->Show();
    return NULL;
}

// 注意：本程序大部分情况下不会输出任何结果
int main()
{
    pthread_t tid1, tid2;
    // 构造InfoPrinted类的动态对象，作为线程函数参数传递给线程tid1
    // 输出100个'a'
    InfoPrinted* p = new InfoPrinted('a', 100);
    pthread_create(&tid1, NULL, &PrintInfo, reinterpret_cast<void *>(p));
    // 构造InfoPrinted类的动态对象，作为线程函数参数传递给线程tid2
    // 输出100个 'z'
    InfoPrinted* q = new InfoPrinted('z', 100);
    pthread_create(&tid2, NULL, &PrintInfo, reinterpret_cast<void *>(q));
    // 使用本注释替换上述线程，可以看到输出结果，可能仅有部分输出
    // PrintInfo( reinterpret_cast<void *>(q));
    return 0;
}
```

##### 存在的问题：一般不会产生任何输出

- 子线程需要使用主线程的数据，如果主线程介绍，子线程如何访问这些数据？

##### 解决方案：使用`pthread_join()`函数，等待子线程结束

- 原型：`int pthread_join( pthread_t thread, void ** retval);`
- 参数：thread为pthread_t类型的线程ID；retval接收线程返回值，不需要接收返回值时传递NULL

```c++
// 注意：无法确定两线程的执行顺序，多粗输出结果可能不同
int main()
{
    pthread_t tid1, tid2;
    
    InfoPrinted* p = new InfoPrinted('a', 100);
    pthread_create(&tid1, NULL, &PrintInfo, reinterpret_cast<void*>(p));
    
    InfoPrinted* q = new InfoPrinted('z', 100);
    pthread_create(&tid2, NULL, &PrintInfo, reinterpret_cast<void*>(p));
    
    // 等待子线程结束
    pthread_join( tid1, NULL );
    pthread_join( tid2, NULL );
    
    return 0;
}
```

#### 线程函数返回值

```c++
#include <pthread.h>
#include <cmath>
#include <iostream>

void* IsPrime( void* n)
{
    unsigned int p = reinterpret_cast<unsigned int>(n);
    unsigned int i = 3u, t = (unsigned int)sqrt(p) + 1u;
    if( p == 2u )
        return reinterpret_cast<void *>( true );
    if( p % 2u == 0u)
        return reinterpret_cast<void *>(false);
    while( i <= t )
    {
        if( p % i == 0u )
            return reinterpret_cast<void *>(false);
        i += 2u;
    }
    return reinterpret_cast<void *>(true);
}

// 使用g++ main.cpp -pthread -lm -fpermissive编译
// 以防止编译器将void*到int的转型当作错误
int main()
{
    pthread_t tids[8];
    bool primalities[8];
    int t;
    for( i = 0; i < 8; i++ )
        pthread_crate(&tids[i], NULL, &IsPrime, reinterpret_cast<void *>(i+2));
    for( i = 0; i < 8; i++)
        std::cout << primelities[i] << "";
    std::cout << std::endl;
    return 0;
}
```

#### 线程ID

##### pthread_equal()函数：确认线程是否相同

- 原型：`int pthread_equal( pthread_t t1, pthread_t t2 );`

##### pthread_self()函数：返回当前线程的ID

- 原型：`pthread_t pthread_self();`
- 示例：`if( !pthread_equal( pthread_self(), other_rid)) pthread_join( other_tid, NULL );`



#### 线程属性

线程属性：精细调整线程的行为

##### 设置线程属性的流程

- 创建`pthread_attr_t`类型的对象
- 调用`pthread_attr_init()`函数初始化线程的缺省属性，传递指向该线程属性对象的指针
  - 原型：`int pthread_attr_init( pthread_attr_t * attr );`
- 对线程属性进行必要修改
- 调用`pthread_create()`函数时传递指向线程属性对象的指针
- 调用`pthread_attr_destroy()`函数清除线程属性对象，`pthread_attr_t`对象本身没有被销毁，因而可以调用`pthread_attr_init()`函数再次初始化
  - 原型：`int pthread_attr_destroy( pthread_attr_t* attr );`

##### 线程属性说明

- 单一线程属性对象可以用于创建多个线程
- 线程创建后，继续保留线程属性对象本身并没有意义
- 对大多数Linux程序，程序最重要的属性分为分离状态（detach state）

##### 线程分类

- 可联线程（joinable thread）：缺省设置，终止时并不自动清除（类似僵尸进程），主线程必须调用`pthread_join()`获取其返回值，此后才能清除
- 分离线程（detached thread）：结束时自动清除，不能调用`pthread_join()`进行线程同步
- 可联线程可通过`pthread_detach()`函数分离，分离线程不能再次联结
  - 原型：`int pthread_detach( pthread_t thread );`

##### `pthread_attr_setdetachstate()`函数：设置线程分离属性

- 原型：`int pthread_attr_setdetachstate( pthread_attr_t* attr, int detachstate );`
- 传递线程属性对象指针和分离线程设置参数`PTHREAD_CREATE_DETACHED`

##### `pthread_attr_getdetachstate()函数：获取线程分离属性`

- 原型`int pthread_attr_getdetachstate( pthread_attr_t* attr, int * detachstate );`

```c++
#include <pthread.h>
// 线程函数
void* ThreadFunc( void * arg ) { ... }
int main()
{
    pthread_attr_t attr;
    pthread_t thread;
    // 初始化线程属性
    pthread_attr_init( &attr );
    // 设置线程属性的分离状态
    pthread_attr_setdetachstate( &attr, PTHREAD_CREATE_DETACHED );
    // 创建线程 
    pthread_create( &thread, & attr, & ThreadFun, NULL);
    // 清除线程属性对象
    pthread_attr_destroy( &attr );
    // 无需联结该线程
    return 0;
}
```

#### 线程撤销

##### `pthread_cancel`()函数：撤销线程

- 原型：`int pthread_cancel( pthrad_t thread );`
- 已撤销的线程可以联结，且必须联结，已释放其资源，除非其为分离线程

##### 线程撤销的类型与状态

- 异步可撤销：在其执行的任何时刻都可撤销
- 同步可撤销：线程可撤销，但撤销操作首先进入队列排队，在线程执行到特定撤销点时才可撤销
- 不可撤销：撤销不可撤销线程的企图被系统忽略，且没有任何消息反馈

##### `pthread_setcanceltype()`函数：设置线程的撤销类型：

- 原型：`int pthread_setcanceltype( int type, int * oldtype );`
- 参数：type为撤销类型，oldtype用于保存原始线程撤销类型，NULL表示不保存
- `PTHREAD_CANCEL_ASYNCHRONOUS`：线程异步可撤销
- `PTHREAD_CANCEL_DEFERRRED`：线程同步可撤销，即延迟到下一撤销点撤销

##### `pthread_setcancelstate()`函数：设置线程的撤销状态

- 原型：`int pthread_setcancelstate( int state, int * oldstate );`
- 第一个参数state为可撤销状态，第二个参数oldstate用于保存原始线程可撤销状态，NULL表示不保存
- `PTHREAD_CANCEL_ENABLE`：线程可撤销
- `PTHREAD_CANCEL_DISABLE`：线程不可撤销
- 线程的撤销状态可以多次设置

##### `pthread_restcancel()函数`：设置撤销点

- 原型：`void pthread_testcancel();`
- 在线程函数中调用`pthread_testcancel()`函数设置撤销点
- 建议：周期性地设置撤销点，保证线程函数内部每一些代码就有一个撤销点，以保证资源能正确释放

##### 使用撤销状态构造临界点（critical section）

- 临界点：要么全部执行，要么一条都不执行的代码段
- 设置线程的撤销状态，线程一旦进入临界点，就必须等到离开临界区，才可以被撤销

```c++
// 用户转账
void Transfer( double * accounts, int from, int to, double amount )
{
    int ocs;
    // 数据有效性检查代码在此，确保转账操作合法有效
    
    // 将线程设置位不可撤销的，进入临界区
    pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &ocs );
    
    accounts[0] += amount;
    accounts[from] -= amount;
    
    // 恢复线程的撤销状态，离开临界区
    pthread_setcacelstate( ocs, NULL );
}
```



#### 线程局部存储

##### 线程局部存储（thread local storage， TLS）：每个线程的特有数据

- 线程特定数据（thread-specific data）
- 进程的多个线程通过全局堆共享全局数据对象
- 每个线程拥有独立的栈

##### 让线程拥有数据的独立副本：不能简单赋值或读取

- `pthread_key_create()`函数：为线程特定数据创建一个键参数：第一个为指向`pthread_key_t`类型变量的指针（每个线程都可以使用它访问自己的独立数据副本）；第二个参数为指向线程清除函数的指针，如果不存在，传递NULL
- `pthread_setspecific()`函数：设置对应键的值
- `pthread_getspecific()`函数：读取对应键的值

```c++
#include <pthread.h>
#include <stdio.h>
static pthread_key_t tlk;		// 关联线程日志文件指针的键
void WriteToThreadLog( const char * msg )
{
    FILE* fd = (FILE *)pthread_getspecific( tlk );
    fprintf( fp, "%d: %s\n", (int)pthread_self(), msg);
}
void CloseThreadLog( void * fp )
{
    fclsoe( (FILE*)fp );
}
void* THreadFunc( void * args )
{
    char filename[255];
    FILE* fp;
    // 生成与线程ID配套的日志文件名
    sprintf( filename, "thread%d.log", (int)pthread_self() );
    fp = fopen( filename, "w" );
    // 设置线程日志文件指针与键的局部存储关联
    pthread_setspecific( tlk, fp );
    // 向日志中写入数据，不同的线程会写入不同的文件
    WriteToThreadLog("Thread starting..");
    return NULL;
}

int main()
{
    int i;
    pthread_t threads[8];
    // 创建键，使用CloseThreadLog()函数作为其清除程序
    pthread_key_create( &tlk, CloseThreadLog );
    for( i = 0; i < 8; ++i )
        pthread_create( &threads[i], NULL, ThreadFunc, NULL );
    for( i = 0; i < 8; ++i )
        pthread_join( threads[i], NULL );
    pthread_key_delete( tlk );
    return 0;
    
}
```



#### 线程清除

##### 线程清除函数：回调函数，单void*参数，无返回值

- 目的：销毁线程退出或被撤销时未释放的资源

##### `pthread_cleanup_push()`函数：注册线程清除函数

- 原型：`void pthread_cleanup_push( void (*routine)(void*), void * arg);`
- 参数：routine为指向线程清除函数的函数指针，arg为传递给回调函数的附加数据对象

##### `pthread_cleanup_pop()`函数：取消线程清除函数注册

- 原型：`void pthread_cleanup_pop( int execute );`
- 参数：整型值，非0调用回调函数释放资源，0不释放

```c++
#include <malloc.h>
#include <pthread.h>
void * AllocateBuffer( size_t size )
{
    return malloc( size );
}
void DeallocateBuffer( void * buffer )
{
    free(buffer);
}
void DoSomeWork()
{
    void* temp_buffer = AllocateBuffer( 1024 );
    // 注册清除处理函数
    pthre_cleanup_push( DeallocateBuffer, temp_buffer );
    // 此处可以调用pthread_exit()退出线程或者撤销线程
    // 取消注册，传递非0值，实施清除任务
    pthread_cleanup_pop(1);
}
```

##### C++的问题

- 对象的析构函数在线程退出时可能没有机会被调用，因而线程栈上的数据未清除
- 如何保证线程资源被正确释放？

##### 解决方法

- 定义异常类，线程在准备退出时引发异常，然后在异常处理中退出线程执行
- 引发异常时，C++确保析构函数被调用

```c++
#include <pthread.h>
class EThreadExit {
    public:
    	EThreadExit( void * ret_val ): _thread_ret_val(ret_val) { }
    	// 实际退出线程，使用对象构造时的返回值
    	void* DoThreadExit() { pthread_exit(_thread_ret_val ); }
    private:
    	void* _thread_ret_val;
};
void * ThreadFunc( void* arg )
{
    try {
        if( 线程需要立即退出 )
            throw EThreadExit( 线程返回值 );
    }
    catch( const EThreadExit & e )
    {
        e.DoThreadExit();		// 执行线程实际退出动作
    }
    return NULL;
}
```



### 线程同步机制

#### 资源竞争

##### 编程任务

- 存在一个队列任务，多个并发线程同时处理这些任务，每个线程在完成某项任务后，检查任务队列中是否有新任务。如果有，就处理该任务，并将该任务从任务队列中删除。
- 假设：两个线程碰巧完成各自任务，但队列中只有一个任务。
- 可能发生的情况：第一个线程发现任务队列非空，准备接收该任务，但没有完成全部设置。此时操作系统碰巧中断该线程，第二个线程获得了执行，也发现任务队列非空，同样准备接收该任务，但发现已无法正确设置任务队列。
- 最坏情况：第一个线程已经从队列中摘取任务，但是还没有将任务队列设置为空，第二个线程对任务队列的访问导致段错误，系统崩溃。

```c++
// 有问题的程序代码
#include <list>
struct Job;
std::list<Job *> job_queue;
// 线程函数
void * DequeueuJob( void * arg )
{
    if( !job_queue.empty() )
    {
        Job* job = job_queue.front();
        job_queue.pop_front();
        ProcessJob(job);
        delete job, job = NULL;
    }
    return NULL;
}
```



#### 互斥

##### 互斥（mutex）定义与性质：MUTial EXclusion

- 相互独占锁，与二元信号类似
- 一次只有一个线程可以锁定一个数据对象，并访问
- 只有该线程释放锁定，其它线程才能访问该数据对象

##### `pthread_mutex_init()`函数：初始化互斥

- 原型：`int pthread_mutex_init( pthread_mutex_t * mutex, const pthread_mutexattr_t* mutexattr );`
- 参数：mutex为互斥对象，mutexattr为互斥属性对象，NULL表示使用缺省属性
- 可使用预定义PTHREAD_MUTEX_INITIALIZER初始化互斥

##### pthread_mutex_destroy()函数：销毁互斥

- 原型：`int pthread_mutex_destroy( pthread_mutex_t * mutex );`

##### `pthread_mutex_lock()`函数：互斥加锁

- 原型：`int pthread_mutex_lock( pthread_mutex_t * mutex );`
- 如果无法锁定，则调用将阻塞，至该互斥被解除锁定状态；

##### `pthread_mutex_trylock()`函数：互斥加锁

- 原型：`int pthread_mutex_trylock( pthread_mutex_t * mutex );`
- 如果无法锁定，则立即返回，不阻塞

##### `pthread_mutex_unlock()`函数：互斥解锁

- 原型：`int pthread_mutex_unlock( pthread_mutex_t* mutex);`

##### 使用互斥的流程

- 定义`pthread_mutex_t`类型的变量，将其地址作为第一个参数传给`pthread_mutex_init()`函数；初始化函数只需调用一次
- 锁定或尝试锁定该互斥；获得访问权后，执行正常程序代码；并在执行完毕后解锁

##### 互斥属性

- pshared属性：进程共享属性
  - 取值：`PTHREAD_PROCESS_SHARED（跨进程共享）`，`PTHREAD_PROCESS_PRIVATE`（本进程内部共享）
- type属性：互斥类型

##### 互斥type属性

- `PTHREAD_MUTEX_NORMAL`：普通锁
  - 被某个线程锁定后，其他请求加锁的线程将等待
  - 容易导致死锁
  - 解锁被其他线程锁定或已解锁的互斥，将导致不可预期的后果
- `PTHREAD_MUTEX_ERRORCHECK`：检错锁
  - 线程对已被其他线程锁定的互斥加锁，将返回EDEADLK
- `PTHREAD_MUTEX_RECURSIVE`：递归锁
  - 允许线程对互斥多次加锁；解锁次数必须与加锁次数匹配
- `PTHREAD_MUTEX_DEFALT`：默认锁
  - 实现上可能为上述三种之一

##### 互斥属性函数

- 初始化互斥属性对象：`int pthread_mutexattr_init( pthread_mutexatt_t * attr );`
- 销毁互斥属性对象：`int pthread_mutexattr_destroy( pthread_mutexatt_t * attr);`
- 获取pshared属性：`int pthread_mutexattr_getpshared( const pthread_mutex_t* mutex, int * pthread );`
- 设置pshared属性：`int pthread_mutexattr_setpshared( pthread_mutex_t * mutex, int pshared);`
- 获取type属性：`int pthread_mutexattr_gettype( const pthread_mutex_t * mutex, int * type );`
- 设置type属性：`int pthread_mutexattr_settype( pthread_mutex_t * mutex, int type );`

```c++
// 完整程序代码
#include <pthread.h>
#include <iostream>
#include <list>
struct Job {
    Job( int x = 0, int y = 0): x(x), y(y) { }
    int x, y;
};
// 一般要求临界区代码越短越好，执行时间越短越好，使用C++ STL可能并不是好选择
std::list<Job *> job_queue;
pthread_mutex_t job_queuue_mutex = PTHREAD_MUTEX_INITIALIZER;
// 此处作业处理工作仅为示例，简单输出线程ID和作业内容信息
void ProcessJob( Job * job )
{
    std::cout << "Thread " << (int)pthread_self();
    std::cout << "processing (" << job->x << ", " << job->y << ")\n";
    
}
// 处理作业时需要加锁
void* DequeueJob( void * arg )
{
    while( true ) {
        Job * job = NULL;
        pthread_mutex_lock( &job_queue_mutex );
        if( !job_queue.empty() ) {
            job = job_queue.front();	// 获取表头元素
            job_queue.pop_front();		// 删除表头元素
        }
        pthread_mutex_unlock( &job_queue_mutex );
        if( !job )
            break;
        ProcessJob( job );
        delete job, job = NULL;
    }
    return NULL;
}

// 作业入队时需要加锁
void * EnqueueJob( void * arg )
{
    Job * job = reinterpret_cast< Job* >( arg );
    pthread_mutex_lock( &job_queue_mutex );		// 锁定互斥
    job_queue.push_back( job );
    
    // 入队时也输出线程ID和作业内容信息
    std::cout << "Thread " << (int)pthread_self();
    std::cout << " enqueueing (" << job->x << "," << job->y << ")\n";
    
    pthread_mutex_unlock( &job_queue_mutex );	// 解锁
    return NULL;
}
int main()
{
    int i;
    pthread_t threads[8];
    for( i = 0; i < 5; i++ )
    {
        Job * job = new Job( i+1, (i+1)*2 );
        pthread_create( &threads[i], NULL, EnquueueJob, job );
    }
    for( i = 5; i < 8; i++ )
        pthread_create( &threads[i], NULL, DequeueJob, NULL );
    for( i = 0; i < 8; ++i )
    {
        pthread_join( threads[i], NULL );
    }
    return 0;
}
```



#### 死锁

##### 死锁：资源被竞争占用，且无法释放

处理策略：更改互斥类型

- 创建互斥属性`pthread_mutexattr_t`型的对象
- 调用`pthread_mutexattr_init()`函数初始化互斥属性对象，传递其地址
- 调用`pthread_mutexattr_setkind_np()`函数设置互斥类型，函数第一个参数为指向互斥属性对象的指针，第二个参数为`PTHREAD_MUTEX_RECURSIVE_NP`（递归互斥）或`PTHREAD_MUTEX_ERRORCHECK_NP`（检错互斥）
- 调用pthread_mutexattr_destroy()函数销毁互斥属性对象

#### 信号量

##### 问题：如何确保任务队列中有任务可以做？

- 如果队列中没有任务，线程可能退出，后续任务出现时，没有线程可以执行它

##### POSIX标准信号量：头文件“semaphore.h”

- 用于多个线程的同步操作
- 操作方法比进程信号量简单

##### 初始化信号量

- 原型：`int sem_init( sem_t * sem, int pshared, unsigned int value );`
- 参数：sem为信号量对象，pshared为共享属性，value为信号量初始值

##### 等待信号量：P操作

- 原型：`int sem_wait( sem_t * sem );`
- 原型：`int sem_trywait( sem_t * sem );`
- 原型：`int sem_timewait( sem_t * sem, const struct timespc * abs_timeout );`
- 说明：`sem_wait()`在无法操作时阻塞，`sem_trywait()`则立即返回，`sem_timewait()`与`sem_wait()`类似，但有时间限制

##### 发布信号量：V操作

- 原型：`int sem_post( sem_t * sem );`

##### 销毁信号量

- 原型：`int sem_dectroy( sem_t * sem );`

```c++
// 处理作业时需要加锁
void * DequeueJob( void * arg )
{
    while( true )
    {
        Job* job = NULL;
        sem_wait( &job_queue_count );		// 等待作业队列中有新作业
        pthread_mutex_lock( &job_queue_mutex );
        if( !job_queue.empty() )
        {
            job = job_queue.front();		// 获取表头元素
            job_queue.pop_front();			// 删除表头元素
        }
        pthread_mutex_unlock( &job_queue_mutex );
        if( !job )
            break;
        ProcessJob( job );
        delete job, job = NULL;
    }
    return NULL;
}
// 作业入队时需要加锁
void * EnqueueJob( void * arg )
{
    Job job = reinterpret_cast< Job *>( arg );
    pthread_mutex_lock( &job_queue_mutex );		// 锁定互斥
    job_queue.push_back( job );
    
    // 新作业入队，递增信号量
    sem_post( &job_queue_count );
    
    // 入队时也输出线程ID和作业内容信息
    std::count << "Thread" << (int)pthread_self();
    std::count << " enqueueing (" << job->x << ", " << job->y << ")\n";
    
    pthread_mutex_unlick( &job_queue_mutex );	// 解锁
    return NULL;
}
```



#### 条件变量

##### 条件变量的功能与目的

- 互斥用于同步线程对共享数据对象的访问
- 条件变量用于在线程间同步共享数据对象的值

##### 初始化条件变量

- 原型：`int pthread_cond_init( pthread_cond_t * cond, const pthread_condattr_t * cond_attr );`
- 可以用宏`PTHREAD_COND_INITIALIZER`代替

##### 销毁条件变量

- 原型：`int pthread_cond_destroy( pthread_cond_t * cond);`

##### 广播条件变量

- 原型：`int pthread_cond_broadcast( pthread_cond_t * cond);`
- 以广播方式唤醒所有等待目标条件变量的线程

##### 唤醒条件变量

- 原型：`int pthread_cond_wait( pthread_cond_t * cond, pthread_mutex_t * mutex );`
- 参数：mutex为互斥，以确保函数操作的原子性



### C++11线程库

#### 支持平台无关的并行程序开发

##### 库：atomic、thread、mutex、condition_variable、future

- thread：std::thread类与std::this_thread名空间
- mutex：互斥相关类，包括std::mutex系列类，std::lock_guard类、std::unique_lock类及其他型式和函数
- condition_variable：条件变量类，包括std::condition_variable类与std::condition_variable_any类
- atomic：std::atomic类与std::atomic_flag类，另外还有一套C风格的原子型式和原子操作函数
- future：包含两个承诺类（std::promise类、std::packaged_task类）、两个期许类（std::future类、std::shared_future类）及相关型式和函数

#### 线程类：thread

- 支持的线程函数无参数和返回值型式的特别要求，有无参数均可，返回值有无亦可

与Linux线程机制相比，C++11线程类更易用线程局部存储使用thread_local关键字

可派生自己的thread类，但实现上需特别注意

- 线程类应支持移动语义，但不应支持拷贝语义

##### 常用线程类成员函数

- 判断线程是否可联：`bool thread::joinable();`
- 等待线程结束：`void thread::join();`
- 分离线程：`void thread::detach();`

##### 定义于名空间this_thread的线程管理函数

- 获取线程ID：`thread::id get_id();`
- 在处于等待状态时，让调度选择其他线程执行：`void yield();`
- 阻塞当前线程指定时长：`template<typename_Rep, typename_Period> void sleep_for( const chrono::duration< _Rep, _Period >& _rtime );`
- 阻塞当前线程至指定时点：`template< typename_Clock, typename _Duration > void sleep_until( const chroni::time_point< _Click, _Duration>& _atime );`

```c++
// 无参数线程函数
#include <iostream>
#include <thread>

void ThreadFunc()
{
    std::cout << "Thread ID: " << std::this_thread::get_id() << std::endl;
}

int main()
{
    std::thread t( &ThreadFunc );			// 创建线程对象并运行
    t.join();								// 等待线程结束
    return 0;
}

```

```c++
// 带双参数的线程函数
#include <iostream>
#include <thread>
void ThreadFunc( int a, int b )
{
    std::cout << "Thread ID: " << srd::this_thread::get_id() << std::endl;
    std::cout << a << " + " << b << " = " << a + b << std::endl;
    
}

int main()
{
    int m = 10, n = 20;
    // C++11标准库使用可变参数的模板形式参数列表，线程函数参数个数任意
    std::thread t( &ThreadFunc, m, n);
    t.join();
    return 0;
}
```

```C++
// 带双参数的函子对象
#include <iostream>
#include <thread>
class Functor
{
    public:
    	void operator()( int a, int b )
        {
            std::cout << "Thread ID: " << std::this_thread::get_id() << std::endl;
            std::cout << a << " + " << b << " = " << a + b << std::endl;
        }
};
int main()
{
    int m = 10, n = 20;
    std::thread t( Functor(), m, n );
    t.join();
    return 0;
}
```

```c++
// 使用std::bind()函数绑定对象及其普通成员函数
#include <iostream>
#include <thread>
class Worker
{
    public:
    	Worker( int a = 0, int b = 0 ): _a(a), _b(b) { }
    	void ThreadFunc() { ...... }
   	private:
    int _a, _b;
};

int main()
{
    Worker worker( 10, 20 );
    std::thread t( std::bind( &Worker::ThreadFunc, &worker ));
    t.join();
    return 0;
}
```

#### 互斥类

##### 基本互斥：mutex类

- 核心成员函数lock()、try_lock()和unlock()
- 上述成员函数无参数，无返回值

##### 递归互斥：recusive_mutex类

- 允许单个线程对互斥进行多次加锁与解锁处理

##### 定时互斥：timed_mutex类

- 在某个时段里或者某个时刻前获取互斥
- 当线程在临界区操作的时间非常长，可以用定时锁指定时间

##### 定时递归互斥：recusive_timed_mutex类

- 综合timed_mutex和recusive_mutex类

##### 共享定时互斥：shared_timed_mutex类（C++14）

```c++
#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
std::mutex x;
void ThreadFunc()
{
    x.lock();
    std::cout << std::this_thread::get_id() << " is entering..." << std::endl;
    std::this_thread::sleep_for( std::chrono::seconds(3) );
    std::cout << std::this_thread::get_id() << " is leaving..." << std::endl;
    x.unlock();
}

int main()
{
    std::vector<std::thread*> v(8);
    for( int i = 0; i < 8; i++)
        v[i] = new std::thread( ThreadFunc );
    for( int i = 0; i < 8; i++ )
        v[i]->join();
}
```



##### 互斥问题：容易导致死锁

- 若某个线程在临界区内的操作导致异常，有可能无法解锁，从而导致其他线程被永杰阻塞
- 若临界区代码有多路分支，其中部分分支提前结束，但没有执行解锁操作，其他线程依然被永久阻塞
- 当多个线程同时申请多个资源时，加锁次序不同也可能导致死锁

##### 资源获取即初始化（resource acquisition is initialization， RAII）

- 使用互斥对象管理类模板自动管理资源

##### 基于作用域的锁管理类模板：std::lock_guard

- 构造时是否加锁可选，不加锁时假定当前线程已获得锁的所有权 ，析构时自动解锁，所有权不可转移，对象生存期内不允许手动加锁和解锁

##### 独一锁管理类模板：std::unique_lock

- 构造时是否加锁可选，对象析构时如果持有锁会自动解锁，所有权可转移，对象生存期内允许手动加锁和解锁

##### 共享锁管理模板：std::shared_lock（C++14）

- 用于管理可转移和共享所有权的互斥对象

##### 互斥管理策略

- 延迟：std::defer_lock，构造互斥管理对象时延迟加锁操作
- 尝试：std::try_to_lock，构造互斥管理对象时尝试加锁操作，但不阻塞线程，互斥不可用时立即返回
- 接收：std::adpot_lock，假定当前线程已获得互斥所有权，不再加锁
- 缺省行为：构造互斥管理对象时没有传递管理策略标签参数，阻塞当前线程至成功获得互斥

##### 互斥的解锁时机

- 当使用C++11的互斥自动管理策略时，只有析构互斥管理对象时才自动释放互斥，因此要特别注意互斥的持有时间；若线程持有互斥的时间过长，有可能极大降低程序效率
- 解决方案：使用复合语句块或专用辅助函数封装临界区操作；动态创建互斥管理对象，并尽早动态释放

##### 多个互斥的竞争访问

- 多个线程多个互斥加锁时保持顺序一致性，以避免可能的死锁
- 使用std::lock()或std::try_lock()

```c++
// 使用互斥管理策略重新实现线程函数
template< typename T > class Worker
{
    public:
    	explicit Worker(int no, T a = 0, T b = 0 ): _no(no), _a(a), _b(b) { }
    void ThreadFunc( T * r )
    {
        {
            // 使用复合语句块封装临界区操作，块结束时即释放局部对象
            std::lock_guard< std::mutex > locker( x );		// 构造对象的同事加锁
            *r = _x + _y;
        }	// 无需手动解锁，locker对象在析构时自动解锁
    	std::cout << "Thread No:" << _no << std::endl;
    	std::cout << _a << " + " << _b << " = " << _a + _b << std::endl;
    }
    private:
    	int _no;
    	T _a, _b;
};

```

```c++
// 转账处理示例
#include <iostream>
#include <mutex>
#include <thread>

class Account
{
    public:
    	explicit Account( double balance ): _balance(balance) { }
    	double GetBalance() { return _balance; }
    	void Increase( double amount ) { _balance += amount; }
    	void Decrease( double amount ) { _balance -= amount; }
    	std::mutex & GetMutex() { return _x; }
    private:
    	double _balance;
    std::mutex _x;
};

// 避免死锁，使用std::lock()函数所动多个互斥，不同的锁定顺序不会导致死锁
// 加锁时有可能引发异常，std::lock()函数会处理该异常
// 将解锁此前已加锁的部分互斥，然后重新引发该异常
void Treansfer( Account & from, Account & to, double amount )
{
    std::unique_lock<std::mutex> locke1(from.GetMutex(), std::adopt_lock );
    std::unique_lock<std::mutex> locker2(to.GetMutex(), std::adopt_lock );
    from.Decrease( amount );
    to.Increase( amount );
}

int main()
{
    Account a1(100.0), a2(200.0);
    // 线程参数采用值传递机制，如果要传递引用，调用std::ref()函数
    std::thread t1( Transfer, std::ref( a1 ), std::ref( a2 ), 10.0 );
    std::thread t2( Transfer, std::ref( a2 ), std::ref( a1 ), 20.0 );
    t1.join();
    t2.join();
    return 0;
}
```



#### 条件变量

##### std::condition_variable类

- 必须与`std::unique_lock`配合使用

##### `std::condition_variable_any`类

- 更加通用的条件变量，可以与任意型式的互斥锁配合使用，相比前者使用时会有额外的开销

##### 多线程通信同步原语

- 阻塞一个或多个线程至收到来自其他线程的通知，超时或发生虚假唤醒
- 两者具有同样的成员函数，且在等待条件变量前都必须要获得相应的锁

#####  条件变量类

###### 成员函数notify_one()：通知一个等待线程

- 原型：`void motify_one() noexcept;`

###### 成员函数notify_all()：通知全部等待线程

- 原型：`void motify_one() noexcept;`

###### wait()：阻塞当前线程至被唤醒

- 原型：`template< typename Lock > void wait( Lock & lock );`
- 原型：`template< typename Lock, typename Predicate > void wait( Lock & lock, Predicate p);`

###### 成员函数wait_for()：阻塞至被唤醒或超过指定时长

- 原型：`template< typename Lock, typename Rep, typename _priod > cv_status wait_for( Lock& lock, const chrono::duration< Rep, Period >& rtime );`
- 原型：`template< typename Lock, typename Rep, typename Period, typename Predicate > bool wait_for( Lock& lock, const chrono::duration< Rep, Period >& rtime, Predicate p);`

###### 成员函数wait_until()：阻塞至被唤醒或到达指定时点

- 原型：`template< typename Lock, typename Clock, typename Duration > cv_status wait_until( Lock & lock, const chrono::time_point< Clock, Duration >& atime );`
- 原型：`template< typename Lock, typename Clock, typename Duration, typename Predicate > bool wait_until( Lock& lock, const chrono::time_point< Clock, Duration >& atime, Predicate p );`

```c++
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
std::mutex x;
std::condition_variable cond;
bool ready = false;
bool IsReady() { return ready; }
void Run( int no )
{
    std::unique_lock<std::mutex> locker(x);
    while( !ready )				// 若标志位非true，阻塞当前线程
        cond.wait( locker );	// 解锁并睡眠，被唤醒后重新加锁
    // 以上两行代码等价于cond.wait( locker, &IsReady );
    // 第二个参数为谓词，亦可使用函子实现
    std::cout << "thread" << no << "\n";
}

int main()
{
    std::thread threads[8];
    for( int i = 0; i < 8; i++ )
        threads[i] = std::thread( Run, i );
    std::cout << "8 threads ready...\n";
    {
        std::unique_lock<std::mutex> locker( x );			// 互斥加锁
        ready = true;										// 设置全局标志位true
        cond.notify_all();									// 唤醒所有线程
    }	// 离开作用域，自动解锁；可将次复合语句块实现为函数
    // 基于区间的循环结构，对属于threads数组的所有元素t，执行循环体
    for( auto & t : threads )
        t.join();
    return 0;
}
```

#### 原子型式

##### 使用方法

- 使用atomic模板定义原子对象
- 使用预定义标准原子型式：atomic_bool、atomic_char、atomic_int、atomic_uint、atomic_long、atomic_wchar_t等等
- 意义：轻量级，支持单变量上的原子操作

```c++
#include <atomic>
#include <iostream>
#include <thread>
int n = 0;
std::atomic< int > a(0);
void AddAtomically( int m ) { while( m-- ) a.fetch_add(1); }
void Add( int m ) { while( m-- ) ++n; };
int main()
{
    std::thread ts1[8], ts[8];
    for( auto & t : ts1 ) t = std::move( std::thread( AddAtomically, 1000000 ));
    for( auto & t : ts2 ) t = std::move( std::thread( Add, 1000000 ) );
    for( auto & t : ts1 ) t.join();
    for( auto & t : ts2 ) t.join();
    // 输出结果：a值固定，而n值多次运行结果可能不同
    std::cout << "a = " << a << std::endl;
    std::cout << "n = " << n << std::endl;
    return 0;
}
```

#### 期许与承诺

##### 线程返回值

- 为支持平台，thread类无属性字段保存线程函数的返回值

##### 解决方案

- 使用指针型式的函数参数
- 使用期许：std::future类模板
- 使用承诺：std::promies类模板

```c++
// 使用指针作为函数参数，获取线程计算结果
#include <iostream>
#include <vector>
#include <tuple>
#include <thread>
#include <mutex>
std::mutex x;
// 劳工线程类模板，处理T型数据对象
template< typename T > class Worker
{
    public:
    	explicit Worker(int no, T a = 0, T b = 0): _no(no), _a(a), _b(b) { }
    	void ThreadFunc( T * r ) { x.lock(); *r = _a + _b; x.unlock(); }
    private:
    	int _no;		// 线程编号，非线程ID
    	T _a, _b;		// 保存在线程中的待处理数据
    
};

int main()
{
    // 定义能够存储8个三元组的向量组v，元组首元素为指向劳工对象的指针
    // 次元素保存该劳工对象计算后的结果数据，尾元素为指向劳工线程对象的指针
    // 向量中的每个元素都表示一个描述线程运行的线程对象，
    // 该线程对象对应的执行具体任务的劳工对象，及该对象运算后的返回值
    std::vector< std::tuple<Worker<int>*, int, std::thread*> > v(8);
    
    // 构造三元组向量，三元编号顺次为0、1、2
    for( int i = 0; i < 8; i++ )
        v[i] = std::make_tuple( new Worker<int>( i, i + 1, i + 2 ), 0, nullptr );
    
    // 输出处理前结果；使用std::get<n>(v[i])获取向量的第i个元组的第n个元素
    // 三元编号顺次为0， 1， 2，因而1号元保存的将是劳工对象运算后的结果
    for( int i = 0; i < 8; i++ )
        std::cout << "No." << i << ":result = " << std::get<1>(v[i]) << std::endl;
    // 创建8个线程分别计算
    for( int i = 0; i < 8; i++ )
    {
        // 将劳工类成员函数绑定为线程函数，对应劳工对象绑定为执行对象
        // 将构造线程对象时传递的附加参数作为被绑定的线程函数的第一个参数
        // auto表示由编译器自动推断f的型式
        auto f = std::bind( &Worker<int>::ThreadFunc, std::get<0>( v[i] ), std::placeholders::_1 );
        
        // 动态构造线程对象，并保存到向量的第i个三元组中
        // 传递三元组的1号元地址，即将该地址作为线程函数的参数
        // 线程将在执行时将结果写入该地址
        // 此性质有绑定函数std::bind()使用占位符std::palceholders::_1指定
        // 线程对象为2号元，即三元组的最后一个元素
        std::get<2>( v[i] ) = new std::thread( f, &std::get<1>( v[i] ) );
    }
    
    for( int i = 0; i < 8; i++ )
    {
        // 等待线程结束
        std::get<2>( v[i] )->join();
        // 销毁劳工对象
        delete std::get<0>( v[i] ), std::get<0>( v[i] ) = nullptr;
        // 销毁线程对象
        delete std::get<2>( v[i] ), std::get<0>( v[i] ) = nullptr;
       
    }
    // 输出线程计算后的结果
    for( int i = 0; i < 8; i++ )
        std::cout << "No." << i << ":result = " << std::get<1>( v[1] ) << std::endl;
    return 0;
}
```

##### 期许

###### std::future类模板

- 目的：获取异步操作结果，延迟引发线程的异步操作异常

###### 使用方法

- 定义期许模板类的期许对象
- 使用`std::async()`函数的返回值初始化
- 调用期许对象的成员函数get()获取线程返回值

```c++
// 使用期许对象获取线程返回值
#include <iostream>
#include <exception>
#include <thread>
#include <future>

unsigned long int CalculateFactorial( short int n )
{
    unsigned long int r = 1;
    if( n > 20 )
        throw std::range_error( "The number is too big.");
    for( short int i = 2; i <= n; i++ )
        r *= i;
    return r;
}

int main()
{
    short int n = 20;
    // 启动异步线程，执行后台计算任务，并返回std::future对象
    std::future< unsigned long int > f = std::async( CalculateFactorial, n );
    try
    {
        // 获取线程返回值，若线程已结束，立即返回，否则等待该线程计算完毕
        // 若线程引发异常，则延迟到std::future::get()或std::future::wait()调用时引发
        unsigned long int r = f.get();
        std::cout << n << "! = " << r << std::endl;
    }
    catch( const std::range_error & e)
    {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
```

##### 承诺

###### std::promise类模板

- 目的：承诺对象允许期许对象获取线程对象创建的线程返回值

###### 使用方法

- 创建承诺`std::promise<T>`对象
- 获取该承诺对象的相关期许`std::future<T>`对象
- 创建线程对象，并传递承诺对象
- 线程函数内部通过承诺模板类的成员函数`set_value()`、`set_value_at_thread_exit()`、`set_exception()`或`set_exception_at_thread_exit()`设置值或异常
- 通过期许对象等待并获取异步操作结果

```c++
// 使用承诺对象设置线程返回值
#include <iostream>
#include <exception>
#include <thread>
#include <future>

unsigned long int CalculateFactorial( short int n )
{
    unsigned long int r = 1;
    if( n > 20 ) throw std::range_error( "The number is too big" );
    for ( short int i = 2; i <= n; i++ )
        r *= i;
    return r;
}

// CalculateFactorial()函数的包装函数原型
void DoCalculateFactorial( std::promise< unsigned long int > && promise, short int n );

int main()
{
    short int n = 6;
    std::promise< unsigned long int > p;		// 创建承诺对象
    std::future< unsigned long int > f = p.get_future();	// 获取相关期许对象
    // 启动线程，执行CalculateFactorial()函数的包装函数
    std::thread t( DoCalculateFactorial, std::move( p ), n);
    t.detach();
    try
    {
        unsigned long int r = f.get();
        std::cout << n << "! = " << r << std::endl;
    }
    catch ( std::range_error & e )
    {
        std::err << e.what() << std::endl;
    }
    return 0;
}

// CalculateFactorial()函数的包装函数实现
void DoCalculateFactorial( std::promise< unsigned long int > && promise, short int n )
{
    try
    {
        //设置线程返回值，供期许对象获取
        promise.set_value( CalculateFactorial( n ) );
    }
    catch ( ... )
    {
        // 捕获全部异常，并在期许获取线程返回值时重新引发
        promise.set_exception( std::current_exception() );
    }
}
```



### 编程实践

#### 第一题

考虑作业队列的容量限制，修改代码，实现标准的生产者-消费者模型。设作业队列最多容量amount个作业，有m个接收作业的线程，有n个处理作业的线程。

#### 第二题

实现Linux互斥、信号量和条件变量的封装类，并使用上述同步机制实现线程池类。提示：

1. 线程池功能与实现类似于进程池
2. 已作业型作为模板形式参数实现作业处理线程池类的作业和处理类
3. 线程函数为静态函数，要仿问类的非静态成员成员，可以定义类的静态对象或传递对象指针，在线程函数中通过该对象指针访问其成员。
4. 可以参考C++11架构

## 网络

### Internet网络协议

#### TCP/IP协议

- 数据链路层：将不同物理网络的不同电气特性进行统一封装，为上一层协议提供一致的接口，主要使用ARP和RARP协议，实现IP地址与机器物理地址（通常为MAC地址）之间相互转换
- 网络层：实现数据包的路由和转发，主要用IP、ICMP协议
  - IP协议：逐跳发送模式；根据数据包的目的地IP地址决定数据如何发送；如果数据包不能直接发送至目的地，IP协议负责寻找到一个合适的下一跳路由器，并将数据包交付给该路由器
  - ICMP协议：因特网控制报文协议，用于检测网络连接
- 传输层：为两台主机的应用提供端到端的通信，主要些使用TCP、UDP协议
- 应用层：应用程序逻辑实现，常用协议ping、telnet、DNS、HTTP、FTP、DHCP等

##### Internet主流协议族



##### 分层。多协议和通信体系

#### HTTP协议

##### 主要特点

- 无连接：无连接是指每次连接只处理一个请求；服务器处理完客户请求，并收到客户应答后，即断开连接，节省传输时间
- 无状态：无状态是指协议对于事务处理没有记忆能力；应答较快，但传输数据量较大

##### HTTP URL：定位网络资源

- `http://host[:port][abs_path]`

##### HTTP请求

- 由三部分组成：请求行、消息报文、请求正文
- 格式：`Method Request-URI HTTP-Version CRLF`
- Method：请求方法，GET、POST等
- HTTP-Version：请求的HTTP协议版本
- CRLF：回车换行

##### HTTP响应

- 由三部分组成：状态行、消息报头、响应正文
- 状态行格式：`HTTP-Version Status-Code Reason_phrase CRLF`
- `HTTP-Version`：服务器HTTP协议版本
- ``Status-Code`：服务器范湖的响应状态码
- `Reason-Phrase`：状态码的文本描述

##### HTTP状态码

- 状态代码有三位数字组成，首数字定义响应类别
  - 1xx：只是信息，表示请求已接收，急需处理；
  - 2xx：成功；
  - 3xx：重定向，要完成请求必须进行更进一步的操作；
  - 4xx：客户端错误，请求有语法错误或请求无法实现；
  - 5xx：服务器端错误，服务器未能实现合法的请求
- 常见状态代码
  - 200：请求成功；
  - 400：Bad Request，请求有语法错误，不能被服务器所理解
  - 401：Unauthorized，请求未经授权；
  - 403：Forbidden，服务器收到请求，但是拒绝提供服务；
  - 404：Not Found，请求资源不存在；
  - 500：Internal Server Error，服务器发生不可预期错误；
  - 503：Server Unavailable，服务器不能处理客户请求



### 套接字

#### 套接字的基本概念

##### 通信类型：控制套接字如何传输和如何处理数据，数据以包的形式传递

- 连接（connection）类型：确保所有包依次序传输，如果丢包，则请求重传
- 数据报（datagram）类型：不保证包的到达顺序，包可能丢失

##### 名空间：指定套接字地址格式

- 本地名空间：套接字地址为普通文件名
- Internert名空间：套接字地址由Internet地址和端口号（用于区分一台主机上的多个套接字）确定

##### 协议：确定数据如何传输

#### 套接字函数：“sys/socket.h”

##### socket()函数：创建套接字

- 原型：`int socket( int domain, int type, int protocol );`
- 参数：名空间、通信类型和协议
- 名空间：PF_LOCAL（本地）或PF_INET（Internet）
- 通信类型：SOCK_STREAM（连接类型）或SOCK_DGRAM（数据报类型）
- 协议：传递0，让系统自动选择协议（通常为最佳协议）
- 返回值：套接字描述符

##### close()函数：释放套接字

- 原型：`int close( int fd );`

##### connect()函数：创建两个套接字之间的连接

- 客户发起此系统调用，视图与服务器建立套接字连接
- 原型：`int connect( int sockfd, const struct sockaddr * addr, socklen_t addrlen ); `
- 参数：sockfd为套接字文件描述符；addr为指向套接字地址结构体的指针（服务器地址）；addrlen为服务器地址字符串的长度
- 返回值：0表示连接成功，-1表示连接失败

##### send()函数：发送数据

- 原型：`ssize_t send( int sockfd, const void * buf, size_t len, int flags );`
- 原型：`ssize_t sendto( int sockfd, const void * buf, size_t len, int flags, const struct sockaddr * dest_addr, socklen_t addrlen );`
- 原型：`ssize_t sendmsg( int sockfd, const struct msghdr * msg, int flags );`
- 只有在套接字处于连接状态时才可调用

##### bind()函数：绑定服务器套接字与其地址

- 原型：`int bind( int sockfd, const struct sockaddr* addr, socklen_t addren );`

##### listen()函数：侦听客户连接

- 原型：`int listen( int sockfd, int backlog );`
- 参数：backlog指定有多少个挂起连接可以挂起连接可以进入队列，超出该值的连接将被抛弃

##### accept()函数：接受连接，为该连接创建一个新的套接字

- 原型：`int accept( int sockfd, struct sockaddr * addr, socklen_t addrlen );`
- 参数：addr为指向套接字地址结构体（客户地址）的指针
- 返回值：创建一个新的套接字，以接受客户连接，返回值为新的套接字文件描述符
- 原先套接字文件描述符可以继续接受新连接

#### 服务器

```c++
// 服务端
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

// 持续读取消息，直到套接字关闭或接收到客户发送的“quit”消息
// 前者返回true，后者返回false，服务器随后将停止服务
bool Server( int client_socket )
{
    while ( true )
    {
        int length;
        charr * msg;
        // 从套接字中读取文本消息的长度，返回值为0,表示客户连接已关闭
        if( read( client_socket, &length, sizeof(length) ) == 0 )
            return true;
        msg = new char[length];
        read( client_socket, msg, length );
        std::cout << msg << std::endl;
        if( !strcmp( msg, "quit" )) { delete[] msg, msg = NULL; return false; }
        else
            delete[] msg, msg = NULL;
    }
}
int main( int argc, char * const argv[] )
{
    const char * const socket_name = argc[1];
    int socket_fd;
    struct sockaddr_un name;
    bool serving = true;
    // 创建套接字
    socket_fd = socket( PF_LOCAL, SOCK_STREAM, 0 );
    // 设定服务器性质
    name.sun_familly = AF_LOCAL;
    strcpy( name.sun_path, socket_name );
    // 绑定套接字
    bind( socket_fd, ( struct sockaddr *)&name, SUN_LEN( &name ) );
    // 侦听客户连接
    listen( socket_fd, 5 );
    // 重复接受连接，直到谋改革客户发出“quit”消息
    while( serving )
    {
        struct sockaddr_un client_name;
        socklen_t client_name_len;
        int client_socket_fd;
        // 接受客户连接请求
        client_socket_fd = accept( socket_fd, (struct sockaddr *)&client_name, &client_name_len );
        serving = Serve( client_socket_fd );	// 服务连接请求
        close( client_socket_fd );				// 关闭客户连接
    }
    close( socket_fd );
    unlink( socket_name );						// 删除客户连接
    return 0;
}
```

#### 本地套接字

```c++
// 客户端
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

void SendMsg( int socket_fd, const char * msg )
{
    int length = strlen( msg ) + 1;
    write( socket_fd, &length, sizeof( lengnth ) );
    write( socket_fd, msg, length );
}

int main( int argc, char * const argv[] )
{
    const char * const socket_name = argv[1];
    const char * const msg = argv[2];
    int socket_fd;
    struct sockaddr_un name;
    // 创建套接字
    socket_fd = socket( PF_LOCAL, SOCK_STREAM, 0);
    // 在套接字地址中村服务器名称
    name.sun_familly = AF_LOCAL;
    strcpy( name.sun_path, socket_name );
    // 连接
    connect( socket_fd, (struct sockaddr *)&name, SUN_LEN( &name ) );
    // 发送消息
    SendMsg( socket_fd, msg );
    close( socket_fd );
    return 0;
}
```

##### 程序测试运行

- 编译连接服务器端程序和客户端程序
- 进入服务器端程序目录，在终端输入：`./server /tmp/socket`；`./server`为服务器端程序名，`/tmp/socket`为服务器启动后的套接字文件名
- 进入客户端程序目录，在新终端输入：`./client /tmp/socket "Hello World!"`；`./client`为客户端程序名
- 停止服务器，在客户端舒输入命令：`./client /tmp/socket "quit"`

#### 网络套接字

```c++
// 网络套接字示例：客户端
#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
// 请求Web服务器的主页
void GetHomepage( int socket_fd )
{
    char buffer[8192];
    sprintf(buffer, "GET /\n");
    write( socket_fd, buffer, strlen( buffer ) );
    while( true )
    {
        ssize_t count = read( socket_fd, buffer, 8192 );
        if( count == 0 )
            return ;
        fwrite( buffer, sizeof( char ), count, stdout );
    }
}

int main( int targcc, charr * const argv[] )
{
    int socket_fd;
    struct sockaddr_in name;
    struct hostent* hostinfo;
    socket_fd = socket( PF_INET, SOCK_STREAM, 0 );
    name.sin_familly = AF_INET;
    hostinfo = gethostbyname( argv[1] );
    if( hostinfo == NULL )
        return 1;
    else
        name.sin_addr = *( (struct in_addr*)hostinfo->h_addr );
    name.sin_port = htons( 80 );
    if( connect( socket_fd, (struct sockaddr*)&name, sizeof(struct sockaddr_in )) == -1 )
    {
        perror("Failure to connect the server.");
        return 2;
    }
    GetHomepage( socket_fd );
    return 0;
}
```





### 编程实践：Web服务器开发

#### 远程系统管理Web服务器

- 允许本地货远程客户通过HTTP访问系统信息，例如显示时间、Linux发布版本、空闲磁盘空间、当前运行的进程等
- 使用模块架构针对Web请求生成动态HTML网页；各模块实现为共享目标库，允许动态装载模块，切可在服务器运行期间添加、删除和替换
- 在子进程或线程中服务Web请求，并设计进程池或线程池管理这些进程或线程
- 服务器不要求超级用户权限
- 不要求实现HTTP全部功能
- 使用面向对象架构