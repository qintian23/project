#ifndef ICLIENTBASE_H
#define ICLIENTBASE_H

typedef unsigned char byte;

namespace  ClientBase
{
    class IRequestBase
    {
    public:
        virtual void SendN640PicShow(byte cmdParam) = 0;
    };

    class IResponseBase
    {

    };

}

#endif // ICLIENTBASE_H
