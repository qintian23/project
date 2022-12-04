#ifndef CLIENTRESPONSE_H
#define CLIENTRESPONSE_H

#include "stdafx.h"

#include "../build/CentralControlResponse.grpc.pb.h"

namespace ClientBase
{
    class CentralControlResponseImpl
    {
    public:
        CentralControlResponseImpl(std::shared_ptr<grpc::Channel> channel) :
            stub_(CentralControlResponse::CentralControlResponse::NewStub(channel)){}

    private:
        std::unique_ptr<CentralControlResponse::CentralControlResponse::Stub> stub_;
    };
}

#endif // CLIENTRESPONSE_H
