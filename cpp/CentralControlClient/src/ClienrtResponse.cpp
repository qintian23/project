#include "../include/ClientResponse.h"

namespace ClientBase
{

    CentralControlResponseImpl::CentralControlResponseImpl()
    {
        std::shared_ptr<grpc::Channel> channel = grpc::CreateChannel(URL, grpc::InsecureChannelCredentials());
        stub_ = CentralControlResponse::CentralControlResponse::NewStub(channel);
    }

    void CentralControlResponseImpl::NewClient(std::string url)
    {
        std::shared_ptr<grpc::Channel> channel = grpc::CreateChannel(url, grpc::InsecureChannelCredentials());
        std::unique_ptr<CentralControlResponse::CentralControlResponse::Stub> tmpStub = CentralControlResponse::CentralControlResponse::NewStub(channel);
        if(stub_ == tmpStub)
        {
            // tmpStub.release();
            return;
        }
        stub_.swap(tmpStub); 
        tmpStub.release();
    }

    bool CentralControlResponseImpl::HeartBeatResp()
    {
        grpc::ClientContext context;
        CentralControlResponse::Response1 reply;
        google::protobuf::Empty empty;
        grpc::Status statu = stub_->HeartBeatResp(&context, empty, &reply);
        ShowMessage(statu, "HeartBeatResp");
    }

    void CentralControlResponseImpl::SignalSwitchResp(byte* cmdInput, byte* cmdOutput, bool* isSuccessed)
    {
        grpc::ClientContext context;
        google::protobuf::Empty empty;
        CentralControlResponse::Response4* reply;
        grpc::Status statu = stub_->SignalSwitchResp(&context, empty, reply);
        if(statu.ok())
        {
            *cmdInput = strtoul(reply->t1().c_str(), NULL, 16);
            *cmdOutput = strtoul(reply->t2().c_str(), NULL, 16);
            *isSuccessed = reply->b1();
        }
        ShowMessage(statu,"SignalSwitchResp");
    }

    void CentralControlResponseImpl::ShowMessage(grpc::Status statu, std::string interface)
    {
        if(statu.ok())
        {
            std::cout<< interface << " is successed!" <<std::endl;
        }
        else
        {
            std::cout<< interface << " is failed! "
                     << statu.error_code() << ": " 
                     << statu.error_message()
                     << ". "  <<std::endl;
        }
    }
}