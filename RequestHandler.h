#pragma once
#include "ThreadPool.h"

class RequestHandler 
{
public:
    RequestHandler();
    ~RequestHandler();
    void pushRequest(FuncType f, std::shared_ptr<int[]>, long left, long right);
private:
    ThreadPool m_tpool;
};