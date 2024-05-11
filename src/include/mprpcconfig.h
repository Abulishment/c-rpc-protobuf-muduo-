#pragma once

//用于  框架读取配置文件  的类
//rpcserver_ip = , rpcserver_port = , zookeeper_ip = , zookeeper_port = .
#include <string>
#include <unordered_map>
class MprpcConfig
{
public:
    //负责解析并加载配置文件。
    void LoadConfigFile(const char *config_file);
    //查询配置项信息。
    std::string Load(const std::string &key);

private:
    //保存配置信息，使其无需每次加载配置时，需要从磁盘文件上进行读取。
    std::unordered_map<std::string, std::string> m_configMap;

    //去掉字符串前后的空格
    void Trim(std::string &src_buf);
};