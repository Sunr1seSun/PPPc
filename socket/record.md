---
typora-copy-images-to: ./
---

参考：http://c.biancheng.net/view/2133.html

### 1 什么是socket？

在计算机通信领域，socket 被翻译为“套接字”，它是计算机之间进行通信的一种约定或一种方式。通过 socket 这种约定，一台计算机可以接收其他计算机的数据，也可以向其他计算机发送数据。

socket 的典型应用就是 Web 服务器和浏览器：

- 浏览器获取用户输入的 URL，向服务器发起请求。
- 服务器分析接收到的 URL，将对应的网页内容返回给浏览器。
- 浏览器再经过解析和渲染，就将文字、图片、视频等元素呈现给用户。

#### 1.1 UNIX/Linux中的socket

通过 socket() 函数来创建一个网络连接，或者说打开一个网络文件，socket() 的返回值就是文件描述符。有了文件描述符，我们就可以使用普通的文件操作函数来传输数据了，例如：

- 用 read() 读取从远程计算机传来的数据；
- 用 write() 向远程计算机写入数据。

#### 1.2 windows中的socket

Windows 会区分 socket 和文件，Windows 就把 socket 当做一个网络连接来对待，因此需要调用专门针对 socket 而设计的数据传输函数，针对普通文件的输入输出函数就无效了。

### 2 套接字有哪些类型？

这个世界上有很多种套接字socket，比如 DARPA Internet 地址（Internet 套接字）、本地节点的路径名（Unix套接字）、CCITT X.25地址（X.25 套接字）等。此处主要指internet套接字。

根据数据的传输方式，可以将 Internet 套接字分成两种类型：流格式和数据报格式。通过 socket() 函数创建连接时，必须告诉它使用哪种数据传输方式。

#### 2.1 流格式套接字（SOCK_STREAM）

TCP协议

流格式套接字（Stream Sockets）也叫“面向连接的套接字”，在代码中使用 SOCK_STREAM 表示。

SOCK_STREAM 是一种可靠的、双向的通信数据流，数据可以准确无误地到达另一台计算机，如果损坏或丢失，可以重新发送。  

SOCK_STREAM 有以下几个特征：

- 数据在传输过程中不会消失；
- 数据是按照顺序传输的；
- 数据的发送和接收不是同步的（有的教程也称“不存在数据边界”）。

实际应用场景：http协议（确保数据准确无误）

#### 2.2 数据报格式套接字（SOCK_DGRAM）

UDP协议

数据报格式套接字（Datagram Sockets）也叫“无连接的套接字”，在代码中使用SOCK_DGRAM 表示。

计算机只管传输数据，不作数据校验，如果数据在传输中损坏，或者没有到达另一台计算机，是没有办法补救的。也就是说，数据错了就错了，无法重传。

可以将 SOCK_DGRAM 比喻成高速移动的摩托车快递，它有以下特征：

- 强调快速传输而非传输顺序；
- 传输的数据可能丢失也可能损毁；
- 限制每次传输的数据大小；
- 数据的发送和接收是同步的（有的教程也称“存在数据边界”）。

实际应用场景：QQ视频聊天和语音聊天（丢失一部分数据可以正常解析）

### 3 OSI网络七层模型

<table>
	<tr>
	    <th>OSI参考模型</th>
	    <th>TCP/IP概念层</th>
	    <th>说明</th>  
	</tr >
	<tr >
	    <td>应用层 </td>
	    <td rowspan="3">应用层</td>
	    <td rowspan="3">各种服务及引用程序。常用协议HTTP、FTP、SMTP等</td>
	</tr>
	<tr>
	    <td>表示层 </td>
	</tr>
	<tr>
	    <td>会话层 </td>
	</tr>
	<tr>
	    <td>传输层 </td>
	    <td>传输层</td>
        <td>确认数据传输及进行纠错处理，常用协议TCP、UDP</td>
	</tr>
	<tr>
        <td>网络层 </td>
	    <td>网络层</td>
        <td>负责数据传输，路径及地址选择，常用协议IP、ARP（地址解析协议）</td>
	</tr>
	<tr>
	    <td nowrap="nowrap">数据链路层 </td>
	    <td rowspan="2">网络接口</td>
        <td rowspan="2">针对物理网络连接形式，如Ethernet、FDDI、ATM</td>
	</tr>
	<tr>
	    <td>物理层 </td>
	</tr>
</table>

### 4 TCP/IP协议族

TCP/IP协议参考模型把所有的TCP/IP系列协议归类到四个抽象层中

