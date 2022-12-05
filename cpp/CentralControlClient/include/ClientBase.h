#ifndef CLIENTBASE_H
#define CLIENTBASE_H

#include "ClientRequest.h"
#include "ClientResponse.h"

namespace  ClientBase
{

    class ClientImpl
    {
    public:

        void Start(std::string ip = "localhost", std::string port = "7007"); // 注：默认实参需要在形参列表的末尾
        void Start(std::string url);
        void Close();

    private:
        bool isConnect = false;
        std::string url;
        CentralControlResponseImpl ResponseClient;
        CentralControlRequestImpl RequestClient;
    };


}

#endif // CLIENTBASE_H
