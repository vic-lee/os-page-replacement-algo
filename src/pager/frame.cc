#include <iostream>

#include "frame.h"

namespace pager
{
const int Frame::UNDEF_ = -10;

Frame::Frame() : page_id_(UNDEF_), pid_(UNDEF_), latest_access_time_(UNDEF_), time_loaded_(UNDEF_){};

Frame::Frame(int pageid, int pid, int access_time)
    : page_id_(pageid), pid_(pid), latest_access_time_(access_time), time_loaded_(access_time){};

bool Frame::is_older_than(Frame &other) const
{
    return (is_initialized() && (latest_access_time_ < other.latest_access_time()));
}

int Frame::residency_time(int eviction_time)
{
    return (eviction_time - time_loaded_);
}

Frame &Frame::operator=(Frame &rhs)
{
    page_id_ = rhs.page_id_;
    pid_ = rhs.pid_;
    latest_access_time_ = rhs.latest_access_time_;
    time_loaded_ = rhs.time_loaded_;
    return *this;
}

bool Frame::operator==(Frame &rhs)
{
    return (this->page_id_ == rhs.page_id_ && this->pid_ == rhs.pid_);
}

std::ostream &operator<<(std::ostream &stream, const Frame &fr)
{
    stream << "Frame: \tprocess id " << fr.pid_ << " page id " << fr.page_id_;
    return stream;
}

bool Frame::is_initialized() const { return pid_ != UNDEF_; }

int Frame::pid() const { return pid_; }

int Frame::page_id() const { return page_id_; }

int Frame::latest_access_time() const { return latest_access_time_; }

void Frame::set_latest_access_time(int t) { latest_access_time_ = t; }

} // namespace pager