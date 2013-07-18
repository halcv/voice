#include "timer.h"

#define METRO_INTERVAL        10
#define STARTUP_COUNTER_MAX    4
#define SWITCH_COUNTER_MAX     2
#define VOICE_COUNTER_MAX      1
#define PLAY_CHECK_COUNTER_MAX 1
#define PC_SERIAL_COUNTER_MAX 1

CTimer::CTimer()
{
    m_pMetro = new Metro(METRO_INTERVAL);
    m_iStartupCounter   = 0;
    m_iSwitchCounter    = 0;
    m_iVoiceCounter     = 0;
    m_iPlayCheckCounter = 0;
    m_iPcSerialCounter  = 0;
}

void CTimer::vLoop()
{
    if (m_pMetro->check()) {
        vTimer10msInterrupt();
    }
}

void CTimer::vTimer10msInterrupt()
{
    vStartupCounterUp();
    vSwitchCounterUp();
    vVoiceCounterUp();
    vPlayCheckCounterUp();
    vPcSerialCounterUp();
}

void CTimer::vStartupCounterUp()
{
    if (m_iStartupCounter < STARTUP_COUNTER_MAX) {
        m_iStartupCounter++;
    }
}

boolean CTimer::isWaitStartup()
{
    boolean ret = false;
    if (m_iStartupCounter >= STARTUP_COUNTER_MAX) {
        ret = true;
        m_iStartupCounter = 0;
    }

    return ret;
}

void CTimer::vSwitchCounterUp()
{
    if (m_iSwitchCounter < SWITCH_COUNTER_MAX) {
        m_iSwitchCounter++;
    }
}

boolean CTimer::isWaitSwitch()
{
    boolean ret = false;
    if (m_iSwitchCounter >= SWITCH_COUNTER_MAX) {
        ret = true;
        m_iSwitchCounter = 0;
    }

    return ret;
}

void CTimer::vVoiceCounterUp()
{
    if (m_iVoiceCounter < VOICE_COUNTER_MAX) {
        m_iVoiceCounter++;
    }
}

boolean CTimer::isWaitVoice()
{
    boolean ret = false;
    if (m_iVoiceCounter >= VOICE_COUNTER_MAX) {
        ret = true;
        m_iVoiceCounter = 0;
    }

    return ret;
}

void CTimer::vPlayCheckCounterUp()
{
    if (m_iPlayCheckCounter < PLAY_CHECK_COUNTER_MAX) {
        m_iPlayCheckCounter++;
    }
}

boolean CTimer::isWaitPlayCheck()
{
    boolean ret = false;
    if (m_iPlayCheckCounter >= PLAY_CHECK_COUNTER_MAX) {
        ret = true;
        m_iPlayCheckCounter = 0;
    }

    return ret;
}

void CTimer::vPcSerialCounterUp()
{
    if (m_iPcSerialCounter < PC_SERIAL_COUNTER_MAX) {
        m_iPcSerialCounter++;
    }
}

boolean CTimer::isWaitPcSerial()
{
    boolean ret = false;
    if (m_iPcSerialCounter >= PC_SERIAL_COUNTER_MAX) {
        ret = true;
        m_iPcSerialCounter = 0;
    }

    return ret;
}
