

#include "dosstate.c"
#include "doserror.c"
#include "dosintrn.c"
#include "dosfcb.c"
#include "dosfile.c"
#include "dosexec.c"
#include "dosmem.c"
#include "doscon.c"
#include "dosnet.c"
#include "dostime.c"
#include "dosnls.c"


//Global environment pointers setup by runtime
LPCVOID _env = NULL;
LPCVOID _argc = NULL;
LPCVOID _argv = NULL;