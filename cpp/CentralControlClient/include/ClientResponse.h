#ifndef CLIENTRESPONSE_H
#define CLIENTRESPONSE_H

#include "stdafx.h"
#include "IClientBase.h"
#include "../../build/CentralControlResponse.grpc.pb.h"

namespace ClientBase
{
    class CentralControlResponseImpl : IResponseBase
    {
    public:
        CentralControlResponseImpl(std::shared_ptr<grpc::Channel> channel) :
            stub_(CentralControlResponse::CentralControlResponse::NewStub(channel)){}

        bool HeartBeatResp();
        void SignalSwitchResp(byte* cmdInput, byte* cmdOutput, bool* isSuccessed);

    private:
        std::unique_ptr<CentralControlResponse::CentralControlResponse::Stub> stub_;
        void ShowMessage(grpc::Status statu, std::string interface);
    };
}

#endif // CLIENTRESPONSE_H