应用层：TFTP，HTTP，SNMP，FTP，SMTP，DNS，Telnet 等等

传输层：TCP，UDP

网络层：IP，ICMP，OSPF，EIGRP，IGMP

数据链路层：SLIP，CSLIP，PPP，MTU

![TCP/IP协议的层次图](.\photo\1-1Z126104435N0.gif)

### 5 socket程序

#### 5.1 linux下

server.cpp

```c++
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
int main()
{
    // 创建监听套接字
    int serv_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    // 将套接字和IP、端口绑定
    bind(serv_sock, serv_addr, sizeof(serv_addr));
    
    // 监听
    listen(serv_sock, 20);
    
    // 接收客户端请求,返回一个与客户端连接的套接字
    int clnt_sock = accept(serv_sock, clnt_addr, sizeof(clnt_addr));
    
    // 向客户端发送数据
    write(clnt_sock, data, sizeof(data));
    
    // 关闭套接字
}
```

client.cpp

```c++
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
int main()
{
    // 创建套接字
	int sock = socket(AF_INET, SOCK_STREAM, 0);
    
    // 发起请求
    connect(sock, serv_addr, sizeof(serv_addr));
    
    // 读取数据
    read(sock, buffer, sizeof(buffer)-1);
    
    //关闭套接字
}
```

#### 5.2 windows下

区别：

- Windows 下的 socket 程序依赖 Winsock.dll 或 ws2_32.dll，必须提前加载。
  - 隐式加载`#pragma comment(lib, "ws2_32.lib")`
  - 显式加载`HINSTANCE dll = LoadLibrary("ws2_32.lib")`
- linux下socket()函数返回int类型，windows下为SOCKET类型。
- linux下使用read()/write()读写，windows下使用recv()/send()函数。

### 6 socket编程函数

#### 6.1 socket()

```c++
int socket(int af, int type, int protocol); // linux
SOCKET socket(int af, int type, int protocol); // windows
```

1）af为（address family），常用的有AF_INET 和 AF_INET6。

2）type为数据传输方式，常用的有SOCK_STREAM（流格式套接字/面向连接的套接字） 和 SOCK_DGRAM（数据报套接字/无连接的套接字）。

3）protocol表示传输协议，常用的有 IPPROTO_TCP 和 IPPTOTO_UDP，分别表示 TCP 传输协议和 UDP 传输协议。

一般情况下，AF和type两个参数就可以创建套接字，操作系统会自动推演协议类型。

#### 6.2 bind()/connect()

服务器端：bind()将socket与特定ip地址端口绑定。

客户端：connect()建立连接。

```c++
// 服务器端用bind()将套接字与特定的 IP 地址和端口绑定起来，只有这样，流经该 IP 地址和端口的数据才能交给套接字处理。
int bind(int sock, struct sockaddr *addr, socklen_t addrlen);  //Linux
int bind(SOCKET sock, const struct sockaddr *addr, int addrlen);  //Windows

// 类似地，客户端也要用 connect() 函数建立连接。
int connect(int sock, struct sockaddr *serv_addr, socklen_t addrlen);  //Linux
int connect(SOCKET sock, const struct sockaddr *serv_addr, int addrlen);  //Windows
```

1）sock是socket文件描述符。

2）addr为sockaddr结构体变量的指针。

```c++
struct sockaddr_in{
    sa_family_t     sin_family;   //地址族（Address Family），也就是地址类型
    uint16_t        sin_port;     //16位的端口号
    struct in_addr  sin_addr;     //32位IP地址
    char            sin_zero[8];  //不使用，一般用0填充
};
struct in_addr{
    in_addr_t  s_addr;  //32位的IP地址
};
```

- 为什么使用 sockaddr_in 而不使用 sockaddr?
  - 可以认为，sockaddr 是一种通用的结构体，可以用来保存多种类型的IP地址和端口号，而 sockaddr_in 是专门用来保存 IPv4 地址的结构体。

<table>
	<tr>
	    <th>sockaddr_in结构体</th>
	    <th>sockaddr结构体</th>
	</tr >
	<tr >
	    <td>sin_family(2) </td>
	    <td>sin_family(2) </td>
	</tr>
	<tr>
	    <td>sin_port(2) </td>
        <td rowspan="3">sa_data(14) </td>
	</tr>
	<tr>
	    <td>sin_addr(4) </td>
	</tr>
	<tr>
	    <td>sin_zero(8) </td>
	</tr>
