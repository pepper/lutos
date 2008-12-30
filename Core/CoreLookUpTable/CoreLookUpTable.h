#ifndef CORELOOKUPTABLE_H
#define CORELOOKUPTABLE_H

#include "../../SystemInformation.h"
#include "CoreLookUpTable.config"

#ifdef CoreLookUpTable_StoreTableInProgramMemory
#	define	CoreLookUpTable_DeclareVariableOption	Porting_StoreInProgramMemory
#else
#	define	CoreLookUpTable_DeclareVariableOption
#endif

#ifdef CoreLookUpTable_Enable4BitLookUpTable
#	include "CoreLookUpTable4Bit.h"
#endif

#ifdef CoreLookUpTable_Enable8BitLookUpTable
#	include "CoreLookUpTable8Bit.h"
#endif

#endif
