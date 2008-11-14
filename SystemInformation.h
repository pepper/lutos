#ifndef	SYSTEMINFORMATION_H
#define	SYSTEMINFORMATION_H

//#define	SystemInformation_IntelMacOSX
#define	SystemInformation_AVR

#if defined(SystemInformation_AVR)
	#define	SystemInformation_SystemClock		11059200
	//#define	SystemInformation_DeviceATmega128	
	#define	SystemInformation_DeviceAT90CAN128
#endif

#endif
