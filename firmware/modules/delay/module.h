#ifndef DELAY_MODULE_H
#define DELAY_MODULE_H

#include <base/module.h>
#ifndef __C32__
#include <delays.h>
#endif

#if !defined(GetInstructionClock)
	#error GetInstructionClock() must be defined.
#endif

#if defined(__18CXX) && !defined(HI_TECH_C)
	#define Delay10us(us)		Delay10TCYx(((GetInstructionClock()/1000000)*(us)))
	#define DelayMs(ms)												\
	do																\
	{																\
		unsigned int _iTemp = (ms); 								\
		while(_iTemp--)												\
			Delay1KTCYx((GetInstructionClock()+999999)/1000000);	\
	} while(0)

#elif defined(__C30__) || defined(__C32__)
	void Delay10us(DWORD dwCount);
	void DelayMs(WORD ms);

#else
	#define Delay10us(x)			\
	do 								\
	{								\
		unsigned long _dcnt;		\
		_dcnt=x*((unsigned long)(0.00001/(1.0/GetInstructionClock())/6));	\
		while(_dcnt--);				\
	} while(0)
	void DelayMs(WORD ms);
#endif

#endif
