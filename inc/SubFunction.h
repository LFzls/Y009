#ifndef   _SUBFUNCTION_H
#define   _SUBFUNCTION_H
/*----------------------------------------------*/
#include "Global.h"


/*----------------------------------------------*/
extern void IniMainPowerOn(void);
extern void MainPoweronFunction(void);

extern void IniMainStandby(void);
extern void MainStandbyFunction(void);
extern void CheckLoadState(void);
extern void CheckBatPercent(void);
extern void IniMainSleep(void);
extern void IniWarningMode(void);
extern void MainWarningFunction(void);


extern void EnterSleep(void); 
extern void IniMainKeyScreenOn(void);
extern void MainKeyScreenOn(void);

extern	void CalOilPercent(void);
extern	void CalOilLevel(void);

/*----------------------------------------------*/
#endif

