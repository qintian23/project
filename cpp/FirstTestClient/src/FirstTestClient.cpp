#include "../include/FirstTestClient.h"

namespace FirstTest
{
    FirstTestClientImpl::FirstTestClientImpl()
    {
        std::shared_ptr<grpc::Channel> channel = grpc::CreateChannel(URL, grpc::InsecureChannelCredentials());
        stub_ = SimpleGrpc::Server::FirstTest::NewStub(channel);
    }

    void FirstTestClientImpl::NewClient(std::string url)
    {
        std::shared_ptr<grpc::Channel> channel = grpc::CreateChannel(url, grpc::InsecureChannelCredentials());
        std::unique_ptr<SimpleGrpc::Server::FirstTest::Stub> tmpStub = SimpleGrpc::Server::FirstTest::NewStub(channel);
        if(stub_ == tmpStub)
        {
            return;
        }
        stub_.swap(tmpStub);
        tmpStub.release();
    }

    std::string FirstTestClientImpl::SimpleRpc(int id, std::string name)
    {
        SimpleGrpc::Server::GrpcParams request;
        request.set_id(id);
        request.set_name(name);
        SimpleGrpc::Server::GrpcResults reply;
        grpc::ClientContext context;
        grpc::Status status = stub_->SimpleRpc(&context, request, &reply);
        if(status.ok())
        {
            return reply.data();
        }
        else
        {
            std::cout<< status.error_code() << ": " << status.error_message() << std::endl;
            return "RPC failed!";
        }
    }

    void FirstTestClientImpl::SimpleEmpty(int id, std::string name)
    {
        SimpleGrpc::Server::GrpcParams request;
        request.set_id(id);
        request.set_name(name);
        google::protobuf::Empty empty;
        grpc::ClientContext context;
        grpc::Status status = stub_->SimpleEmpty(&context, request, &empty);
    }

    void FirstTestClientImpl::ClientStream(bool *success, std::string *data)
    {
        SimpleGrpc::Server::GrpcResults response;
        grpc::ClientContext context;
        std::shared_ptr<grpc::ClientWriter<SimpleGrpc::Server::GrpcParams>> stream(stub_->ClientStream(&context, &response));
        auto thread_func=[stream]()
        {
            std::vector<SimpleGrpc::Server::GrpcParams> v_tmp;
            for(int i=0; i<50; i++)
            {
                SimpleGrpc::Server::GrpcParams tmp;
                tmp.set_id(i);
                tmp.set_name("123");
                v_tmp.push_back(tmp);
            }
            for(SimpleGrpc::Server::GrpcParams& d:v_tmp)
            {
                std::cout<< "write" <<std::endl;
                stream->Write(d);
            }
            stream->WritesDone();
        };
        std::thread writer(thread_func);
        writer.join();
        grpc::Status status = stream->Finish();
        if(!status.ok())
        {
            std::cout<< "get Data rpc failed!" <<std::endl;
        }
    }

    void FirstTestClientImpl::ServerStream(int id, std::string name)
    {
        SimpleGrpc::Server::GrpcParams request;
        request.set_id(id);
        request.set_name(name);
        grpc::ClientContext context;
        std::shared_ptr<grpc::ClientReader<SimpleGrpc::Server::GrpcResults>> stream(stub_->ServerStream(&context, request));
        SimpleGrpc::Server::GrpcResults recv_data;
        while (stream->Read(&recv_data))
        {
            std::cout<< "data " << recv_data.data() << " send sucess" << std::endl;
        }
        grpc::Status status = stream->Finish();
        if(!status.ok())
        {
            std::cout<< "get Data rpc failed!" <<std::endl;
        }
    }

    void FirstTestClientImpl::TwoWayStream()
    {
        grpc::ClientContext context;
        std::shared_ptr<grpc::ClientReaderWriter<SimpleGrpc::Server::GrpcParams, SimpleGrpc::Server::GrpcResults>> stream(stub_->TwoWayStream(&context));
        auto thread_func=[stream]()
        {
            std::vector<SimpleGrpc::Server::GrpcParams> v_tmp;
            for(int i=0; i<50; i++)
            {
                SimpleGrpc::Server::GrpcParams tmp;
                tmp.set_id(i);
                tmp.set_name("123");
                v_tmp.push_back(tmp);
            }
            for(SimpleGrpc::Server::GrpcParams& d:v_tmp)
            {
                std::cout<< "write" <<std::endl;
                stream->Write(d);
            }
            stream->WritesDone();
        };
        std::thread writer(thread_func);
        SimpleGrpc::Server::GrpcResults recv_data;
        while (stream->Read(&recv_data))
        {
            std::cout<< "data " << recv_data.data() << " send sucess" << std::endl;
        }
        writer.join();
        grpc::Status status = stream->Finish();
        if(!status.ok())
        {
            std::cout<< "get Data rpc failed!" <<std::endl;
        }
    }
}