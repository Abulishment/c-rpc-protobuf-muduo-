#pragma once

//mprpc框架的基础类，负责框架的一些初始化操作。
#include "mprpcconfig.h"
class MprpcApplication
{
public:
    static void Init(int argc, char **argv);
    static MprpcApplication& GetInstance();
    static MprpcConfig& GetConfig();
private:    
    MprpcApplication() {}
    MprpcApplication(const MprpcApplication&) = delete;
    MprpcApplication& operator=(const MprpcApplication&) = delete;
    MprpcApplication(MprpcApplication&&) = delete;
    MprpcApplication& operator=(MprpcApplication&&) = delete;
    static MprpcConfig m_config;
};