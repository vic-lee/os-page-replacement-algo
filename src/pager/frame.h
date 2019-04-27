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
    bool is_older_than(const Frame &other) const;
    bool is_less_recently_used_than(const Frame &other) const;

    int pid() const;
    int page_id() const;
    int latest_access_time() const;
    void set_latest_access_time(int t);
    int residency_time(int eviction_time);

    Frame &operator=(Frame &rhs);
    bool operator==(Frame &rhs);
    friend std::ostream &operator<<(std::ostream &stream, const Frame &fr);

private:
    static const int UNDEF_;
    int page_id_;
    int pid_;
    int latest_access_time_;
    int time_loaded_;
};
} // namespace pager

#endif