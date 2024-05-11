#include <iostream>
#include <string>
#include "../user.pb.h"
#include "mprpcapplication.h"
#include "rpcprovider.h"
/*
    UserService原本为一个本地服务，提供两个方法，Login和GetFriendLists。
*/
class UserService : public fixbug::UserServiceRpc  //该类被rpc服务发布端使用(rpc服务提供者。)
{
public: 
    bool Login(std::string name, std::string pwd)
    {
        //简单表示业务
        std::cout << "doing local service: Login" << std::endl;
        std::cout << "name:" << name << " pwd:" << pwd << std::endl;
        
    }


    /*重写基类UserServiceRpc的虚函数，下面的方法都是框架直接调用的方法。
    1.caller ==> Login(LoginRequest) => muduo => callee.
    2.callee ==> Login(LoginRequest) => 交到下面这个重写的Login方法。
    */
    void Login(::google::protobuf::RpcController* controller,
                       const ::fixbug::LoginRequest* request,
                       ::fixbug::LoginResponse* response,
                       ::google::protobuf::Closure* done)
    {
        //框架给业务上报了请求参数LoginRequest，应用获取其相应的数据执行本地业务。
        //(解包)
        std::string name = request->name();
        std::string pwd = request->pwd();

        //执行本地业务
        bool login_request = Login(name, pwd);

        //把业务处理完成后的响应写入(包括错误码、错误消息、以及返回值)
        fixbug::ResultCode *code = response->mutable_result();
        code->set_errcode(0);
        code->set_errmsg("");
        response->set_success(login_request);

        //执行回调??????????????
        done->Run();
    }

};

int main(int argc, char **argv)
{
    //调用框架的初始化操作。(如：指明两端等, 配置文件加载)
    MprpcApplication::Init(argc, argv);

    
    //provider是一个rpc网络服务发布者。把UserService对象发布到rpc节点上。
    RpcProvider provider;
    provider.NotifyService(new UserService());

    //启动rpc服务发布节点  run以后，进程进入阻塞状态，等待远程的rpc调用请求。
    provider.Run();


    UserService us;
    us.Login("xxx", "xxx");

    return 0;
}