#ifndef _TIMER_H_
#define _TIMER_H_

#include "board.h"
#include <Metro.h>

class CTimer {
  public:
    CTimer();
    void vLoop();
    void vClearStartupCounter();
    boolean isWaitStartup();
    boolean isWaitSwitch();
    boolean isWaitVoice();
    boolean isWaitPlayCheck();
    boolean isWaitPcSerial();
    
  private:
    void vTimer10msInterrupt();
    void vStartupCounterUp();
    void vSwitchCounterUp();
    void vVoiceCounterUp();
    void vPlayCheckCounterUp();
    void vPcSerialCounterUp();
    
    Metro* m_pMetro;
    int m_iStartupCounter;
    int m_iSwitchCounter;
    int m_iVoiceCounter;
    int m_iPlayCheckCounter;
    int m_iPcSerialCounter;
};

#endif // _TIMER_H_
