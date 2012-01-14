#ifndef CRYSTALFONTZ_MODULE_H
#define CRYSTALFONTZ_MODULE_H

#include <base/module.h>
#include <delay/module.h>

// Verify the appropriate modules have been included
#ifndef DELAY_MODULE_H
	#error Missing the delay module. Make sure it is included and that the 'modules' folder is in the include directory lookup
#endif

#ifndef LCD_CS_PIN
#error LCS_CS_PIN needs to be defined in userconfig.h
#endif
#ifndef LCD_CLK_PIN
#error LCD_CLK_PIN needs to be defined in userconfig.h
#endif
#ifndef LCD_DATA_PIN
#error LCD_DATA_PIN needs to be defined in userconfig.h
#endif
#ifndef LCD_CS
#error LCD_CS needs to be defined in userconfig.h
#endif
#ifndef LCD_CLK
#error LCD_CLK needs to be defined in userconfig.h
#endif
#ifndef LCD_DATA
#error LCD_DATA needs to be defined in userconfig.h
#endif

// ============================================================================
// FUNCTION PROTOTYPES
// ============================================================================
void LCD_Initialize(void);
void LCD_WriteFromROM(const rom CHAR *data);
void LCD_WriteFromRAM(const ram CHAR *data);
void LCD_ClearScreen(void);
void WriteLCDSPIByte(CHAR b);
void LCD_SetContrast(BYTE level);

#endif