#ifndef H_FRAME
#define H_FRAME

namespace pager
{
class Frame
{
public:
    Frame();
    Frame(int pageid, int pid, int access_time);

private:
    const int PAGE_ID_;
    const int PID_;
    int latest_access_time_;
};
} // namespace pager

#endif