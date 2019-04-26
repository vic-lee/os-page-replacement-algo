#include <iostream>

#include "frame.h"

namespace pager
{
Frame::Frame() : page_id_(-10), pid_(-10), latest_access_time_(-10){};

Frame::Frame(int pageid, int pid, int access_time)
    : page_id_(pageid), pid_(pid), latest_access_time_(access_time){};

int Frame::pid() const { return pid_; }

int Frame::page_id() const { return page_id_; }

int Frame::latest_access_time() const { return latest_access_time_; }

void Frame::set_latest_access_time(int t) { latest_access_time_ = t; }

Frame &Frame::operator=(Frame &rhs)
{
    page_id_ = rhs.page_id_;
    pid_ = rhs.pid_;
    latest_access_time_ = rhs.latest_access_time_;
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

} // namespace pager