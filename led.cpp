#include "led.h"

CLed::CLed()
{
    for (int i = 0;i < LED_NAME_MAX;i++) {
        m_tLedStatus[i].isRequest = false;
        m_tLedStatus[i].state = LED_STATE_OFF;
    }
    m_isLedRequest = false;
}

void CLed::vLedProcess()
{
    if (isLedRequest() == false) {
        return;
    }

    vPlayLed();

}

void CLed::vSetLedRequest(int iLedName,int iState)
{
    m_tLedStatus[iLedName].isRequest = true;
    m_tLedStatus[iLedName].state = iState;
    m_isLedRequest = true;
}

boolean CLed::isLedRequest()
{
    int iRet = m_isLedRequest;
    m_isLedRequest = false;
    return iRet;
}

void CLed::vPlayLed()
{
    for (int i;i < LED_NAME_MAX;i++) {
        if (m_tLedStatus[i].isRequest == true) {
            m_tLedStatus[i].isRequest = false;
            switch(m_tLedStatus[i].state) {
            case LED_STATE_OFF:
                vOff(iGetPort(i));
                break;
            case LED_STATE_ON:
                vOn(iGetPort(i));
                break;
            case LED_STATE_BLINK:
                vBlink(iGetPort(i));
                break;
            }
        }
    }
}

int CLed::iGetPort(int iLedName)
{
    int iPort = POWER_LED_PORT;
    switch(iLedName) {
    case LED_NAME_POWER:
        iPort = POWER_LED_PORT;
        break;
    case LED_NAME_PLAY_STATE:
        iPort = PLAY_STATE_LED_PORT;
        break;
    }

    return iPort;
}
void CLed::vBlink(int iPort)
{
    digitalWrite(iPort,!digitalRead(iPort));
}

void CLed::vOn(int iPort)
{
    digitalWrite(iPort,HIGH);
}

void CLed::vOff(int iPort)
{
    digitalWrite(iPort,LOW);
}
