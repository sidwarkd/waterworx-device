#ifndef __USB_MODULE
#define __USB_MODULE


//#define tris_self_power     TRISAbits.TRISA2    // Input
#define self_power          1

//#define USE_USB_BUS_SENSE_IO
//#define tris_usb_bus_sense  TRISBbits.TRISB5    // Input
#define USB_BUS_SENSE       1 

#define BAUDRATE2       57600UL
#define BRG_DIV2        4 
#define BRGH2           1 

void SERIALUSB_Initialize(void);
void SERIALUSB_ProcessTasks(void);
void SERIALUSB_Write(char *data);

#endif