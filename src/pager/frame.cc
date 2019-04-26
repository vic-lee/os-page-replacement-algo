#include <iostream>

#include "frame.h"

namespace pager
{
Frame::Frame() : PAGE_ID_(-10), PID_(-10), latest_access_time_(-10){};

Frame::Frame(int pageid, int pid, int access_time)
    : PAGE_ID_(), PID_(), latest_access_time_(access_time){};

int Frame::pid() const { return PID_; }

int Frame::page_id() const { return PAGE_ID_; }

int Frame::latest_access_time() const { return latest_access_time_; }

void Frame::set_latest_access_time(int t) { latest_access_time_ = t; }

Frame &Frame::operator=(Frame &) { return *this; }

std::ostream &operator<<(std::ostream &stream, const Frame &fr)
{
    stream << "Frame: \tprocess id " << fr.PID_ << " page id " << fr.PAGE_ID_;
    return stream;
}

} // namespace pager