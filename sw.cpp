#include "sw.h"

#define LONG_ON_COUNTER_MAX 100

typedef enum {
    SW_STATE_OFF,
    SW_STATE_ON,
    SW_STATE_LONG_ON
} E_SWITCH_STATE;

CSw::CSw(CTimer* pTimer,CAtp3011* pAtp3011)
{
    m_pTimer = pTimer;
     m_pAtp3011 = pAtp3011;
    m_iLongOnCounter = 0;
    for (int i = 0;i < SW_NAME_MAX;i++) {
        m_tSwStatus[i].iOldState = SW_STATE_OFF;
        m_tSwStatus[i].iLongOnCounter = 0;
    }
}

void CSw::vSwitchStateMachine()
{
    if (m_pTimer->isWaitSwitch() == false) {
        return;
    }
    

    for (int i = 0;i < SW_NAME_MAX;i++) {
        int iNowState = digitalRead(iGetPort(i));

        switch(m_tSwStatus[i].iOldState) {
        case SW_STATE_OFF:
            if (iNowState == HIGH) {
                vOffToOff(i);
            } else {
                vOffToOn(i);
            }
            break;
        case SW_STATE_ON:
            if (iNowState == HIGH) {
                vOnToOff(i);
            } else {
                vOnToOn(i);
            }
            break;
        case SW_STATE_LONG_ON:
            if (iNowState == HIGH) {
                vLongOnToOff(i);
            } else {
                vLongOnToLongOn(i);
            }
            break;
        }
    }
}

int CSw::iGetPort(int iSwName)
{
    int iPort = VOICE_SWITCH_PORT;
    switch(iSwName) {
    case SW_NAME_VOICE:
        iPort = VOICE_SWITCH_PORT;
        break;
    }
    
    return iPort;
}

void CSw::vOffToOff(int iSwName)
{
    m_tSwStatus[iSwName].iOldState = SW_STATE_OFF;
    m_tSwStatus[iSwName].iLongOnCounter = 0;
}

void CSw::vOffToOn(int iSwName)
{
    m_tSwStatus[iSwName].iOldState = SW_STATE_ON;
    m_tSwStatus[iSwName].iLongOnCounter = 0;
    vOn(iSwName);
}

void CSw::vOnToOff(int iSwName)
{
    m_tSwStatus[iSwName].iOldState = SW_STATE_OFF;
    m_tSwStatus[iSwName].iLongOnCounter = 0;
    vOff(iSwName);
}

void CSw::vOnToOn(int iSwName)
{
    m_tSwStatus[iSwName].iOldState = SW_STATE_ON;
    m_tSwStatus[iSwName].iLongOnCounter++;
    if (m_tSwStatus[iSwName].iLongOnCounter >= LONG_ON_COUNTER_MAX) {
        vOnToLongOn(iSwName);
    }
}

void CSw::vOnToLongOn(int iSwName)
{
    m_tSwStatus[iSwName].iOldState = SW_STATE_LONG_ON;
    m_tSwStatus[iSwName].iLongOnCounter = 0;
}

void CSw::vLongOnToLongOn(int iSwName)
{
    m_tSwStatus[iSwName].iOldState = SW_STATE_LONG_ON;
    m_tSwStatus[iSwName].iLongOnCounter = 0;
    vLongOn(iSwName);
}

void CSw::vLongOnToOff(int iSwName)
{
    m_tSwStatus[iSwName].iOldState = SW_STATE_OFF;
    m_tSwStatus[iSwName].iLongOnCounter = 0;
    vOff(iSwName);
}

void CSw::vOn(int iSwName)
{
    switch(iSwName) {
    case SW_NAME_VOICE:
        m_pAtp3011->vSetAtp3011Request();
        break;
    }
}

void CSw::vLongOn(int iSwName)
{
    switch(iSwName) {
    case SW_NAME_VOICE:
        break;
    }
}

void CSw::vOff(int iSwName)
{
    switch(iSwName) {
    case SW_NAME_VOICE:
        break;
    }
}

