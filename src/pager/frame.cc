#include "frame.h"

namespace pager
{
Frame::Frame() : PAGE_ID_(-10), PID_(-10), latest_access_time_(-10){};

Frame::Frame(int pageid, int pid, int access_time)
    : PAGE_ID_(), PID_(), latest_access_time_(access_time){};
} // namespace pager