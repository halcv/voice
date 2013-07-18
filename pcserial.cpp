#include "pcserial.h"

#define SERIAL_MAX_SIZE 60

CPcSerial::CPcSerial(CTimer* pTimer,CAtp3011* pAtp3011)
{
    m_pTimer = pTimer;
    m_pAtp3011 = pAtp3011;
    vClearRecieveData();
}

void CPcSerial::vPcSerialProcess()
{
    if (m_pTimer->isWaitPcSerial() == false) {
        return;
    }
    
    if (isGetData() == true) {
        m_pAtp3011->vUpdateVoiceData(m_cRecieveData);
        m_pAtp3011->vSetAtp3011Request();
        vClearRecieveData();
    }
}

boolean CPcSerial::isGetData()
{
    boolean ret = false;
    int i = 0;
    while((Serial.available()) > 0) {
        m_cRecieveData[i] = Serial.read();
        i++;
    }
    if (i != 0) {
        ret = true;
    }
    return ret;
}

void CPcSerial::vClearRecieveData()
{
    for (int i = 0;i < RECIVE_DATA_SIZE;i++) {
        m_cRecieveData[i] = 0;
    }
}
