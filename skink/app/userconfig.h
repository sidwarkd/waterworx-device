#ifndef APP_USERCONFIG_H
#define APP_USERCONFIG_H

//============================================
// RUNTIME MODE
//============================================
#define DEBUGGING
#ifndef DEBUGGING
#define RELEASE
#endif

//#define TESTING

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
// I/O Pin Settings
// =====================================================
#define mLED_Yellow     LATEbits.LATE0
#define mLED_Red        LATEbits.LATE1
#define mLED_White      LATEbits.LATE2
#define mLED_Green      LATEbits.LATE3

#define mLED            LATEbits.LATE2

#define mStation5       LATAbits.LATA5
// These settings are backward because of how the UBW board
// is laid out.  Change them if you make your own board
#define mLED_Yellow_On()        (mLED_Yellow = 0);
#define mLED_Red_On()           (mLED_Red = 0); 
#define mLED_White_On()         (mLED_White = 0);
#define mLED_Green_On()         (mLED_Green = 0);
#define mLED_Yellow_Off()       (mLED_Yellow = 1);
#define mLED_Yellow_Toggle()    (mLED_Yellow = !mLED_Yellow);
#define mLED_Red_Off()          (mLED_Red = 1);
#define mLED_Red_Toggle()       (mLED_Red = !mLED_Red);
#define mLED_White_Off()        (mLED_White = 1);
#define mLED_White_Toggle()    (mLED_White = !mLED_White);
#define mLED_Green_Off()        (mLED_Green = 1);
#define mLED_Green_Toggle()    (mLED_Green = !mLED_Green);

#define mStation5_On()        (mStation5 = 1);
#define mStation5_Off()       (mStation5  = 0);
#define mStation5_Toggle()    (mStation5  = !mStation5 );


#define mSwitch_Prog    (PORTEbits.RE7)
#define mSwitch_User    (PORTEbits.RE6)
#define SWITCH_PRESSED  0

// =====================================================
// Oscillator Settings
// =====================================================
#define CLOCK_FREQ              80000000L
#define GetSystemClock()        (80000000ul)
#define GetPeripheralClock()    (GetSystemClock()/4) 
#define GetInstructionClock()   (GetSystemClock())

//============================================
// CRYSTALFONTZ SETTINGS
//============================================
#define LCD_CS_PIN      TRISDbits.TRISD1
#define LCD_CLK_PIN     TRISDbits.TRISD2
#define LCD_DATA_PIN    TRISDbits.TRISD3

#define LCD_CS          LATDbits.LATD1
#define LCD_CLK         LATDbits.LATD2
#define LCD_DATA        LATDbits.LATD3

//============================================
// WiFi Settings
//============================================
#define MAX_PENDING_REQUESTS    2

//============================================
// MRF24WB0M WiFi I/O pins
//============================================
#define MRF24WB0M_IN_SPI1
//#define MRF24WB0M_IN_SPI2
#if defined(MRF24WB0M_IN_SPI1)
        // MRF24WB0M in SPI1 slot
        #define WF_CS_TRIS              (TRISAbits.TRISA3)
        #define WF_CS_IO                (LATAbits.LATA3)
        #define WF_SDI_TRIS             (TRISCbits.TRISC4) 
        #define WF_SCK_TRIS             (TRISDbits.TRISD10)
        #define WF_SDO_TRIS             (TRISDbits.TRISD0)
        #define WF_RESET_TRIS           (TRISFbits.TRISF0)//
        #define WF_RESET_IO             (LATFbits.LATF0)//
        #define WF_INT_TRIS             (TRISEbits.TRISE8)     // INT1
        #define WF_INT_IO               (PORTEbits.RE8)
        #define WF_HIBERNATE_TRIS       (TRISFbits.TRISF1)
        #define WF_HIBERNATE_IO         (PORTFbits.RF1)
        #define WF_INT_EDGE             (INTCONbits.INT1EP)
        #define WF_INT_IE               (IEC0bits.INT1IE)
        #define WF_INT_IF               (IFS0bits.INT1IF)
        #define WF_INT_IE_CLEAR         IEC0CLR
        #define WF_INT_IF_CLEAR         IFS0CLR
        #define WF_INT_IE_SET           IEC0SET
        #define WF_INT_IF_SET           IFS0SET
        #define WF_INT_BIT              0x00000080
        #define WF_INT_IPCSET           IPC1SET
        #define WF_INT_IPCCLR           IPC1CLR
        #define WF_INT_IPC_MASK         0xFF000000
        #define WF_INT_IPC_VALUE        0x0C000000

        #define WF_SSPBUF               (SPI1BUF)
        #define WF_SPISTAT              (SPI1STAT)
        #define WF_SPISTATbits          (SPI1STATbits)
        #define WF_SPICON1              (SPI1CON)
        #define WF_SPICON1bits          (SPI1CONbits)
        #define WF_SPI_IE_CLEAR         IEC0CLR
        #define WF_SPI_IF_CLEAR         IFS0CLR
        #define WF_SPI_INT_BITS         0x03800000
        #define WF_SPI_BRG              (SPI1BRG)
        #define WF_MAX_SPI_FREQ         (10000000ul)    // Hz

