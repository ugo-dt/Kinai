#pragma once

#include "Kinai/Core/Core.hpp"

namespace Kinai
{

/**
 * Kinai networking
 * 
 * socket
 * 	create
 * 	delete
 * 	bind
 * 	connect
 * 	listen
 * 
 * messages
 * 	send
 * 	recv
 * 
 * server, client
 * poller
 */

class Network
{
public:
    #ifdef KN_PLATFORM_WINDOWS
        typedef SOCKET SocketHandle;
    #else
        typedef int SocketHandle;
    #endif

    enum
    {
        InvalidSocket = -1,
    };

    static void Init();
    static void Shutdown();

    class Client
    {
    public:
        static void Connect(const char *host, int port);
        static void Disconnect();

        static void Send(const u8* data, size_t size);
        static void Update();

        static bool IsConnected();
        static void SetName(const char *name);

    private:
        friend class Network;
        static const char *name;
        static SocketHandle socket;
        static struct pollfd* poll_fds;
        static size_t nfds;

        static const char *host;
        static int port;
        static bool in_connect_loop;
        static u8* packet_buffer;
        static size_t packet_buffer_size;
    };

    class Server
    {
    public:
        static void Start(const char *host, int port);
        static void Stop();

        static void Send(int client_id, const u8* data, size_t size);
        static void Broadcast(const u8* data, size_t size);
        static void Update();

        static bool IsRunning();
        static const char *GetHost();
        static int GetPort();

    private:
        friend class Network;
        static SocketHandle socket;
        static struct pollfd* poll_fds;
        static size_t nfds;
        static const char *host;
        static int port;
        static u8* packet_buffer;
        static size_t packet_buffer_size;
    };

    // static void SetTimeout(int seconds);
    // static void SetMaxClients(int max_clients);
    // static void SetPacketBufferSize(size_t size);

private:
    static void CloseSocket(SocketHandle socket);
    static void ValidateConnect(const char *host, int port);
    static const char *GetLastNetworkError();

private:
    static int _timeout_seconds;
    static int _max_clients;
    static size_t _packet_buffer_size;
};

} // Kinai

