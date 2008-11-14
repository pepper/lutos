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

#include "../CoreBasicTypeDefine.h"
#include "../CoreBasicFunctionAndVariable/CoreBasicFunctionAndVariable.h"
#include "CoreScheduler.config"
#include "CoreSchedulerQueue.h"

#define CoreScheduler_EmptyQueueResetType	0
#define CoreScheduler_EmptyJobsResetType	1
//#define CoreScheduler_EmptyQueueResetType	2

//Can Mix Those Option
#define CoreScheduler_PauseAll				0x00
#define CoreScheduler_PauseCheckWork		0x02
#define CoreScheduler_PausePushWork			0x04

struct CoreScheduler_JobLookUpTableType{
	Data_1Byte start;
	Data_1Byte number;
};
typedef struct CoreScheduler_JobLookUpTableType CoreScheduler_JobLookUpTableType;

struct CoreScheduler_IndexLookUpTableType{
	Data_1Byte start;
	Data_1Byte number;
};
typedef struct CoreScheduler_IndexLookUpTableType CoreScheduler_IndexLookUpTableType;

typedef Data_1Byte	CoreScheduler_JobStatusID;

Data_1Byte	CoreScheduler_PauseState;

Data_1Byte	CoreScheduler_JobStatus;
Data_1Byte	CoreScheduler_JobTrigTimes[CoreScheduler_JobCapability];
Data_1Byte	CoreScheduler_JobAllowRetrigMask;

static const CoreScheduler_JobLookUpTableType	CoreScheduler_JobLookUpTable[] = {
	{0, 0}, {0, 1}, {1, 1}, {0, 2},
	{2, 1}, {4, 2}, {1, 2}, {0, 3},
	{3, 1}, {10, 2}, {8, 2}, {7, 3},
	{2, 2}, {4, 3}, {1, 3}, {0, 4}
};

static const CoreScheduler_JobID	CoreScheduler_JobPermutationAndCombination[] = {
	0, 1, 2, 3, 0, 2, 3, 0, 1, 3, 0, 3
};
/*
static const CoreScheduler_IndexLookUpTableType	CoreScheduler_IndexLookUpTableType[] = {

};*/

static const CoreScheduler_JobStatusID	CoreScheduler_IndexPermutationAndCombination[] = {
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

void (*CoreScheduler_JobExecuteFunction[4])(void);

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

#endif
