#ifndef CORELOOKUPTABLE8BIT_H
#define CORELOOKUPTABLE8BIT_H

#ifdef CoreLookUpTable_StoreTableInProgramMemory
#	define	CoreLookUpTable_Read8BitTableIndex(ITEMSTATUS)					Porting_Read2ByteFromProgramMemory(CoreLookUpTable_8BitTableIndex[ (ITEMSTATUS) ])
#	define	CoreLookUpTable_Read8BitTableAccount(ITEMSTATUS)				Porting_Read1ByteFromProgramMemory(CoreLookUpTable_8BitTableaAccount[ (ITEMSTATUS) ])
#	define	CoreLookUpTable_Read8BitTableaPermutationAndCombination(INDEX)	Porting_Read1ByteFromProgramMemory(CoreLookUpTable_8BitTableaPermutationAndCombination[ (INDEX) ])
#else
#	define	CoreLookUpTable_Read8BitTableIndex(ITEMSTATUS)					(CoreLookUpTable_8BitTableIndex[ (ITEMSTATUS) ])
#	define	CoreLookUpTable_Read8BitTableAccount(ITEMSTATUS)				(CoreLookUpTable_8BitTableaAccount[ (ITEMSTATUS) ])
#	define	CoreLookUpTable_Read8BitTableaPermutationAndCombination(INDEX)	(CoreLookUpTable_8BitTableaPermutationAndCombination[ (INDEX) ])
#endif

//8-Bit Look Up Table
static const Data_2Byte CoreLookUpTable_DeclareVariableOption CoreLookUpTable_8BitTableIndex[] = {
	0,		0,		1,		0,		2,		176,	1,		0,
	3,		256,	97,		96,		2,		176,	1,		0,
	4,		292,	141,	140,	54,		220,	53,		52,
	3,		256,	97,		96,		2,		176,	1,		0,
	5,		308,	161,	160,	78,		240,	77,		76,
	31,		276,	121,	120,	30,		200,	29,		28,
	4,		292,	141,	140,	54,		220,	53,		52,
	3,		256,	97,		96,		2,		176,	1,		0,
	6,		315,	170,	169,	89,		249,	88,		87,
	44,		285,	132,	131,	43,		211,	42,		41,
	19,		301,	152,	151,	67,		231,	66,		65,
	18,		267,	110,	109,	17,		189,	16,		15,
	5,		308,	161,	160,	78,		240,	77,		76,
	31,		276,	121,	120,	30,		200,	29,		28,
	4,		292,	141,	140,	54,		220,	53,		52,
	3,		256,	97,		96,		2,		176,	1,		0,
	7,		318,	174,	173,	94,		253,	93,		92,
	50,		289,	137,	136,	49,		216,	48,		47,
	26,		305,	157,	156,	73,		236,	72,		71,
	25,		272,	116,	115,	24,		195,	23,		22,
	13,		312,	166,	165,	84,		245,	83,		82,
	38,		281,	127,	126,	37,		206,	36,		35,
	12,		297,	147,	146,	61,		226,	60,		59,
	11,		262,	104,	103,	10,		183,	9,		8,
	6,		315,	170,	169,	89,		249,	88,		87,
	44,		285,	132,	131,	43,		211,	42,		41,
	19,		301,	152,	151,	67,		231,	66,		65,
	18,		267,	110,	109,	17,		189,	16,		15,
	5,		308,	161,	160,	78,		240,	77,		76,
	31,		276,	121,	120,	30,		200,	29,		28,
	4,		292,	141,	140,	54,		220,	53,		52,
	3,		256,	97,		96,		2,		176,	1,		0
};

