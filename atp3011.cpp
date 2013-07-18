#include <Wire.h>
#include "atp3011.h"

#define I2C_ADDRESS 0x2E
#define I2C_BUFFER_SIZE 32

CAtp3011::CAtp3011(CTimer* pTimer,CPlayCheck* pPlayCheck)
{
    m_pTimer = pTimer;
    m_pPlayCheck = pPlayCheck;
    m_isRequest = false;
    vSetVoiceDefaultData();
    Wire.begin();
}

void CAtp3011::vAtp3011Process()
{
    if (m_pTimer->isWaitVoice() == false) {
        return;
    }

    if (m_isRequest == false) {
        return;
    }

    if(isBusy() == true) {
        return;
    }

    vSendVoiceData();
    m_isRequest = false;
}

void CAtp3011::vSetAtp3011Request()
{
    if (m_isRequest == false && m_pPlayCheck->isNowPlay() == false) {
        m_isRequest = true;
    }
}

boolean CAtp3011::isBusy()
{
    boolean ret = false;
    char cRecieve = 'h';
    Wire.beginTransmission(I2C_ADDRESS);
    Wire.write(0xff);
    Wire.endTransmission();
    Wire.requestFrom(I2C_ADDRESS,1);
    while (Wire.available()) {
        cRecieve = Wire.read();
    }
    if (cRecieve == '*' || cRecieve == 'h') {
        ret = true;
    }
    return ret;
}

void CAtp3011::vSendVoiceData()
{
    char *pData = m_cVoiceData;
    Wire.beginTransmission(I2C_ADDRESS);
    int i = 0;
    while(1) {
        if (i != 0 && i % (I2C_BUFFER_SIZE - 1) == 0) {
            Wire.endTransmission();
            Wire.beginTransmission(I2C_ADDRESS);
        }
        Wire.write(*(pData + i));
        if (*(pData + i) == '\r') {
            break;
        }
        i++;
    }
    Wire.endTransmission();
}

void CAtp3011::vUpdateVoiceData(char *pData)
{
    vClearVoiceData();
    
    int i = 0;
    while(1) {
        m_cVoiceData[i] = *(pData + i);
        if (m_cVoiceData[i] == '\r') {
            break;
        }
        i++;
    }
}

void CAtp3011::vSetVoiceDefaultData()
{
    m_cVoiceData[0]  = 'k';
    m_cVoiceData[1]  = 'o';
    m_cVoiceData[2]  = 'n';
    m_cVoiceData[3]  = 'n';
    m_cVoiceData[4]  = 'n';
    m_cVoiceData[5]  = 'i';
    m_cVoiceData[6]  = 't';
    m_cVoiceData[7]  = 'i';
    m_cVoiceData[8]  = 'w';
    m_cVoiceData[9]  = 'a';
    m_cVoiceData[10] = '\r';
}

void CAtp3011::vClearVoiceData()
{
    for (int i = 0;i < VOICE_DATA_SIZE;i++) {
        m_cVoiceData[i] = 0;
    }
}

