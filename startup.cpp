#include "startup.h"

#define LOOP_COUNTER_MAX 10

CStartup::CStartup(CTimer* pTimer,CLed* pLed)
{
    m_pLed = pLed;
    m_pTimer = pTimer;
    m_iLoopCount = 0;
    m_isCompleate = false;
}

void CStartup::vStartupProcess()
{
    if (m_isCompleate == true) {
        return;
    }
    if (m_pTimer->isWaitStartup() == false) {
        return;
    }
    
    m_pLed->vSetLedRequest(LED_NAME_POWER,LED_STATE_BLINK);
    m_iLoopCount++;
    if (m_iLoopCount >= LOOP_COUNTER_MAX) {
        m_isCompleate = true;
        m_pLed->vSetLedRequest(LED_NAME_POWER,LED_STATE_ON);
    }
}
