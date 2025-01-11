# Daytime TCP Client/Server

这是一个简单的基于 TCP 的时间同步客户端/服务器程序，使用标准时间服务端口(13)。

## 项目结构

```plaintext
.
├── Makefile              # 项目构建文件
├── README.md             # 项目说明文档
├── bin/                  # 编译后的可执行文件目录
│   ├── time_client       # 客户端可执行文件
│   └── time_server       # 服务端可执行文件
├── include/              # 头文件目录
│   └── unp.h             # Unix网络编程头文件
└── src/                  # 源代码目录
    ├── client/           # 客户端源码
    │   └── time_client.c
    └── server/           # 服务端源码
        └── time_server.c
```

## 功能说明

### 服务器端 (time_server)
- 监听端口 13
- 当客户端连接时，发送当前系统时间
- 需要 root 权限运行（因为使用了特权端口）

### 客户端 (time_client)
- 连接到指定的服务器
- 接收并显示服务器发送的时间信息
- 使用方法: `./time_client <server_ip>`

## 编译和运行

### 编译
```bash
make all      # 编译所有程序
```

### 运行

**方式一：单独运行服务器和客户端**

```bash
# 终端 1：启动服务器（需要 root 权限）
sudo make server

# 终端 2：运行客户端
make client
```

**方式二：使用单个命令运行（推荐）**

```bash
sudo make run   # 自动启动服务器和客户端
```

### 清理
```bash
make clean    # 清理编译产物
make rebuild  # 清理并重新编译
```

### 其他命令
```bash
make clearport  # 清理被占用的 13 端口
```

## 注意事项

1. 服务器使用端口 13（标准时间服务端口），需要 root 权限
2. 运行前确保端口 13 未被其他程序占用
3. 客户端需要指定服务器的 IP 地址
4. 默认使用 127.0.0.1 作为服务器地址

## 开发环境

- 系统环境：Linux/Unix
- 编译器：GCC
- 依赖库：标准 C 库

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details