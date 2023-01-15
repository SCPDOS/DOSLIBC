/*
    The start of a DOS low level library upon which stdlib (newlib) will be 
    built!
*/
#ifndef _SCPDOS_H
#define _SCPDOS_H
#pragma pack(push, 1) //Ensure all structs are aligned to 1 byte boundaries

#include "Headers/basetsd.h"
#include "Headers/dosstate.h"
#include "Headers/dosdisk.h"
#include "Headers/doserror.h"
#include "Headers/dosintrn.h"
#include "Headers/dosdrvr.h"
#include "Headers/dosfcb.h"
#include "Headers/dosfile.h"
#include "Headers/dosexec.h"
#include "Headers/dosmem.h"
#include "Headers/doscon.h"
#include "Headers/dosnet.h"
#include "Headers/dostime.h"
#include "Headers/dosnls.h"

#pragma pack(pop)

//Export the global runtime vars
LPCVOID _env;
LPCVOID _argc;
LPCVOID _argv;

#endif