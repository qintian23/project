#include "include/ClientBase.h"

int main(int argc, char **argv)
{
    CentralControl::ClientImpl centralcontrol(argc, argv);
    // 发送心跳
    centralcontrol.RequestClient.SendHeartBeatData();

    // 心跳状态
    bool type = centralcontrol.ResponseClient.HeartBeatResp();
    std::cout << type << std::endl;

    return 0;
}
