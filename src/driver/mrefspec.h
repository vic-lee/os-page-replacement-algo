#ifndef H_MREFSPEC
#define H_MREFSPEC

namespace driver
{
typedef int RefType;

extern RefType SEQ_REF;  /* Sequential memory reference keyword */
extern RefType BACK_REF; /* Backward memory reference keyword */
extern RefType JMP_REF;  /* Jump memory reference keyword */
extern RefType RAND_REF; /* Random memory reference keyword */

} // namespace driver

#endif