#ifndef SOCKET_CREATOR_H
#define SOCKET_CREATOR_H


#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <deque>
using std::deque;

#include <mutex>
using std::mutex;

#include <memory>
#include <thread>
using std::thread;

#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/un.h>

#define BUFFER_SIZE sizeof(bands_t)

struct bands_t
{
    float band [13];
} ;


class socket_creator
{
public:
    socket_creator();
    ~socket_creator();
    void InitSocket();
    void ReadSocket();
    bands_t GetData();
    
private: 
    int connect_socket;
    int data_socket;
    std::unique_ptr<thread> connect_thread;
    deque<bands_t> nano_bands;
    mutex access_lock;
    
};

#endif // SOCKET_CREATOR_H
