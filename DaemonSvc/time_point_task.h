#pragma once
#include <boost/thread.hpp>
#include "scoped_handle.h"
#include "task_base.h"
#include "period_time.h"



//时间点任务：在每天、每周、每月的指定时间执行
class CTimePointTask : public CTaskBase
{
public:
    //deviation_minutes是误差
    CTimePointTask(const TaskFunc& f, const PeriodTime& period);
    ~CTimePointTask(void);

public:
    bool is_started() const;
    bool start();
    void stop();

private:
    void worker_func();

    typedef __int64 seconds_t;
    seconds_t get_last_should_execute_time();
    bool has_executed_after(const seconds_t& begin_time);
    static seconds_t get_local_time();

private:
    bool m_started;
    seconds_t m_last_executed_time;

    TaskFunc m_f;
    const PeriodTime m_period;

    boost::thread m_worker_thread;
    scoped_handle<> m_exit_event;
};

