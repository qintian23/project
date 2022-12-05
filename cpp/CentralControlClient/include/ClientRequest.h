#ifndef CLIENTREQUEST_H
#define CLIENTREQUEST_H

#include "stdafx.h"
#include "IClientBase.h"
#include "../../build/CentralControlRequest.grpc.pb.h"

namespace ClientBase
{
    class CentralControlRequestImpl : public IRequestBase
    {
    public:
        CentralControlRequestImpl(std::shared_ptr<grpc::Channel> channel) :
            stub_(CentralControlRequest::CentralControlRequest::NewStub(channel)){}

        void SendN640PicShow(byte &cmdParam);
        void SendHeartBeatData();

    private:
        std::unique_ptr<CentralControlRequest::CentralControlRequest::Stub> stub_;
        void ShowMessage(grpc::Status statu, std::string interface);
    };
}

#endif // CLIENTREQUEST_H
