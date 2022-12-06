#include "../include/ClientRequest.h"

namespace ClientBase
{

    CentralControlRequestImpl::CentralControlRequestImpl()
    {
        std::shared_ptr<grpc::Channel> channel = grpc::CreateChannel(URL, grpc::InsecureChannelCredentials());
        stub_ = CentralControlRequest::CentralControlRequest::NewStub(channel);
    }

    void CentralControlRequestImpl::NewClient(std::string url)
    {
        std::shared_ptr<grpc::Channel> channel = grpc::CreateChannel(url, grpc::InsecureChannelCredentials());
        std::unique_ptr<CentralControlRequest::CentralControlRequest::Stub> tmpStub = CentralControlRequest::CentralControlRequest::NewStub(channel);
        if(stub_ == tmpStub)
        {
            // tmpStub.release();
            return;
        }
        stub_.swap(tmpStub); 
        tmpStub.release(); // 释放对CentralControlRequest的stub的控制权，并将其指向的对象置为空
    }

    void CentralControlRequestImpl::SendN640PicShow(byte &cmdParam) 
    {
        CentralControlRequest::Request1 request = CentralControlRequest::Request1();
        request.set_s1(cmdParam);
        google::protobuf::Empty reply;
        grpc::ClientContext context;
        grpc::Status statu = stub_->SendN640PicShow(&context, request, &reply);
        ShowMessage(statu, "SendN640PicShow");
    }

    void CentralControlRequestImpl::SendHeartBeatData()
    {
        google::protobuf::Empty request;
        google::protobuf::Empty reply;
        grpc::ClientContext context;
        grpc::Status statu = stub_->SendHeartBeatData(&context, request, &reply);
        ShowMessage(statu, "SendHeartBeatData");
    }

    void CentralControlRequestImpl::ShowMessage(grpc::Status statu, std::string interface)
    {
        if(statu.ok())
        {
            std::cout<< interface << " is successed!" <<std::endl;
        }
        else
        {
            std::cout<< interface << " is failed! " << statu.error_code() << ": " << statu.error_message()
            << ". "  <<std::endl;
        }
    }

} // ClientBase
