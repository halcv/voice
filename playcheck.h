#ifndef _PLAY_CHECK_H_
#define _PLAY_CHECK_H_

#include "board.h"
#include "timer.h"
#include "led.h"

class CPlayCheck {
  public:
    CPlayCheck(CTimer* pTimer,CLed* pLed);
    void vPlayCheckStateMachine();
    boolean isNowPlay();
    
  private:
    void vOffToOff();
    void vOffToOn();
    void vOnToOn();
    void vOnToOff();
    void vDriveLed(int iLedState);
    int iGetPlayState();
    int m_iLedDriveCounter;
    CTimer* m_pTimer;
    CLed* m_pLed;
    int m_iPlayState;
};

#endif // _PLAY_CHECK_H_
