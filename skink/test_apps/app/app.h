#ifndef APP_H
#define APP_H

#include <xc.h>
#include <plib.h>
#include "userconfig.h"
#include <string.h>

void InitializeSystem();

// Modules
#include <base/module.h>
#include <delay/module.h>


#ifdef TESTING
//#include <test/module.h>
#endif

#endif
