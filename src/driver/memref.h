#ifndef H_MREFSPEC
#define H_MREFSPEC

namespace driver
{
enum RefType
{
    INIT_REF, /* Initial memory reference keyword */
    SEQ_REF,  /* Sequential memory reference keyword */
    BACK_REF, /* Backward memory reference keyword */
    JMP_REF,  /* Jump memory reference keyword */
    RAND_REF  /* Random memory reference keyword */
};

} // namespace driver

#endif