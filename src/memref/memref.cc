#include "memref.h"

namespace memref
{

Reference::Reference(int pid, int delta) : pid_(pid), delta_(delta), INIT_FACTOR_(111){}

}