#ifndef CLIENTBASE_H
#define CLIENTBASE_H

#include "ClientRequest.h"
#include "ClientResponse.h"

namespace  ClientBase
{

    class ClientImpl
    {
    public:
        ClientImpl(int argc, char **argv);

        CentralControlResponseImpl ResponseClient;
        CentralControlRequestImpl RequestClient;
        
    private:
        bool isConnect = false;
        std::string GetTargetStr(int argc, char **argv);
    };


}

#endif // CLIENTBASE_H
