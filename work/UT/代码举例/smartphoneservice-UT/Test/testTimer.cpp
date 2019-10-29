#include "testTimer.h"
#include "TimerManager.h"

namespace goni
{
Timer::Timer(TimerClient *client)
    : m_id(InvalidTimerId)
    , m_started(false)
    , m_client(client)
    , m_oneShot(true)
{
}

Timer::~Timer()
{
    if(isActive()) {
        stop();
    }
}

TimerClient *Timer::client()
{
    return m_client;
}

void Timer::setClient(TimerClient *client)
{
    m_client = client;
}

int Timer::id()
{
    return m_id;
}

void Timer::start(int interval, bool oneShot)
{
    if (m_started) {
        return;
    }
    m_oneShot = oneShot;
    if(BS_NO_ERROR == TimerManagerInst.startTimer(interval, &Timer::timerFunc, this, oneShot, m_id)) {
        m_started = true;
        return;
    }
    BSLOGW("Timer::start timer start failed m_id %d", m_id);
}

void Timer::stop()
{
    if (!m_started) {
        return;
    }
    if(BS_NO_ERROR == TimerManagerInst.stopTimer(m_id)) {
        m_id = InvalidTimerId;
        m_started = false;
        return;
    }
    BSLOGW("Timer::stop timer stop failed");
}

bool Timer::isActive() const
{
    return m_started;
}

void Timer::timerFunc(int timerId, void *param)
{
    Timer *timer = static_cast<Timer *>(param);
    if(timer != NULL) {
        BSASSERT(timer->m_id == timerId, "Timer::timerFunc bad id");
        timer->fired();
    }
}

void Timer::fired()
{
    if(m_oneShot) {
        m_started = false;
    }
    if(m_client != NULL) {
        m_client->onTimer(this);
    }
    //in onTimer callback may call startTimer, so clear id when timer is not active
    if(m_oneShot && !m_started) {
        m_id = InvalidTimerId;
    }
}
}
