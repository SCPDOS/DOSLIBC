/*
    The start of a DOS low level library upon which stdlib (newlib) will be 
    built!
*/
#ifndef _SCPDOS_H
#define _SCPDOS_H
#pragma pack(push, 1) //Ensure all structs are aligned to 1 byte boundaries

#include "basetsd.h"
#include "dosstate.h"
#include "dosdisk.h"
#include "doserror.h"
#include "dosintrn.h"
#include "dosdrvr.h"
#include "dosfcb.h"
#include "dosfile.h"
#include "dosexec.h"
#include "dosmem.h"
#include "doscon.h"
#include "dosnet.h"
#include "dostime.h"
#include "dosnls.h"

#pragma pack(pop)

//Export the global runtime vars
LPCVOID _env;
LPCVOID _argc;
LPCVOID _argv;

#endif