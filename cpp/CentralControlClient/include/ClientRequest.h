#ifndef CLIENTREQUEST_H
#define CLIENTREQUEST_H

#include "stdafx.h"
#include "IClientBase.h"
#include "../../build/CentralControlRequest.grpc.pb.h"

namespace CentralControl
{
    class CentralControlRequestImpl : public IRequestBase
    {
    public:
        /// @brief 默认构造函数
        CentralControlRequestImpl();

        /// @brief 通过channel初始化client
        /// @param channel 
        CentralControlRequestImpl(std::shared_ptr<grpc::Channel> channel) :
            stub_(CentralControlRequest::CentralControlRequest::NewStub(channel)){}

        // ~CentralControlRequestImpl();

        void NewClient(std::string url);

        void SendN640PicShow(byte &cmdParam);
        void SendHeartBeatData();

    private:
        std::unique_ptr<CentralControlRequest::CentralControlRequest::Stub> stub_;
        void ShowMessage(grpc::Status statu, std::string interface);
    };
}

#endif // CLIENTREQUEST_H
