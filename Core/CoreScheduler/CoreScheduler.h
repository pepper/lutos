/**
 * @file	共用排程模組的標頭檔
 * @brief	提供使用者高自由度的工作排程功能，讓使用者可以利用本模組內含的排程系統以及事件處發機制，進行程式流程控管，並可進行『不同觸發來源』的集體管理。
 * @author	嚴孝頤（pepper.yen@gmail.com）
 * @version	0.0.1
 * @date	2008-11-14
 */

#ifndef CORESCHEDULER_H
#define CORESCHEDULER_H

#include <avr/interrupt.h>
#include <avr/pgmspace.h>

#include "../CoreBasicTypeDefine.h"
#include "../CoreBasicFunctionAndVariable/CoreBasicFunctionAndVariable.h"
#include "../CoreMemory/CoreMemory.h"
#include "CoreScheduler.config"
#include "CoreSchedulerQueue.h"


#include "Driver/Uart/Uart.h"
#include <util/delay.h>

//#define CoreScheduler_EmptyQueueResetType	0
//#define CoreScheduler_EmptyJobsResetType	1
//#define CoreScheduler_EmptyQueueResetType	2

//Can Mix Those Option
//#define CoreScheduler_PauseAll				0x00
//#define CoreScheduler_PauseCheckWork			0x02
//#define CoreScheduler_PausePushWork			0x04

#if CoreScheduler_Level > 1
static const Data_2Byte	CoreScheduler_JobLookUpTableNodeStart[] PROGMEM = {
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

static const Data_1Byte	CoreScheduler_JobLookUpTableNodeNumber[] PROGMEM = {
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

static const CoreScheduler_JobID	CoreScheduler_JobPermutationAndCombinationNode[] PROGMEM = {
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

static const Data_1Byte	CoreScheduler_JobLookUpTableLeafStart[] PROGMEM = {
	0, 0, 1, 0, 2, 4, 1, 0, 3, 10, 8, 7, 2, 4, 1, 0
};

static const Data_1Byte	CoreScheduler_JobLookUpTableLeafNumber[] PROGMEM = {
	0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4
};

static const CoreScheduler_JobID	CoreScheduler_JobPermutationAndCombinationLeaf[] PROGMEM = {
	0, 1, 2, 3, 0, 2, 3, 0, 1, 3, 0, 3
};

/** @struct CoreScheduler_JobTreeNodeType 
 *  定義樹狀工作狀態表的中間節點，節點子元素可以指向『節點』或『末枝節點』。
 */ 
struct CoreScheduler_JobTreeNodeType {
	Data_1Byte								childStatus[2];	///< 代表此 Node 底下的 Child Node 是否有工作被觸發
	//struct CoreScheduler_JobTreeNodeType	*parent;		///< 上層元素（觸發事件時回追設定用）
	//void									*child[4];		///< 子元素（可以指向『節點』或『末枝節點』，由執行期定義）
};
typedef struct CoreScheduler_JobTreeNodeType CoreScheduler_JobTreeNodeType;

/** @struct CoreScheduler_JobTreeLeafType 
 *  定義樹狀工作狀態表的末枝節點，單一節點可指向4個工作。
 */ 
struct CoreScheduler_JobTreeLeafType {
	//struct CoreScheduler_JobTreeNodeType	*parent;							///< 上層元素（觸發事件時回追設定用）
	Data_1Byte								jobStatus[2];						///< 代表此節點指向的四個工作的觸發狀態（Most 4-Bit 代表重複觸發、Last 4-Bit 代表觸發狀態）
#if defined(CoreScheduler_CheckRetrig)
	Data_1Byte								jobAllowRetrigMask;					///< 設定指向的工作是否允許重複觸發（預設為允許觸發）
	Data_1Byte								jobTrigTimes[4][2];					///< 距上次檢查後被觸發的次數，若允許重複觸發就會 Push N 次至 Job Queue 中
#endif
	void									(*jobExecuteFunction[4])(void);		///< 工作觸發後要執行之函數的指標（無傳參）
};
typedef struct CoreScheduler_JobTreeLeafType CoreScheduler_JobTreeLeafType;

//CoreScheduler_JobTreeNodeType	*CoreScheduler_JobTreeNode[CoreScheduler_Level - 1];

///包含八個子群組的中間節點
#if CoreScheduler_Level > 1
CoreScheduler_JobTreeNodeType	CoreScheduler_JobTreeNodeLevel1;
#endif
#if CoreScheduler_Level > 2
CoreScheduler_JobTreeNodeType	CoreScheduler_JobTreeNodeLevel2[8];
#endif

///包含四個工作的末枝節點，共會有 4 * 8^(Level-1) 個
CoreScheduler_JobTreeLeafType	CoreScheduler_JobTreeLeaf[CoreScheduler_JobTreeLeafQuantity];

///代表外部模組目前可以改變的狀態旗標
Data_1Byte	CoreScheduler_CurrentCollectBuffer;

//Data_1Byte	CoreScheduler_PauseState;

void	CoreScheduler_Init(void);
void	CoreScheduler_RegisterJob(CoreScheduler_JobID id, void (*function)(void));
void	CoreScheduler_NeedToWork(CoreScheduler_JobID id);

#if defined(CoreScheduler_CheckRetrig)
void	CoreScheduler_AllowRetrigger(CoreScheduler_JobID id, Data_Boolean enable);
//Default is all allow Retrigger
#endif

void	CoreScheduler_RunLoop(void);
void	CoreScheduler_Execute(void);
void	CoreScheduler_CheckAndPush(void);
void	CoreScheduler_Pause(Data_1Byte type);
void	CoreScheduler_Reset(Data_1Byte type);
void	CoreScheduler_NothingToDo(void);
#endif