#elif defined(MRF24WB0M_IN_SPI2)
        // MRF24WB0M in SPI2 slot
        #define WF_CS_TRIS              (TRISGbits.TRISG9)
        #define WF_CS_IO                (LATGbits.LATG9)
        #define WF_SDI_TRIS             (TRISGbits.TRISG7)
        #define WF_SCK_TRIS             (TRISGbits.TRISG6)
        #define WF_SDO_TRIS             (TRISGbits.TRISG8)
        #define WF_RESET_TRIS           (TRISGbits.TRISG0)
        #define WF_RESET_IO             (LATGbits.LATG0)
        #define WF_INT_TRIS             (TRISAbits.TRISA14)     // INT3
        #define WF_INT_IO               (PORTAbits.RA14)
        #define WF_HIBERNATE_TRIS       (TRISGbits.TRISG1)
        #define WF_HIBERNATE_IO         (PORTGbits.RG1)
        #define WF_INT_EDGE             (INTCONbits.INT3EP)
        #define WF_INT_IE               (IEC0bits.INT3IE)
        #define WF_INT_IF               (IFS0bits.INT3IF)
        #define WF_INT_IE_CLEAR         IEC0CLR
        #define WF_INT_IF_CLEAR         IFS0CLR
        #define WF_INT_IE_SET           IEC0SET
        #define WF_INT_IF_SET           IFS0SET
        #define WF_INT_BIT              0x00008000
        #define WF_INT_IPCSET           IPC3SET
        #define WF_INT_IPCCLR           IPC3CLR
        #define WF_INT_IPC_MASK         0xFF000000
        #define WF_INT_IPC_VALUE        0x0C000000

        #define WF_SSPBUF               (SPI2BUF)
        #define WF_SPISTAT              (SPI2STAT)
        #define WF_SPISTATbits          (SPI2STATbits)
        #define WF_SPICON1              (SPI2CON)
        #define WF_SPICON1bits          (SPI2CONbits)
        #define WF_SPI_IE_CLEAR         IEC1CLR
        #define WF_SPI_IF_CLEAR         IFS1CLR
        #define WF_SPI_INT_BITS         0x000000e0
        #define WF_SPI_BRG              (SPI2BRG)
        #define WF_MAX_SPI_FREQ         (10000000ul)    // Hz
#endif

//============================================
// Testing Module Settings
//============================================
#define NUM_MODULES_TO_TEST     1

//============================================
// Bootlaoder Settings
//============================================
#define TRANSPORT_LAYER_SD_CARD

//============================================
// MDD Settings
//============================================
#define USE_SD_INTERFACE_WITH_SPI

//============================================
// SD CARD Settings
//============================================

/* SD Card definitions: Change these to fit your application when using
   an SD-card-based physical layer                                   */

// Registers for the SPI module you want to use
#define MDD_USE_SPI_1
//#define MDD_USE_SPI_2

