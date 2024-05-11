#include "test.pb.h"
#include <google/protobuf/generated_message_table_driven.h>
#include <iostream>
#include <ostream>
#include <string>

int main()
{
    fixbug::LoginResponse rsp;
    fixbug::ResultCode *rc = rsp.mutable_result();
    rc->set_errcode(1);
    rc->set_errmsg("登录失败。");


    fixbug::GetFriendListsResponse gflrsp;
    fixbug::User *pusr = gflrsp.add_friend_list();
    pusr->set_name("zhang san");
    pusr->set_age(20);
    pusr->set_sex(fixbug::User::MAN);

    fixbug::User *pusr1 = gflrsp.add_friend_list();
    pusr1->set_name("zhang san");
    pusr1->set_age(20);
    pusr1->set_sex(fixbug::User::MAN);

    std::cout << gflrsp.friend_list_size() << std::endl;

     

    return 0;
}


int main1()
{

    //LoginRequest   Client ==>  Server.

    //创建登录请求对象。
    fixbug::LoginRequest req;
    req.set_name("zhang san");
    req.set_pwd("123456");

    //将对象序列化为string。 object->string.（可通过网络发送的数据）
    std::string send_str;
    if (req.SerializeToString(&send_str)) {
        std::cout << send_str << std::endl;
    }

    //从send_str反序列化为一个请求对象。
    fixbug::LoginRequest reqB;
    if (reqB.ParseFromString(send_str)) {
        std::cout << reqB.name() << std::endl;
        std::cout << reqB.pwd() << std::endl;
    }

    return 0;
}