</table>

3）addrlen 为 addr 变量的大小，可由 sizeof() 计算得出。

#### 6.3 listen()/accept()

服务器端：绑定后，使用listen()函数让套接字进入监听状态，再用accept()响应客户端请求。

```c++
int listen(int sock, int backlog);  //Linux
int listen(SOCKET sock, int backlog);  //Windows
```

sock 为需要进入监听状态的套接字，backlog 为**请求队列**的最大长度。

当套接字正在处理客户端请求时，如果有新的请求进来，套接字是没法处理的，只能把它放进缓冲区，待当前请求处理完毕后，再从缓冲区中读取出来处理。如果不断有新的请求进来，它们就按照先后顺序在缓冲区中排队，直到缓冲区满。这个缓冲区，就称为**请求队列**。

```c++
int accept(int sock, struct sockaddr *addr, socklen_t *addrlen);  //Linux
SOCKET accept(SOCKET sock, struct sockaddr *addr, int *addrlen);  //Windows
```

sock 为服务器端套接字，addr 为 sockaddr_in 结构体变量，addrlen 为参数 addr 的长度，可由 sizeof() 求得。

accept() 返回一个新的套接字来和客户端通信，addr 保存了客户端的IP地址和端口号，而 sock 是服务器端的套接字。后面和客户端通信时，要使用这个新生成的套接字，而不是原来服务器端的套接字。

#### 6.4 send()/recv()和write()/read()

linux下：

````c++
ssize_t write(int fd, const void *buf, size_t nbytes);
ssize_t read(int fd, void *buf, size_t nbytes);
````

windows下：

```c++
int send(SOCKET sock, const char *buf, int len, int flags);
int recv(SOCKET sock, char *buf, int len, int flags);
```

### 7 socket缓冲区

write()/send() 并不立即向网络中传输数据，而是先将数据写入缓冲区中，再由TCP协议将数据从缓冲区发送到目标机器。一旦将数据写入到缓冲区，函数就可以成功返回，不管它们有没有到达目标机器，也不管它们何时被发送到网络，这些都是TCP协议负责的事情。

![TCP套接字的I/O缓冲区示意图](.\photo\1149355056-0.jpg)

#### 阻塞模式

发送数据时（write()/send()）：

1）检查缓冲区，如果可用长度小于要发送的数据，则阻塞写入函数，知道缓冲区中的数据被发送到目标机器，才唤醒。

2）当TCP协议正在向网络发送数据时，输出缓冲区被锁定，发送完毕解锁。、

3）写入数据大于缓冲区最大长度将分批写入。

4）直到所有数据被写入缓冲区，写入函数才返回。

读取数据时（read()/recv()）：

1）检查输入缓冲区，如果有数据则读取，否则阻塞。

2）如果要读取的数据小于缓冲区中的数据长度，则只能读取缓冲区中的部分数据，剩余数据不断积压。

3）直到读取完数据后，读取函数才返回。

### 8 TCP数据包及三次握手

![img](.\photo\1155315343-0.jpg)

建立连接：

![img](.\photo\1155312401-1.jpg)

1)开始：

客户端调用socket()创建套接字，未建立连接，套接字处于`CLOSED`状态；服务器端调用 listen() 函数后，套接字进入`LISTEN`状态，开始监听客户端请求。

2)客户端发起请求：

- 客户端调用connect()函数，TCP协议组建一个数据包，并设置 SYN 标志位，表示该数据包是用来建立同步连接的。同时生成一个随机数字 1000，填充“序号（Seq）”字段，表示该数据包的序号。
  - 完成这些工作，开始向服务器端发送数据包，客户端就进入了`SYN-SEND`状态。
- 服务器端接收到数据包，检测到SYN标识位，也会组建一个数据包，并设置 SYN 和 ACK 标志位，SYN 表示该数据包用来建立连接，ACK 用来确认收到了刚才客户端发送的数据包，是客户端数据包序号+1，1001。
  - 客户端将数据包发出，进入`ESTABLISED`状态，表示连接已经成功建立。
- 服务器端收到数据包，检测到已经设置了 ACK 标志位，就知道这是客户端发来的“确认包”。服务器会检测“确认号（Ack）”字段，看它的值是否为 2000+1，如果是就说明连接建立成功，服务器进入`ESTABLISED`状态。

### 9 传输过程

ack = seq + 传递的字节数 + 1

![img](.\photo\115A453O-1.jpg)

### 10 四步挥手

![img](.\photo\115T13926-0.jpg)