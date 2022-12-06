#include "include/ClientBase.h"

int main(int argc, char **argv)
{
    CentralControl::ClientImpl centralcontrol(argc, argv);
    // 发送心跳
    centralcontrol.RequestClient.SendHeartBeatData();

    byte cmdParam = 0x11;
    centralcontrol.RequestClient.SendN640PicShow(cmdParam);

    // 心跳状态
    bool type = centralcontrol.ResponseClient.HeartBeatResp();
    std::cout << type << std::endl;

    byte input, output;
    bool falg;
    centralcontrol.ResponseClient.SignalSwitchResp(&input, &output, &falg);
    std::cout << input << output << falg  << std::endl;

    return 0;
}
