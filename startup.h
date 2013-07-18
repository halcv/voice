#ifndef _STARTUP_H_
#define _STARTUP_H_

#include "board.h"
#include "led.h"
#include "timer.h"

class CStartup {
  public:
    CStartup(CTimer* pTimer,CLed* pLed);
    void vStartupProcess();

  private:
    int m_iLoopCount;
    CLed* m_pLed;
    CTimer* m_pTimer;
    boolean m_isCompleate;
};

#endif // _STARTUP_H_
