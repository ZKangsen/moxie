#include <iostream>

#include <moxie/base/EventLoop.h>
#include <string.h>
#include <moxie/base/Log.h>
#include <moxie/base/Socket.h>
#include <moxie/base/NetAddress.h>
#include <moxie/base/PollerEvent.h>
#include <moxie/base/ListenHandler.h>
#include <moxie/base/ClientHandler.h>

using namespace moxie;

class EchoClientHandler : public ClientHandler {
public:
    EchoClientHandler(const std::shared_ptr<PollerEvent>& client,  const std::shared_ptr<moxie::NetAddress>& cad)
        : event_(client),
        peer_(cad) {
    }

    virtual void AfetrRead(const std::shared_ptr<PollerEvent>& event, EventLoop *loop) {
        if (readBuf_.readableBytes() > 0) {
            writeBuf_.append(readBuf_.peek(), readBuf_.readableBytes());
            readBuf_.retrieveAll();
            event->EnableWrite();
            loop->Modity(event);
        }
    }

    virtual void AfetrWrite(const std::shared_ptr<PollerEvent>& event, EventLoop *loop) {
        if (writeBuf_.readableBytes() > 0) {
            return;
        }
        event->DisableWrite();
        loop->Modity(event);
    }
private:
    std::shared_ptr<PollerEvent> event_;
    std::shared_ptr<moxie::NetAddress> peer_;
};

class Echo : public ListenHadler {
public:
    virtual void AfterAcceptSuccess(const std::shared_ptr<PollerEvent>& client, EventLoop *loop, const std::shared_ptr<moxie::NetAddress>& cad) {
        if (!loop->Register(client, std::make_shared<EchoClientHandler>(client, cad))) {
            ::close(client->GetFd());
            return;
        }
    }
};

int main() {
    EventLoop *loop = new EventLoop();
    int server = socket(AF_INET, SOCK_STREAM, 0);
    if (server < 0) {
        LOGGER_ERROR("socket error : " << strerror(errno));
        return -1;
    }

    Socket::SetExecClose(server);
    Socket::SetNoBlocking(server);

    NetAddress addr(AF_INET, 8899, "127.0.0.1");

    if (!(Socket::Bind(server, addr)
          && Socket::Listen(server, 128))) {
        return -1;
    }

    // 注册监听套接字的处理类
    std::shared_ptr<PollerEvent> event = std::make_shared<PollerEvent>(server, moxie::kReadEvent);
    if (!loop->Register(event, std::make_shared<Echo>())) {
        LOGGER_ERROR("Loop Register Error");
        return -1;
    }

    loop->Loop();

    delete loop;
    return 0;
}
