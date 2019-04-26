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

    bool is_initialized() const;

    int pid() const;
    int page_id() const;
    int latest_access_time() const;
    void set_latest_access_time(int t);

    Frame &operator=(Frame &rhs);
    bool operator==(Frame &rhs);
    friend std::ostream &operator<<(std::ostream &stream, const Frame &fr);

private:
    static const int UNDEF_;
    int page_id_;
    int pid_;
    int latest_access_time_;
};
} // namespace pager

#endif