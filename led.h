#ifndef _LED_H_
#define _LED_H_

#include "board.h"

typedef enum {
    LED_STATE_OFF,
    LED_STATE_ON,
    LED_STATE_BLINK,
    LED_STATE_MAX
} E_LED_STATE;

typedef enum {
    LED_NAME_POWER,
    LED_NAME_PLAY_STATE,
    LED_NAME_MAX
} E_LED_NAME;

typedef struct {
    boolean isRequest;
    int state;
} T_LED_STATUS;

class CLed {
  public:
    CLed();
    void vLedProcess();
    void vSetLedRequest(int iLedName,int iState);
  private:
    void vPlayLed();
    void vOn(int iPort);
    void vOff(int iPort);
    void vBlink(int iPort);
    int iGetPort(int iLedName);
    boolean isLedRequest();
    T_LED_STATUS m_tLedStatus[LED_NAME_MAX];
    boolean m_isLedRequest;
};

#endif // _LED_H_
