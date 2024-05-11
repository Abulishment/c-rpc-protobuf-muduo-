#pragma once
#include <google/protobuf/service.h>
#include <memory>
#include <muduo/net/Callbacks.h>
#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/InetAddress.h>

//框架提供的 专门用于 发布rpc服务  的网络对象类
class RpcProvider
{
public:
    //框架提供给外部使用的  可以发布rpc方法的 函数接口。
    void NotifyService(google::protobuf::Service *service); 

    //启动rpc服务节点， 开始提供rpc远程网络调用服务
    void Run();

private:
    //组合EventLoop
    muduo::net::EventLoop m_eventLoop_;
    std::unique_ptr<muduo::net::TcpServer> m_tcpserverPtr;


    void OnConnection(const muduo::net::TcpConnectionPtr &);
};