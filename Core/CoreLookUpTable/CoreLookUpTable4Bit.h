#ifndef CORELOOKUPTABLE4BIT_H
#define CORELOOKUPTABLE4BIT_H

#ifdef CoreLookUpTable_StoreTableInProgramMemory
#	define	CoreLookUpTable_Read4BitTableIndex(ITEMSTATUS)					Porting_Read1ByteFromProgramMemory(CoreLookUpTable_4BitTableIndex[ (ITEMSTATUS) ])
#	define	CoreLookUpTable_Read4BitTableAccount(ITEMSTATUS)				Porting_Read1ByteFromProgramMemory(CoreLookUpTable_4BitTableaAccount[ (ITEMSTATUS) ])
#	define	CoreLookUpTable_Read4BitTableaPermutationAndCombination(INDEX)	Porting_Read1ByteFromProgramMemory(CoreLookUpTable_4BitTableaPermutationAndCombination[ (INDEX) ])
#else
#	define	CoreLookUpTable_Read4BitTableIndex(ITEMSTATUS)					(CoreLookUpTable_4BitTableIndex[ (ITEMSTATUS) ])
#	define	CoreLookUpTable_Read4BitTableAccount(ITEMSTATUS)				(CoreLookUpTable_4BitTableaAccount[ (ITEMSTATUS) ])
#	define	CoreLookUpTable_Read4BitTableaPermutationAndCombination(INDEX)	(CoreLookUpTable_4BitTableaPermutationAndCombination[ (INDEX) ])
#endif

//4-Bit Look Up Table
static const Data_1Byte CoreLookUpTable_DeclareVariableOption CoreLookUpTable_4BitTableIndex[] = {
	0, 0, 1, 0, 2, 4, 1, 0, 3, 10, 8, 7, 2, 4, 1, 0
};

static const Data_1Byte CoreLookUpTable_DeclareVariableOption CoreLookUpTable_4BitTableaAccount[] = {
	0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4
};

static const Data_1Byte CoreLookUpTable_DeclareVariableOption CoreLookUpTable_4BitTableaPermutationAndCombination[] = {
	0, 1, 2, 3, 0, 2, 3, 0, 1, 3, 0, 3
};

#endif
