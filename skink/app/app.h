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
//#include <mdd/module.h>
#include <bootldr/module.h>
//#include <crystalfontz/module.h>
//#include <wifi/module.h>
//#include <json/module.h>
//#include <usb/module.h>
#include <sdcard/module.h>
//#include <rtcc/module.h>


#ifdef TESTING
//#include <test/module.h>
#endif

#endif
