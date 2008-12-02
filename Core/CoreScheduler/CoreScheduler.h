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

//#define CoreScheduler_EmptyQueueResetType	0
//#define CoreScheduler_EmptyJobsResetType	1
//#define CoreScheduler_EmptyQueueResetType	2

//Can Mix Those Option
//#define CoreScheduler_PauseAll				0x00
//#define CoreScheduler_PauseCheckWork		0x02
//#define CoreScheduler_PausePushWork			0x04

/** @struct CoreScheduler_JobLookUpTableType 
 *  定義查表 Index 型別
 */ 
/*struct CoreScheduler_JobLookUpTableType{
	Data_1Byte start;
	Data_1Byte number;
};
typedef struct CoreScheduler_JobLookUpTableType CoreScheduler_JobLookUpTableType;

static const CoreScheduler_JobLookUpTableType	CoreScheduler_JobLookUpTable[] = {
	{0, 0}, {0, 1}, {1, 1}, {0, 2},
	{2, 1}, {4, 2}, {1, 2}, {0, 3},
	{3, 1}, {10, 2}, {8, 2}, {7, 3},
	{2, 2}, {4, 3}, {1, 3}, {0, 4}
};*/

static const Data_2Byte	CoreScheduler_JobLookUpTableStart[] PROGMEM = {
	0, 0, 1, 0, 2, 4, 1, 0, 3, 10, 8, 7, 2, 4, 1, 0
};

static const Data_1Byte	CoreScheduler_JobLookUpTableNumber[] PROGMEM = {
	0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4
};

static const CoreScheduler_JobID	CoreScheduler_JobPermutationAndCombination[] PROGMEM = {
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

CoreScheduler_JobTreeNodeType	*CoreScheduler_JobTreeNode[CoreScheduler_Level - 1];

///包含四個工作的末枝節點，共會有 Level^4 個
CoreScheduler_JobTreeLeafType	CoreScheduler_JobTreeLeaf[CoreScheduler_JobTreeLeafQuantity];

///代表外部模組目前可以改變的狀態旗標
Data_1Byte	CoreScheduler_CurrentCollectBuffer;

//Data_1Byte	CoreScheduler_PauseState;

void	CoreScheduler_Init(void);
void	CoreScheduler_RegisterJob(CoreScheduler_JobID id, void (*function)(void));
void	CoreScheduler_NeedToWork(CoreScheduler_JobID id);
void	CoreScheduler_AllowRetrigger(CoreScheduler_JobID id, Data_Boolean enable);
//Default is all allow Retrigger
void	CoreScheduler_RunLoop(void);
void	CoreScheduler_Execute(void);
void	CoreScheduler_CheckAndPush(void);
void	CoreScheduler_Pause(Data_1Byte type);
void	CoreScheduler_Reset(Data_1Byte type);
void	CoreScheduler_NothingToDo(void);
#endif
