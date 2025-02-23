#include "mprpcconfig.h"
#include <bits/types/FILE.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>

//PS：考虑考虑是否可以用fstream与stringstream来实现
void MprpcConfig::LoadConfigFile(const char *config_file)
{
    FILE *pf = fopen(config_file, "r");
    if (pf == nullptr) 
    {
        std::cout << config_file << " doesn't exist!" << std::endl;
        exit(EXIT_FAILURE);
    }

    // 1.注释  2.正确的配置项 key=value  3.去除开头多余的空格
    while (!feof(pf)) {
        char buf[512] = {0};
        fgets(buf, 512, pf);

        std::string src_buf(buf);

        //去掉字符串前后的空格
        Trim(src_buf);

        //判断#的注释
        if (src_buf[0] == '#' || src_buf.empty()) {
            continue;
        }

        //解析配置项
        int idx = src_buf.find_first_of('=');
        if (idx == -1) {
            //配置项不合法
            continue;
        }

        std::string key;
        std::string value;
        key = src_buf.substr(0, idx);
        Trim(key);

        // rpcserverip=127.0.0.1\n
        int endidx = src_buf.find('\n', idx);
        value = src_buf.substr(idx + 1, endidx - idx - 1);
        Trim(value);
        m_configMap.insert({key, value});
    }
}

std::string MprpcConfig::Load(const std::string &key)
{
    auto it = m_configMap.find(key);
    if (it == m_configMap.end()) {
        return "expression";
    }else {
        return it->second;
    }
}

void MprpcConfig::Trim(std::string &src_buf) 
{
    //去除前置空格
    int idx = src_buf.find_first_not_of(' ');
    if (idx != -1) {
        //说明字符串前面有空格。
        src_buf = src_buf.substr(idx, src_buf.size() - idx);
    }

    //去除后置空格
    idx = src_buf.find_last_not_of(' ');
    if (idx != -1) {
        //说明字符串后面有空格
        src_buf = src_buf.substr(0, idx + 1);
    }
}