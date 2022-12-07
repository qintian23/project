#include "include/FirstTestClient.h"

int main(int argc, char** argv)
{
    std::cout<< "Hello world" << std::endl;

    FirstTest::FirstTestClientImpl firsttest;
    
    int id = 0;
    std::string name = "hjk", data;
    bool success;

    std::string reply = firsttest.SimpleRpc(id, name);
    std::cout<< reply << std::endl;
    firsttest.SimpleEmpty(id, name);

    // firsttest.ClientStream(&success, &data);

    // firsttest.ServerStream(id, name);

    firsttest.TwoWayStream();

    return 0;
}