#ifndef APP_H
#define APP_H

#include "userconfig.h"
#include <plib.h>

void InitializeSystem();

// Modules
#include <base/module.h>
#include <delay/module.h>
#include <crystalfontz/module.h>
#include <wifi/module.h>
#include <json/module.h>
#include <sprinkler/module.h>
#include <usb/module.h>

#endif
