#include "Kinai/Network/Network.hpp"

namespace Kinai
{

constexpr int DEFAULT_MAX_CLIENTS = 8;
constexpr int DEFAULT_TIMEOUT_SECONDS = 5;
constexpr int DEFAULT_PACKET_BUFFER_SIZE = 1024;

int Network::_timeout_seconds = DEFAULT_TIMEOUT_SECONDS;
int Network::_max_clients = DEFAULT_MAX_CLIENTS;
size_t Network::_packet_buffer_size = DEFAULT_PACKET_BUFFER_SIZE;

const char *Network::Client::name = nullptr;
Network::SocketHandle Network::Client::socket = Network::InvalidSocket;
struct pollfd* Network::Client::poll_fds = nullptr;
size_t Network::Client::nfds = 0;
const char *Network::Client::host = nullptr;
int Network::Client::port = 0;
bool Network::Client::in_connect_loop = false;
u8* Network::Client::packet_buffer = nullptr;
size_t Network::Client::packet_buffer_size = 0;

Network::SocketHandle Network::Server::socket = Network::InvalidSocket;
struct pollfd* Network::Server::poll_fds = nullptr;
size_t Network::Server::nfds = 0;
const char *Network::Server::host = nullptr;
int Network::Server::port = 0;
u8* Network::Server::packet_buffer = nullptr;
size_t Network::Server::packet_buffer_size = 0;

void Network::CloseSocket(SocketHandle socket)
{
#ifdef KN_PLATFORM_WINDOWS
    closesocket(socket);
#else
    close(socket);
#endif
}

const char *Network::GetLastNetworkError(void)
{
#ifdef _WIN32
	static char last_error[256] = {0};

	DWORD errorMessageID = GetLastError();
	if (errorMessageID == 0)
		return "No error";

	LPSTR messageBuffer = NULL;
	// Ask Win32 to give us the string version of that message ID.
	// The parameters we pass in, tell Win32 to create the buffer that holds the message for us (because we don't yet know how long the message string will be).
	size_t size = FormatMessageA(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		errorMessageID,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPSTR)&messageBuffer, 0, NULL);

	strncpy(last_error, messageBuffer, size);
	last_error[size - 1] = '\0'; // remove newline character
	LocalFree(messageBuffer);
	return last_error;
#else
	return strerror(errno);
#endif
}

#ifdef KINAI_DEBUG
void Network::ValidateConnect(const char *host, int port)
{
    int res = inet_pton(AF_INET, host, &(struct in_addr){0});
	Log::Validate(res > 0, "Invalid host: {}: {}", host, GetLastNetworkError());
    Log::Validate(port > 0 && port <= 65535, "Invalid port: {}: {}", port, GetLastNetworkError());
}
#endif

void Network::Init()
{
    _timeout_seconds = DEFAULT_TIMEOUT_SECONDS;
    _max_clients = DEFAULT_MAX_CLIENTS;
    _packet_buffer_size = DEFAULT_PACKET_BUFFER_SIZE;

    #ifdef KN_PLATFORM_WINDOWS
        int status;
        WSADATA wsaData;
        status = WSAStartup(WINSOCK_VERSION, &wsaData);
        if (status != 0)
            _SNET_PANIC_MSG(WSASTARTUP_FAILED, _snet_last_error());
    #endif

    Client::packet_buffer = new u8[_packet_buffer_size];
    Server::packet_buffer = new u8[_packet_buffer_size];
}

void Network::Shutdown()
{
    if (Client::IsConnected())
        Client::Disconnect();
    if (Server::IsRunning())
        Server::Stop();
    delete[] Client::packet_buffer;
    delete[] Server::packet_buffer;

    #ifdef KN_PLATFORM_WINDOWS
        WSACleanup();
    #endif
}

void Network::Client::Connect(const char *host, int port)
{
    Log::Validate(!IsConnected(), "Client is already connected");
    if (Client::in_connect_loop)
        return;
    KN_ASSERT(Client::socket == Network::InvalidSocket);
    KN_ASSERT(!Client::poll_fds);
    KN_ASSERT(host != nullptr);
    KN_ASSERT(port > 0 && port <= 65535);

    if (std::strcmp(host, "localhost") == 0)
        host = "127.0.0.1";

    #ifdef KINAI_DEBUG
        Network::ValidateConnect(host, port);
    #endif

    Client::host = host;
    Client::port = port;

    #if KINAI_HAS_THREADS
    #endif
}

} // Kinai
