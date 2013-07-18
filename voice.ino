#include <Wire.h>
#include <Metro.h>
#include <timer.h>
#include <LiquidCrystal.h>
#include "startup.h"
#include "led.h"
#include "sw.h"
#include "atp3011.h"
#include "playcheck.h"
#include "pcserial.h"

static CTimer* g_pTimer;
static CLed* g_pLed;
static CStartup* g_pStartup;
static CSw* g_pSw;
static CAtp3011* g_pAtp3011;
static CPlayCheck* g_pPlayCheck;
static CPcSerial* g_pPcSerial;
static void vInitPort();
static void vCreateInstance();
static void vInitLcd();
static LiquidCrystal g_lcd(12, 11, 5, 4, 3, 2);

void setup()
{
    vInitPort();
    vCreateInstance();
    vInitLcd();
    Serial.begin(115200);
}

void loop()
{
    g_pTimer->vLoop();
    g_pStartup->vStartupProcess();
    g_pSw->vSwitchStateMachine();
    g_pLed->vLedProcess();
    g_pPlayCheck->vPlayCheckStateMachine();
    g_pAtp3011->vAtp3011Process();
    g_pPcSerial->vPcSerialProcess();
}

static void vInitPort()
{
    pinMode(POWER_LED_PORT,OUTPUT);
    digitalWrite(POWER_LED_PORT,LOW);
    pinMode(VOICE_SWITCH_PORT,INPUT);
    pinMode(PLAY_STATE_LED_PORT,OUTPUT);
    digitalWrite(PLAY_STATE_LED_PORT,LOW);
    pinMode(PLAY_STATE_PORT,INPUT);
}

static void vCreateInstance()
{
    g_pTimer = new CTimer();
    g_pLed = new CLed();
    g_pStartup = new CStartup(g_pTimer,g_pLed);
    g_pPlayCheck = new CPlayCheck(g_pTimer,g_pLed);
    g_pAtp3011 = new CAtp3011(g_pTimer,g_pPlayCheck);
    g_pSw = new CSw(g_pTimer,g_pAtp3011);
    g_pPcSerial = new CPcSerial(g_pTimer,g_pAtp3011);
}

static void vInitLcd()
{
    g_lcd.begin(16,2);
    g_lcd.setCursor(0,0);
    g_lcd.print("VOICE");
    g_lcd.setCursor(0,1);
    g_lcd.print("ATP3011F4-PU");
}
