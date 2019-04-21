#ifndef H_MREFSPEC
#define H_MREFSPEC

namespace driver
{
typedef int RefType;

extern const RefType INIT_REF; /* Initial memory reference keyword */
extern const RefType SEQ_REF;  /* Sequential memory reference keyword */
extern const RefType BACK_REF; /* Backward memory reference keyword */
extern const RefType JMP_REF;  /* Jump memory reference keyword */
extern const RefType RAND_REF; /* Random memory reference keyword */

} // namespace driver

#endif