#include "playcheck.h"

#define LED_DRIVE_COUNTER_MAX 5

typedef enum {
    PLAY_STATE_OFF,
    PLAY_STATE_ON,
    PLAY_STATE_MAX
} E_PLAY_STATE;

CPlayCheck::CPlayCheck(CTimer* pTimer,CLed* pLed)
{
    m_pTimer = pTimer;
    m_pLed = pLed;
    m_iPlayState = PLAY_STATE_OFF;
    m_iLedDriveCounter = 0;
}

void CPlayCheck::vPlayCheckStateMachine()
{
    if (m_pTimer->isWaitPlayCheck() == false) {
        return;
    }

    int iState = iGetPlayState();
    switch(m_iPlayState) {
    case PLAY_STATE_OFF:
        if (iState == PLAY_STATE_OFF) {
            vOffToOff();
        } else {
            vOffToOn();
        }
        break;
    case PLAY_STATE_ON:
        if (iState == PLAY_STATE_OFF) {
            vOnToOff();
        } else {
            vOnToOn();
        }
        break;
    }
}
void CPlayCheck::vOffToOff()
{
    m_iPlayState = PLAY_STATE_OFF;
    m_iLedDriveCounter = 0;
}

void CPlayCheck::vOffToOn()
{
    m_iPlayState = PLAY_STATE_ON;
    m_iLedDriveCounter = 0;
    vDriveLed(LED_STATE_BLINK);
}

void CPlayCheck::vOnToOn()
{
    m_iPlayState = PLAY_STATE_ON;
    m_iLedDriveCounter++;
    if (m_iLedDriveCounter >= LED_DRIVE_COUNTER_MAX) {
        m_iLedDriveCounter = 0;
        vDriveLed(LED_STATE_BLINK);
    }
}

void CPlayCheck::vOnToOff()
{
    m_iPlayState = PLAY_STATE_OFF;
    m_iLedDriveCounter = 0;
    vDriveLed(LED_STATE_OFF);
}

boolean CPlayCheck::isNowPlay()
{
    boolean ret = false;
    if (m_iPlayState == PLAY_STATE_ON) {
        ret = true;
    }

    return ret;
}

int CPlayCheck::iGetPlayState()
{
    int iRet = PLAY_STATE_OFF;
    if (digitalRead(PLAY_STATE_PORT) == LOW) {
        iRet = PLAY_STATE_ON;
    }

    return iRet;
}

void CPlayCheck::vDriveLed(int iLedState)
{
    m_pLed->vSetLedRequest(LED_NAME_PLAY_STATE,iLedState);
}
