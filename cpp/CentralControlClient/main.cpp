#include "include/ClientBase.h"

int main(int argc, char **argv)
{
    CentralControl::ClientImpl centralcontrol(argc, argv);
    // 发送心跳
    centralcontrol.RequestClient.SendHeartBeatData();

    byte cmdParam = 0x11;
    centralcontrol.RequestClient.SendN640PicShow(cmdParam);

    byte cmdParam1;
    bool flag, type1;
    flag = true;
    
    centralcontrol.RequestClient.SendScreenBrightOut(flag);

    // 心跳状态
    bool type = centralcontrol.ResponseClient.HeartBeatResp();
    std::cout << type << std::endl;

    // byte input, output;
    // bool falg;
    // centralcontrol.ResponseClient.SignalSwitchResp(&input, &output, &falg);
    // std::cout << input << output << falg  << std::endl;
    // 亮灭屏
    centralcontrol.ResponseClient.ScreenBrightOutResp(&cmdParam1, &type1);
    std::cout << cmdParam1 <<  type1 << std::endl;

    return 0;
}
