#ifndef _PCSERIAL_H_
#define _PCSERIAL_H_

#include "board.h"
#include "timer.h"
#include "atp3011.h"

#define RECIVE_DATA_SIZE 127

class CPcSerial {
  public:
    CPcSerial(CTimer *pTimer,CAtp3011* pAtp3011);
    void vPcSerialProcess();
    
  private:
    void vClearRecieveData();
    boolean isGetData();
    CTimer* m_pTimer;
    CAtp3011* m_pAtp3011;
    char m_cRecieveData[RECIVE_DATA_SIZE];
};

#endif // _PC_SERIAL_H_
