

#include "Source/dosstate.c"
#include "Source/doserror.c"
#include "Source/dosintrn.c"
#include "Source/dosfcb.c"
#include "Source/dosfile.c"
#include "Source/dosexec.c"
#include "Source/dosmem.c"
#include "Source/doscon.c"
#include "Source/dosnet.c"
#include "Source/dostime.c"
#include "Source/dosnls.c"


//Global environment pointers setup by runtime
LPCVOID _env = NULL;
LPCVOID _argc = NULL;
LPCVOID _argv = NULL;