//SPI Configuration
#define SPI_START_CFG_1     (PRI_PRESCAL_64_1 | SEC_PRESCAL_8_1 | MASTER_ENABLE_ON | SPI_CKE_ON | SPI_SMP_ON)
#define SPI_START_CFG_2     (SPI_ENABLE)

 // Define the SPI frequency
 #define SPI_FREQUENCY          (10000000)
   
       #if defined MDD_USE_SPI_1
            // Description: SD-SPI Chip Select Output bit
            #define SD_CS               LATBbits.LATB1
            // Description: SD-SPI Chip Select TRIS bit
            #define SD_CS_TRIS          TRISBbits.TRISB1
           
           // Description: SD-SPI Card Detect Input bit
           #define SD_CD               PORTFbits.RF0
           // Description: SD-SPI Card Detect TRIS bit
           #define SD_CD_TRIS          TRISFbits.TRISF0

           // Description: SD-SPI Write Protect Check Input bit
           #define SD_WE               PORTFbits.RF1
           // Description: SD-SPI Write Protect Check TRIS bit
           #define SD_WE_TRIS          TRISFbits.TRISF1
                  
           // Description: The main SPI control register
           #define SPICON1             SPI1CON
           // Description: The SPI status register
           #define SPISTAT             SPI1STAT
           // Description: The SPI Buffer
           #define SPIBUF              SPI1BUF
           // Description: The receive buffer full bit in the SPI status register
           #define SPISTAT_RBF         SPI1STATbits.SPIRBF
           // Description: The bitwise define for the SPI control register (i.e. _____bits)
           #define SPICON1bits         SPI1CONbits
           // Description: The bitwise define for the SPI status register (i.e. _____bits)
           #define SPISTATbits         SPI1STATbits
           // Description: The enable bit for the SPI module
           #define SPIENABLE           SPICON1bits.ON
           // Description: The definition for the SPI baud rate generator register (PIC32)
           #define SPIBRG               SPI1BRG

            // Tris pins for SCK/SDI/SDO lines
            #if defined(__32MX360F512L__) // All PIC32MX3XX 
                // Description: The TRIS bit for the SCK pin
                #define SPICLOCK            TRISFbits.TRISF6
                // Description: The TRIS bit for the SDI pin
                #define SPIIN               TRISFbits.TRISF7
                // Description: The TRIS bit for the SDO pin
                #define SPIOUT              TRISFbits.TRISF8
            #else   // example: PIC32MX360F512L
                // Description: The TRIS bit for the SCK pin
                #define SPICLOCK            TRISDbits.TRISD10
                // Description: The TRIS bit for the SDI pin
                #define SPIIN               TRISCbits.TRISC4
                // Description: The TRIS bit for the SDO pin
                #define SPIOUT              TRISDbits.TRISD0
            #endif

                //SPI library functions
            #define putcSPI             putcSPI1
            #define getcSPI             getcSPI1
            #define OpenSPI(config1, config2)   OpenSPI1(config1, config2)
            
        #elif defined MDD_USE_SPI_2
            // Description: SD-SPI Chip Select Output bit
            #define SD_CS               LATBbits.LATB9
            // Description: SD-SPI Chip Select TRIS bit
            #define SD_CS_TRIS          TRISBbits.TRISB9
            
            // Description: SD-SPI Card Detect Input bit
            #define SD_CD               PORTGbits.RG0
            // Description: SD-SPI Card Detect TRIS bit
            #define SD_CD_TRIS          TRISGbits.TRISG0

            // Description: SD-SPI Write Protect Check Input bit
            #define SD_WE               PORTGbits.RG1
            // Description: SD-SPI Write Protect Check TRIS bit
            #define SD_WE_TRIS          TRISGbits.TRISG1
            
            // Description: The main SPI control register
            #define SPICON1             SPI2CON
            // Description: The SPI status register
            #define SPISTAT             SPI2STAT
            // Description: The SPI Buffer
            #define SPIBUF              SPI2BUF
            // Description: The receive buffer full bit in the SPI status register
            #define SPISTAT_RBF         SPI2STATbits.SPIRBF
            // Description: The bitwise define for the SPI control register (i.e. _____bits)
            #define SPICON1bits         SPI2CONbits
            // Description: The bitwise define for the SPI status register (i.e. _____bits)
            #define SPISTATbits         SPI2STATbits
            // Description: The enable bit for the SPI module
            #define SPIENABLE           SPI2CONbits.ON
            // Description: The definition for the SPI baud rate generator register (PIC32)
            #define SPIBRG              SPI2BRG

            // Tris pins for SCK/SDI/SDO lines

            // Description: The TRIS bit for the SCK pin
            #define SPICLOCK            TRISGbits.TRISG6
            // Description: The TRIS bit for the SDI pin
            #define SPIIN               TRISGbits.TRISG7
            // Description: The TRIS bit for the SDO pin
            #define SPIOUT              TRISGbits.TRISG8
            //SPI library functions
            #define putcSPI             putcSPI2
            #define getcSPI             getcSPI2
            #define OpenSPI(config1, config2)   OpenSPI2(config1, config2)
        #endif       
        // Will generate an error if the clock speed is too low to interface to the card
        #if (GetSystemClock() < 100000)
            #error Clock speed must exceed 100 kHz
        #endif 

#endif

