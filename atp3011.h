#ifndef _ATP3011_H_
#define _ATP3011_H_

#include "board.h"
#include "timer.h"
#include "playcheck.h"

#define VOICE_DATA_SIZE 127

class CAtp3011 {
  public:
    CAtp3011(CTimer* pTimer,CPlayCheck* pPlayCheck);
    void vSetAtp3011Request();
    void vAtp3011Process();
    void vUpdateVoiceData(char *pData);
    
  private:
    boolean isBusy();
    void vSendVoiceData();
    void vSetVoiceDefaultData();
    void vClearVoiceData();
    CTimer* m_pTimer;
    CPlayCheck* m_pPlayCheck;
    boolean m_isRequest;
    boolean m_isBusy;
    char m_cVoiceData[VOICE_DATA_SIZE];
};

#endif // _ATP3011_H_
