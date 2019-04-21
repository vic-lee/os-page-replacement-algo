namespace driver
{
class Process
{
public:
    Process(int id, int proc_size);
    void do_next_sequential_reference();
    void do_next_backward_reference();
    void do_next_jump_reference();

private:
    void do_next_reference(int delta);

    const int ID_;
    const int SIZE_;
    const int INIT_CONST_;
    int current_ref_addr_;
};
} // namespace driverß