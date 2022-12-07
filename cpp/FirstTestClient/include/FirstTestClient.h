#ifndef FIRSTTESTCLIENT_H
#define FIRSTTESTCLIENT_H

#include <thread>
#include <iostream>
#include <memory>
#include <string>
#include <grpcpp/grpcpp.h>

#include "IFirstTest.h"
#include "../build/FirstTest.grpc.pb.h"

#define URL "localhost:7007"

namespace FirstTest
{
    class FirstTestClientImpl : IFirstTest
    {
    private:
        std::unique_ptr<SimpleGrpc::Server::FirstTest::Stub> stub_;

    public:
        FirstTestClientImpl();
        FirstTestClientImpl(std::shared_ptr<grpc::Channel> channel) :
            stub_(SimpleGrpc::Server::FirstTest::NewStub(channel)){}
        void NewClient(std::string url);

        std::string SimpleRpc(int id, std::string name);
        void SimpleEmpty(int id, std::string name);
        void ClientStream(bool *success, std::string *data);
        void ServerStream(int id, std::string name);
        void TwoWayStream();
        
    };
    

    
}

#endif // FIRSTTESTCLIENT_H