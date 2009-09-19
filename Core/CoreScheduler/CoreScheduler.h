/**
 * @file	共用排程模組的標頭檔
 * @brief	提供使用者高自由度的工作排程功能，讓使用者可以利用本模組內含的排程系統以及事件處發機制，進行程式流程控管，並可進行『不同觸發來源』的集體管理。
 * @author	嚴孝頤（pepper.yen@gmail.com）
 * @version	0.0.1
 * @date	2008-11-14
 */

#ifndef CORESCHEDULER_H
#define CORESCHEDULER_H

#include "../../SystemInformation.h"
#include "../CoreBasicFunctionAndVariable/CoreBasicFunctionAndVariable.h"
#include "CoreScheduler.config"
#include "CoreSchedulerQueue.h"

#ifndef	CoreLookUpTable_Enable4BitLookUpTable
#	define	CoreLookUpTable_Enable4BitLookUpTable
#endif

#if CoreScheduler_Level > 1
#	ifndef	CoreLookUpTable_Enable8BitLookUpTable
#		define	CoreLookUpTable_Enable8BitLookUpTable
#	endif
#endif
#include "../CoreLookUpTable/CoreLookUpTable.h"

#define CoreScheduler_QueueResetType	1
#define CoreScheduler_JobsResetType		2

/** @struct CoreScheduler_JobTreeNodeType 
 *  定義樹狀工作狀態表的中間節點，節點子元素可以指向『節點』或『末枝節點』。
 */ 
struct CoreScheduler_JobTreeNodeType {
	Data_1Byte								childStatus[2];	///< 代表此 Node 底下的 Child Node 是否有工作被觸發
};
typedef struct CoreScheduler_JobTreeNodeType CoreScheduler_JobTreeNodeType;

/** @struct CoreScheduler_JobTreeLeafType 
 *  定義樹狀工作狀態表的末枝節點，單一節點可指向4個工作。
 */ 
struct CoreScheduler_JobTreeLeafType {
	Data_1Byte								jobStatus[2];						///< 代表此節點指向的四個工作的觸發狀態（Most 4-Bit 代表重複觸發、Last 4-Bit 代表觸發狀態）
#if defined(CoreScheduler_EnableCheckRetrig)
	Data_1Byte								jobAllowRetrigMask;					///< 設定指向的工作是否允許重複觸發（預設為允許觸發）
	Data_1Byte								jobTrigTimes[4][2];					///< 距上次檢查後被觸發的次數，若允許重複觸發就會 Push N 次至 Job Queue 中
#endif
	void									(*jobExecuteFunction[4])(void);		///< 工作觸發後要執行之函數的指標（無傳參）
};
typedef struct CoreScheduler_JobTreeLeafType CoreScheduler_JobTreeLeafType;

void	CoreScheduler_Init(void);
void	CoreScheduler_RegisterJob(CoreScheduler_JobID id, void (*function)(void));
void	CoreScheduler_NeedToWork(CoreScheduler_JobID id);

#if defined(CoreScheduler_EnableCheckRetrig)
void	CoreScheduler_AllowRetrigger(CoreScheduler_JobID id, Data_Boolean enable);
//Default is all allow Retrigger
#endif

void	CoreScheduler_RunLoop(void);
void	CoreScheduler_Execute(void);
void	CoreScheduler_CheckAndPush(void);

#if defined(CoreScheduler_EnablePauseExecuteJob)
void	CoreScheduler_PauseExecuteJob(Data_Boolean state);
#endif

#if defined(CoreScheduler_EnablePausePushJob)
void	CoreScheduler_PausePushJob(Data_Boolean state);
#endif

void	CoreScheduler_Reset(Data_1Byte type);
void	CoreScheduler_NothingToDo(void);

#endif
