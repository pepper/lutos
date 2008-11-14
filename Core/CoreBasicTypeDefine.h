/*!
 @header	Basic Type Define
			本標頭檔包含了所有本人撰寫的模組所用的基本型別的定義，用處在於順利在不同的機器上執行而不會產生執行上的差異
 @copyright	PEPPER.YEN at MVMC Lab.
 @updated	2008-03-25
 @version	1.2.0
 */
#ifndef COREBASICTYPEDEFINE_H
#define	COREBASICTYPEDEFINE_H

#include "../SystemInformation.h"

#if defined(SystemInformation_IntelMacOSX) || defined (SystemInformation_AVR)
	
	#ifndef NULL
		#define NULL 0
	#endif

	#ifndef __cplusplus
		#define	TRUE	1
		#define	FALSE	0
		/*!
		 @typedef	Data_Boolean
		 @abstract	利用一個Byte的資料空間模擬出布林代數的資料型態。
		 */
		typedef unsigned char	Data_Boolean;
	#endif

	#ifdef __cplusplus
		#define	TRUE	true
		#define	FALSE	false
		typedef bool			Data_Boolean;
	#endif

	/*!
	 @typedef	Data_1Byte
	 @abstract	一個Byte的資料空間。
	 */
	typedef	unsigned char	Data_1Byte;

	/*!
	 @typedef	Data_2Byte
	 @abstract	二個Byte的資料空間。
	 */
	typedef	unsigned short	Data_2Byte;

	/*!
	 @typedef	Data_4Byte
	 @abstract	四個Byte的資料空間。
	 */
	typedef	unsigned int	Data_4Byte;

	/*!
	 @typedef	Data_1Byte
	 @abstract	一個Byte包含正負號的資料空間。
	 */
	typedef char			Data_1ByteSigned;

	/*!
	 @typedef	Data_2Byte
	 @abstract	二個Byte包含正負號的資料空間。
	 */
	typedef short			Data_2ByteSigned;

	/*!
	 @typedef	Data_4Byte
	 @abstract	四個Byte包含正負號的資料空間。
	 */
	typedef int				Data_4ByteSigned;

	/*!
	 @typedef	Data_Float
	 @abstract	單精度浮點數資料空間。
	 */
	typedef	float	Data_Float;

	/*!
	 @typedef	Data_Double
	 @abstract	背精度浮點數資料空間。
	 */
	typedef	double	Data_Double;

#endif

#endif
