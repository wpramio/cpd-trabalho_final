#include <assert.h>
#include "Timer.h"

Timer::Timer(string name):
    running_(false)
{
    name_ = name;
    get_frequency(&frequency_);
}

void Timer::start()
{
    running_ = true;
    clock_now(&start_time_);
    last_lap_time_ = start_time_;
}

void Timer::stop()
{
    assert(running_ == true);
    clock_now(&end_time_);
    running_ = false;
}

void Timer::reset()
{
    assert(running_ == true);
    clock_now(&start_time_);
    last_lap_time_ = start_time_;
}

double Timer::get_lap(time_unit_type unit_type)
{
    double ret;
    assert(running_ == true);
    TIME_UNIT lap_time;
    clock_now(&lap_time);
    ret = millisec_gap(last_lap_time_, lap_time, frequency_);
    last_lap_time_ = lap_time;
    return ret / unit_type;
}

void Timer::lap(string name)
{
    printf("%s timer %s lap takes: %.4fms\n", name_.c_str(), name.c_str(), get_lap());
}


double Timer::get_total(time_unit_type unit_type)
{
    double ret;
    if (running_)
    {
        TIME_UNIT now;
        clock_now(&now);
        ret = millisec_gap(start_time_, now, frequency_);
    }
    else
    {
        ret = millisec_gap(start_time_, end_time_, frequency_);
    }
    return ret / unit_type;
}

void Timer::print()
{
    printf("%s timer totally elpased: %.4fms\n", name_.c_str(),
            get_total());
}

TIME_UNIT Timer::get_current_timestamp()
{
    TIME_UNIT current_time;
    clock_now(&current_time);
    return current_time;
}

double Timer::get_time_gap(const TIME_UNIT &begin, const TIME_UNIT &end, time_unit_type unit_type)
{
    return millisec_gap(begin, end, frequency_) / (int)unit_type;
}