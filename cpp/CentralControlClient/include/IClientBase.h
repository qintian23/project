#ifndef ICLIENTBASE_H
#define ICLIENTBASE_H

typedef unsigned char byte;

namespace  CentralControl
{
    class IRequestBase
    {
    public:
        /// <summary>
        /// 1. 发送数据-N640图片显示
        /// </summary>
        virtual void SendN640PicShow(byte &cmdParam) = 0;

        /// <summary>
        /// 6. 发送心跳包
        /// </summary>
        virtual void SendHeartBeatData() = 0;
    };

    class IResponseBase
    {
    public:
        /// <summary>
        /// 1. 心跳-中控响应
        /// </summary>
        virtual bool HeartBeatResp() = 0;

        /// <summary>
        /// 13. 信号源切换-中控响应
        /// </summary>
        virtual void SignalSwitchResp(byte* cmdInput, byte* cmdOutput, bool* isSuccessed) = 0;
    };

}

#endif // ICLIENTBASE_H
