#include "../include/ClientBase.h"

namespace CentralControl
{
    ClientImpl::ClientImpl(int argc, char **argv)
    {
        std::string target_str = GetTargetStr(argc, argv);
        RequestClient.NewClient(target_str);
        ResponseClient.NewClient(target_str);
    }

    std::string ClientImpl::GetTargetStr(int argc, char **argv)
    {
        std::string target_str;
        std::string arg_str("--target");
        if(argc > 1)
        {
            std::string arg_val = argv[1];
            size_t start_pos = arg_val.find(arg_str);
            if(start_pos != std::string::npos)
            {
                start_pos += arg_str.size();
                if(arg_val[start_pos] == '=')
                {
                    target_str = arg_val.substr(start_pos + 1);
                }
                else
                {
                    std::cout << "The only correct argument syntax is --target=" << std::endl;
                    return URL;
                }
            }
            else
            {
                std::cout << "The only acceptable argument is --target=" << std::endl;
                return URL;
            }
        }
        else
        {
            return URL;
        }
        return target_str;
    }

} // namespace ClientBase
