#ifndef TIMER_H
#define TIMER_H

#include "servicebase/ServiceBaseDefines.h"
#include "servicebase/ServiceBaseGlobal.h"

namespace goni
{
class Timer;
class SERVICEBASE_API TimerClient
{
public:
    virtual ~TimerClient(){}
    virtual void onTimer(Timer *) = 0;
};

class SERVICEBASE_API Timer
{
public:
    explicit Timer(TimerClient *client);
    ~Timer();

    TimerClient *client();
    void setClient(TimerClient *client);

    int id();
    void start(int interval, bool oneShot = true);
    void stop();
    bool isActive() const;
private:
    static void timerFunc(int timerId, void *param);
    void fired();
    int m_id;
    bool m_started;
    TimerClient* m_client;
    bool m_oneShot;
};

template <class Receiver>
class SERVICEBASE_API EasyTimer : public TimerClient
{
public:
    typedef void (Receiver::*ReceiverMethod)(Timer *);
    EasyTimer();
    ~EasyTimer();
    void start(int interval, bool oneShot, Receiver *receiver, ReceiverMethod method);
    void stop();
    int id();
    bool isActive() const;
    virtual void onTimer(Timer* timer);
private:
    Receiver *m_receiver;
    ReceiverMethod m_method;
    Timer *m_internalTimer;
};

template <class Receiver>
EasyTimer<Receiver>::EasyTimer()
    : m_receiver(NULL)
    , m_method(NULL)
    , m_internalTimer(NULL)
{
    m_internalTimer = new Timer(this);
}

template <class Receiver>
EasyTimer<Receiver>::~EasyTimer()
{
    delete m_internalTimer;
    m_internalTimer = NULL;
    m_receiver = NULL;
}

template <class Receiver>
void EasyTimer<Receiver>::stop()
{
    m_internalTimer->stop();
}

template <class Receiver>
int EasyTimer<Receiver>::id()
{
    if(m_internalTimer != NULL) {
        return m_internalTimer->id();
    }
    return InvalidTimerId;
}

template <class Receiver>
bool EasyTimer<Receiver>::isActive() const
{
    if(m_internalTimer != NULL) {
        return m_internalTimer->isActive();
    }
    return false;
}

template <class Receiver>
void EasyTimer<Receiver>::start(int interval, bool oneShot, Receiver *receiver, ReceiverMethod method)
{
    m_receiver = receiver;
    m_method = method;
    m_internalTimer->start(interval, oneShot);
}

template <class Receiver>
void EasyTimer<Receiver>::onTimer(Timer *timer)
{
    if(NULL != m_receiver) {
        (m_receiver->*(m_method))(timer);
    }
}
}
#endif // TIMER_H
