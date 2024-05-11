#include "rpcprovider.h"
#include "mprpcapplication.h"
#include <cstdint>
#include <functional>
#include <muduo/net/Callbacks.h>
#include <muduo/net/InetAddress.h>
#include <muduo/net/TcpServer.h>
#include <string>

void RpcProvider::NotifyService(google::protobuf::Service *service) 
{

}

void RpcProvider::Run()
{
    std::string ip = MprpcApplication::GetInstance().GetConfig().Load("rpcserverip");
    std::uint16_t port = stoi(MprpcApplication::GetConfig().Load("rpcserverport"));
    muduo::net::InetAddress address(ip, port);


    //创建TcpServer对象
    muduo::net::TcpServer server(&m_eventLoop_, address, "RpcProvider");
    //绑定连接回调和消息读写回调方法  muduo==>分离了网络代码和业务代码。
    server.setConnectionCallback(std::bind(&RpcProvider::OnConnection, this, ));

    //设置muduo库的线程数量
    server.setThreadNum(4);
}

void RpcProvider::OnConnection(const muduo::net::TcpConnectionPtr &conn)
{
    
}