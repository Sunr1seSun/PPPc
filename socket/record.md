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