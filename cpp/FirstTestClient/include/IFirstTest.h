#ifndef IFIRSTTEST_H
#define IFIRSTTEST_H

#include <iostream>

namespace FirstTest
{
    class IFirstTest
    {
    public:
        /// @brief 有参有返回简单rpc
        /// @param id 
        /// @param name 
        /// @return 
        virtual std::string SimpleRpc(int id, std::string name) = 0;
        /// @brief 有参无返回简单rpc
        /// @param id 
        /// @param name 
        virtual void SimpleEmpty(int id, std::string name) = 0;
        virtual void ClientStream(bool *success, std::string *data) = 0;
        virtual void ServerStream(int id, std::string name) = 0;
        virtual void TwoWayStream() = 0;
    };
    
    
}

#endif // IFIRSTTEST_H