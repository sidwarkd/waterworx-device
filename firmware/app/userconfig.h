#ifndef APP_USERCONFIG_H
#define APP_USERCONFIG_H

//============================================
// CONFIGURATION BITS
//============================================
#if defined(APPLICATION_ENTRY_POINT)
    #ifdef __18F27J53
        #pragma config WDTEN	= OFF		// Watchdog disabled
        #pragma config PLLDIV	= 2		// 8 MHz crystal
        #pragma config CFGPLLEN     = ON		// PLL Enabled
        #pragma config STVREN	= ON		// Stack over/underflow reset enabled
        #pragma config XINST	= OFF		// Extended instruction set off
        #pragma config CPUDIV	= OSC3_PLL3	// CPU system clock divide by 3
        #pragma config CP0	        = OFF		// Disable code protect
        #pragma config OSC	        = INTOSCPLL	// Use internal oscillator
        #pragma config SOSCSEL 	= DIG
        #pragma config CLKOEC	= OFF		// CLKO output disabled on RA6
        #pragma config FCMEN	= OFF		// Fail-Safe clock monitor off
        #pragma config IESO	        = OFF		// Internal/External osc switch over mode
        #pragma config WDTPS 	= 32768		// WD post scalar
        #pragma config DSWDTOSC	= INTOSCREF	// DSWDT uses INTRC
        #pragma config RTCOSC	= INTOSCREF	// RTCC clock select
        #pragma config DSBOREN	= OFF		// Deep Sleep BOR
        #pragma config DSWDTEN	= OFF		// Deep Sleep WDT
        #pragma config DSWDTPS	= K32		// Deep Sleep WDT Postscalar
        #pragma config IOL1WAY	= OFF		// IOCLOCK one-way enable
        #pragma config ADCSEL	= BIT10		// ADC 10 bit
        #pragma config MSSP7B_EN    = MSK5		// MSSP address masking
        #pragma config WPCFG	= OFF		// Config words page write protect
        #pragma config WPDIS	= OFF		// WPCFG bits ignored
        #pragma config LS48MHZ	= SYS48X8
    #elif defined(__PIC32MX__)
        // The oscillator settings here create an 80MHz system clock
        #pragma config FVBUSONIO        = ON
        #pragma config FUSBIDIO         = ON
        #pragma config FCANIO           = ON
        #pragma config FETHIO           = ON
        #pragma config FMIIEN           = ON
        #pragma config FSRSSEL          = PRIORITY_7
        #pragma config FPLLODIV         = DIV_1
        #pragma config UPLLEN           = ON
        #pragma config UPLLIDIV         = DIV_2
        #pragma config FPLLMUL          = MUL_20
        #pragma config FPLLIDIV         = DIV_2
        #pragma config FWDTEN           = OFF
        #pragma config WDTPS            = PS1
        #pragma config FCKSM            = CSDCMD
        #pragma config FPBDIV           = DIV_1
        #pragma config OSCIOFNC         = OFF
        #pragma config POSCMOD          = HS
        #pragma config IESO             = OFF
        #pragma config FSOSCEN          = ON
        #pragma config FNOSC            = PRIPLL
        #pragma config CP               = OFF
        #pragma config BWP              = OFF
        #pragma config PWP              = OFF
        #pragma config ICESEL           = ICS_PGx1
        #pragma config DEBUG            = OFF
    #else
        #error Unrecognized device.  Define config settings for your target in userconfig.h
    #endif
    
#endif


// =====================================================
// Oscillator Settings
// =====================================================
#define GetSystemClock()            (80000000ul)
#define GetPeripheralClock()        (GetSystemClock()) 
#define GetInstructionClock()       (GetSystemClock())

#endif

