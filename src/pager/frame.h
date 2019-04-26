#ifndef H_FRAME
#define H_FRAME

#include <iosfwd>

namespace pager
{
class Frame
{
public:
    Frame();
    Frame(int pageid, int pid, int access_time);

    int pid() const;
    int page_id() const;
    int latest_access_time() const;
    void set_latest_access_time(int t);

    Frame &operator=(Frame &rhs);
    friend std::ostream &operator<<(std::ostream &stream, const Frame &fr);

private:
    int PAGE_ID_;
    int PID_;
    int latest_access_time_;
};
} // namespace pager

#endif