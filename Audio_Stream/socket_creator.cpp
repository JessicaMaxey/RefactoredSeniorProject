#include "socket_creator.h"

socket_creator::socket_creator() : connect_socket(0), data_socket(0)
{
    
}

socket_creator::~socket_creator()
{
}

bands_t socket_creator::GetData()
{
    bands_t dataz;
    
    if(nano_bands.size() == 0)
    {
        return {0.0};
    }
    
    access_lock.lock();
    
    dataz = nano_bands.front();
    nano_bands.pop_front();

    access_lock.unlock();
    
    return dataz;
}

void socket_creator::ReadSocket()
{
    uint32_t count = 0;
    int ret = 0;
    
    while(1)
    {
        data_socket = accept(connect_socket, NULL, NULL);
        
        if(data_socket == -1)
        {
            perror("failed to accept");
        }
        
        while(1)
        {
            count ++;
            bands_t bands;
            
            ret = read(data_socket, &bands, BUFFER_SIZE);
            
            if(ret == -1)
            {
                perror("failed to read");
                break;
            }
            
            access_lock.lock();
            nano_bands.push_back(bands);
            access_lock.unlock();
            
            if (count % 10 == 0) {                
                for (int i = 0; i < 13; i++)
                {
                    //if (i %  3 == 2)
                        //printf("\n");
                    //printf("%i: %f ", i, bands.band[i]);
                }
                //printf("\n");
            }
        }
    }
}

void socket_creator::InitSocket()
{
    sockaddr_in socket_info;
    int ret;
    
    connect_socket = socket(AF_INET, SOCK_STREAM, 6);
    
    if(connect_socket == -1)
    {
        perror("socket failed to connect");
        exit(-1);
    }
    
    inet_aton("127.0.0.1", (in_addr*)&socket_info.sin_addr.s_addr);
    socket_info.sin_port = htons(4321);
    socket_info.sin_family = AF_INET;
    
    ret = bind(connect_socket, (const struct sockaddr *)&socket_info, sizeof(struct sockaddr_in));
    
    if (ret == -1)
    {
        perror("failed to bind");
        exit(-1);
    }

    ret = listen(connect_socket, 20);
    
    if(ret == -1)
    {
        perror("failed to listen");
        exit(-1);
    }
    
    auto proxy = [&]()
    {
        this->ReadSocket();
    };
    
    connect_thread = std::make_unique<thread>(proxy);    
}