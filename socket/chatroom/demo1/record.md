参考：

https://github.com/RsrnlWysxr/UDP-ChatRoom

1
服务器端实现转发功能：

向除了发送者以外的用户广播消息。

```c++
map<string, sockaddr_in> userTable;

for (auto x : userTable) {
	if (x.second.sin_port == cli.sin_port)
		continue;
	SendMessage(recv_message, x.second);
}
```

2
使用了setsockopt()函数，重用一个端口进行收发。