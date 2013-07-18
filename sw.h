#ifndef _SW_H_
#define _SW_H_

#include "board.h"
#include "led.h"
#include "timer.h"
#include "atp3011.h"

typedef enum {
    SW_NAME_VOICE,
    SW_NAME_MAX
} E_SW_NAME;

typedef struct {
    int iOldState;
    int iLongOnCounter;
} T_SW_STATUS;

class CSw {
  public:
    void vSwitchStateMachine();
    CSw(CTimer* pTimer,CAtp3011* pAtp3011);
    
  private:
    void vOffToOff(int iSwName);
    void vOffToOn(int iSwName);
    void vOnToOn(int iSwName);
    void vOnToOff(int iSwName);
    void vOnToLongOn(int iSwName);
    void vLongOnToLongOn(int iSwName);
    void vLongOnToOff(int iSwName);
    void vOn(int iSwName);
    void vLongOn(int iSwName);
    void vOff(int iSwName);
    int iGetPort(int iSwName);
    CTimer* m_pTimer;
    CAtp3011* m_pAtp3011;
    T_SW_STATUS m_tSwStatus[SW_NAME_MAX];
    int m_iLongOnCounter;
};

#endif // _SW_H_
