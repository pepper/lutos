#ifndef PORTINGDATATYPE_H
#define PORTINGDATATYPE_H

//Data Type Definition
#ifndef NULL
#define NULL 0
#endif

#ifndef __cplusplus
#define	TRUE	1
#define	FALSE	0
typedef unsigned char	Data_Boolean;
#endif

#ifdef __cplusplus
#define	TRUE	true
#define	FALSE	false
typedef bool			Data_Boolean;
#endif

typedef	unsigned char	Data_1Byte;
typedef	unsigned short	Data_2Byte;
typedef	unsigned int	Data_4Byte;
typedef char			Data_1ByteSigned;
typedef short			Data_2ByteSigned;
typedef int				Data_4ByteSigned;
typedef	float			Data_Float;
typedef	double			Data_Double;

#endif
