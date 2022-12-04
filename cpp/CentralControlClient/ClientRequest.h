#ifndef CLIENTREQUEST_H
#define CLIENTREQUEST_H

#include "stdafx.h"

#include "../build/CentralControlRequest.grpc.pb.h"

namespace ClientBase
{
    class CentralControlRequestImpl
    {
    public:
        CentralControlRequestImpl(std::shared_ptr<grpc::Channel> channel) :
            stub_(CentralControlRequest::CentralControlRequest::NewStub(channel)){}

    private:
        std::unique_ptr<CentralControlRequest::CentralControlRequest::Stub> stub_;
    };
}

#endif // CLIENTREQUEST_H
