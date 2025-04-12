# ChatServer

基于 Socket 的多用户聊天服务器，使用 C++ 开发，支持 Windows 平台。

## 功能特点

- 支持多客户端同时连接
- 配置文件管理服务器设置
- 用户管理系统
- 实时消息广播
- 一个进程一个房间
- 基于 Winsock2 的网络通信

## 系统架构

项目采用面向对象设计，主要包含以下几个模块：

- **Net**: 网络通信模块，处理 Socket 连接和消息传输
- **IO**: 配置文件读写模块，管理服务器配置
- **Entity**: 用户实体模块，管理用户信息
- **Util**: 工具模块，提供日志等辅助功能

### 类图

项目包含以下主要类：

- `Server`: 服务器核心类，处理客户端连接和消息转发
- `ConfigManager`: 配置管理器，负责配置文件的读写
- `ConfigFile`: 配置文件类，存储配置信息
- `User`: 用户类，存储用户信息

## 安装与使用

### 环境要求

- Windows 操作系统
- Visual Studio 2019 或更高版本
- C++11 或更高版本

### 编译步骤

1. 使用 Visual Studio 打开 `ChatServer.sln` 解决方案文件
2. 选择 Release 配置
3. 构建解决方案

### 运行服务器

1. 运行编译生成的 `ChatServer.exe`
2. 服务器将自动加载 `ServerConfig.ini` 配置文件
3. 如果配置文件不存在，将自动创建默认配置

### 配置文件

服务器配置文件 `ServerConfig.ini` 包含以下参数：

```ini
my_server_name = server  # 服务器名称
passwd = 000            # 服务器密码
ip = 0.0.0.0            # 监听 IP 地址
port = 56789            # 监听端口
