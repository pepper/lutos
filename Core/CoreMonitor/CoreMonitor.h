#ifndef COREMONITOR_H
#define	COREMONITOR_H

//Watching Variable List
//Static Data Update (Active)(User Set Frequance)
//Maybe a CoreMonitor_StartMonitore Function
//Remote Command Reading System Memory (Passive)
//

#include "../../SystemInformation.h"
#include "CoreMonitor.config"

struct CoreMonitor_WatchingVariableContainer{
	void						*point;
	CoreMonitor_DataLengthType	length;
};
typedef struct CoreMonitor_WatchingVariableContainer CoreMonitor_WatchingVariableContainer;

void	CoreMonitor_Init(void);
void	CoreMonitor_RegisterVariable(void *point, CoreMonitor_DataLengthType length);

#endif
