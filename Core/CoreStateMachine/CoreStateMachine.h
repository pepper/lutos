#ifndef CORESTATEMACHINE_H
#define	CORESTATEMACHINE_H

#include "../CoreScheduler/CoreScheduler.h"
#include "CoreStateMachine.config"

typedef	Data_1Byte Statemachine_StateMachineID;
typedef	Data_1Byte Statemachine_StateID;

struct StateMachine_StateMachine{
	Data_Boolean						runState;
	StateMachine_StateMachineRouter*	entry;
	StateMachine_StateMachineRouter*	current;
};

struct StateMachine_StateMachineRouter{
	StateMachine_StateID	workJob;
	Data_1Byte				(*selector)(void);				
};

struct StateMachine_State{
	CoreScheduler_JobID		begin;
	CoreScheduler_JobID		run;
	CoreScheduler_JobID		end;
	Data_Boolean			(*condition)(void);
	CoreTimer_Timer			timer;
};

StateMachine_StateMachineRouter StateMachine_StateMachineRouterContainer[StateMachine_StateMachineRouterQuantity];

Statemachine_StateMachineID		StateMachine_CreateStateMachine(Statemachine_StateMachineID id);
Data_Boolean					StateMachine_StateTrig(Statemachine_StateID);


#endif
