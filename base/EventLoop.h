#ifndef MOXIE_EVENTLOOP_H
#define MOXIE_EVENTLOOP_H
#include <memory>
#include <assert.h>
#include <unordered_map>
#include <atomic>

#include <moxie/base/PollerEvent.h>
#include <moxie/base/SigIgnore.h>
#include <moxie/base/Handler.h>
#include <moxie/base/Epoll.h>
#include <moxie/base/Mutex.h>
#include <moxie/base/MutexLocker.h>
#include <moxie/base/TimerEngine.h>

namespace moxie {

class EventLoop {
public:
    EventLoop();

    bool Register(const std::shared_ptr<PollerEvent>& event, const std::shared_ptr<Handler>& handler);
    bool Modity(const std::shared_ptr<PollerEvent>&  event);
    bool Delete(const std::shared_ptr<PollerEvent>& event);

    bool RegisterTimer(Timer* timer);
    bool UnregisterTimer(Timer* timer);

    void Loop();
    void Quit();
    bool Started() const;
private:
    struct EventContext {
        int fd;
        std::shared_ptr<PollerEvent> event;
        std::shared_ptr<Handler> handle;
    };
private:
    Epoll *epoll_;
    std::unordered_map<int, EventContext*> contexts_;
    std::atomic_bool quit_;
    std::atomic_bool started_;
    SigIgnore ignore_;
    static size_t kEpollRetBufSize;
    static size_t kDefaultTimeOut;
    std::shared_ptr<TimerEngine> te_;
};

}

#endif // MOXIE_EVENTLOOP_H
