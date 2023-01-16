//
// Current standard library, for now freestanding ONLY
//

//Freestanding libraries: X means implemented, O means unimplemented yet
//
//Headers available as of ANSI
//<float.h>  O
//<limits.h> X
//<iso646.h>
//<stdarg.h> O
//<stddef.h> O

//Headers available as of C99
//<stdbool.h> X
//<stdint.h>  X

#pragma once 
#ifndef _STDLIB_H
#define _STDLIB_H

//ANSI Headers
#include "./float.h"
#include "./limits.h"
#include "./iso646.h"
#include "./stdarg.h"
#include "./stddef.h"
//C99 Headers
#include "./stdbool.h"
#include "./stdint.h"

#endif