#include "../include/ClientBase.h"

namespace ClientBase
{

    void ClientImpl::Start(std::string ip, std::string port)
    {
        url=ip+":"+port;
        ResponseClient = CentralControlResponseImpl(
            grpc::CreateChannel(url, grpc::InsecureChannelCredentials()));
        RequestClient = CentralControlRequestImpl(
            grpc::CreateChannel(url, grpc::InsecureChannelCredentials()));
    }


} // namespace ClientBase
