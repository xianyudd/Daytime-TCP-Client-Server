# 定义编译器和编译选项
CC = gcc
CFLAGS = -I./include -Wall -Wextra

# 定义目录变量
BINDIR = ./bin
SRCDIR = ./src
CLIENTDIR = $(SRCDIR)/client
SERVERDIR = $(SRCDIR)/server

# 定义运行参数
SERVER_IP = 127.0.0.1

# 默认目标：构建所有程序
all: $(BINDIR)/time_client $(BINDIR)/time_server

# 编译客户端
$(BINDIR)/time_client: $(CLIENTDIR)/time_client.c
	$(CC) $(CFLAGS) $< -o $@

# 编译服务端
$(BINDIR)/time_server: $(SERVERDIR)/time_server.c
	$(CC) $(CFLAGS) $< -o $@

# 清理端口
.PHONY: clearport
clearport:
	@echo "Clearing port 13..."
	@-sudo fuser -k 13/tcp 2>/dev/null || true

# 运行服务器和客户端
.PHONY: run
run: all clearport
	@echo "Starting server in background..."
	@sudo $(BINDIR)/time_server & 
	@echo "Waiting for server to start..."
	@sleep 2
	@echo "Starting client..."
	@$(BINDIR)/time_client $(SERVER_IP)
	@echo "Cleaning up..."
	@-sudo pkill time_server
	@-sudo fuser -k 13/tcp 2>/dev/null || true

# 清理目标：删除所有编译产物
.PHONY: clean
clean:
	rm -f $(BINDIR)/*

# 重新构建目标：先清理，再构建
.PHONY: rebuild
rebuild: clean all