static const Data_1Byte CoreLookUpTable_DeclareVariableOption CoreLookUpTable_8BitTableaAccount[] = {
	0,	1,	1,	2,	1,	2,	2,	3,
	1,	2,	2,	3,	2,	3,	3,	4,
	1,	2,	2,	3,	2,	3,	3,	4,
	2,	3,	3,	4,	3,	4,	4,	5,
	1,	2,	2,	3,	2,	3,	3,	4,
	2,	3,	3,	4,	3,	4,	4,	5,
	2,	3,	3,	4,	3,	4,	4,	5,
	3,	4,	4,	5,	4,	5,	5,	6,
	1,	2,	2,	3,	2,	3,	3,	4,
	2,	3,	3,	4,	3,	4,	4,	5,
	2,	3,	3,	4,	3,	4,	4,	5,
	3,	4,	4,	5,	4,	5,	5,	6,
	2,	3,	3,	4,	3,	4,	4,	5,
	3,	4,	4,	5,	4,	5,	5,	6,
	3,	4,	4,	5,	4,	5,	5,	6,
	4,	5,	5,	6,	5,	6,	6,	7,
	1,	2,	2,	3,	2,	3,	3,	4,
	2,	3,	3,	4,	3,	4,	4,	5,
	2,	3,	3,	4,	3,	4,	4,	5,
	3,	4,	4,	5,	4,	5,	5,	6,
	2,	3,	3,	4,	3,	4,	4,	5,
	3,	4,	4,	5,	4,	5,	5,	6,
	3,	4,	4,	5,	4,	5,	5,	6,
	4,	5,	5,	6,	5,	6,	6,	7,
	2,	3,	3,	4,	3,	4,	4,	5,
	3,	4,	4,	5,	4,	5,	5,	6,
	3,	4,	4,	5,	4,	5,	5,	6,
	4,	5,	5,	6,	5,	6,	6,	7,
	3,	4,	4,	5,	4,	5,	5,	6,
	4,	5,	5,	6,	5,	6,	6,	7,
	4,	5,	5,	6,	5,	6,	6,	7,
	5,	6,	6,	7,	6,	7,	7,	8
};

static const Data_1Byte CoreLookUpTable_DeclareVariableOption CoreLookUpTable_8BitTableaPermutationAndCombination[] = {
	0, 1, 2, 3, 4, 5, 6, 7, 0, 1, 2, 3, 4, 5, 7, 0, 
	1, 2, 3, 4, 6, 7, 0, 1, 2, 3, 4, 7, 0, 1, 2, 3, 
	5, 6, 7, 0, 1, 2, 3, 5, 7, 0, 1, 2, 3, 6, 7, 0, 
	1, 2, 3, 7, 0, 1, 2, 4, 5, 6, 7, 0, 1, 2, 4, 5, 
	7, 0, 1, 2, 4, 6, 7, 0, 1, 2, 4, 7, 0, 1, 2, 5, 
	6, 7, 0, 1, 2, 5, 7, 0, 1, 2, 6, 7, 0, 1, 2, 7, 
	0, 1, 3, 4, 5, 6, 7, 0, 1, 3, 4, 5, 7, 0, 1, 3, 
	4, 6, 7, 0, 1, 3, 4, 7, 0, 1, 3, 5, 6, 7, 0, 1, 
	3, 5, 7, 0, 1, 3, 6, 7, 0, 1, 3, 7, 0, 1, 4, 5, 
	6, 7, 0, 1, 4, 5, 7, 0, 1, 4, 6, 7, 0, 1, 4, 7, 
	0, 1, 5, 6, 7, 0, 1, 5, 7, 0, 1, 6, 7, 0, 1, 7, 
	0, 2, 3, 4, 5, 6, 7, 0, 2, 3, 4, 5, 7, 0, 2, 3, 
	4, 6, 7, 0, 2, 3, 4, 7, 0, 2, 3, 5, 6, 7, 0, 2, 
	3, 5, 7, 0, 2, 3, 6, 7, 0, 2, 3, 7, 0, 2, 4, 5, 
	6, 7, 0, 2, 4, 5, 7, 0, 2, 4, 6, 7, 0, 2, 4, 7, 
	0, 2, 5, 6, 7, 0, 2, 5, 7, 0, 2, 6, 7, 0, 2, 7, 
	0, 3, 4, 5, 6, 7, 0, 3, 4, 5, 7, 0, 3, 4, 6, 7, 
	0, 3, 4, 7, 0, 3, 5, 6, 7, 0, 3, 5, 7, 0, 3, 6, 
	7, 0, 3, 7, 0, 4, 5, 6, 7, 0, 4, 5, 7, 0, 4, 6, 
	7, 0, 4, 7, 0, 5, 6, 7, 0, 5, 7, 0, 6, 7, 0, 7
};

#endif
