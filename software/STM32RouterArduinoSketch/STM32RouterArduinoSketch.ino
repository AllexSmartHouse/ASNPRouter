#include "PortHandler.h"
#include "SysMessageHandler.h"
#include "stm32f1xx_hal_iwdg.h"

const long long OVERFLOW_TIME = 2000;
const long long OVERFLOW_BLINK_TIME = 100;
const long long ERROR_TIME = 5000;
const long long ERROR_BLINK_TIME = 500;

long long overflowTime = 0;
long long errorTime = 0;

IWDG_HandleTypeDef hiwdg;
void startWatchDog(){
  hiwdg.Instance = IWDG;
  hiwdg.Init.Prescaler = IWDG_PRESCALER_32;
  hiwdg.Init.Reload    = 1000;
  
  HAL_IWDG_Init(&hiwdg);
}

void resetWatchDog(){
  HAL_IWDG_Refresh(&hiwdg);
}

const long DEFAULT_BAUD_RATE = 19200;

const int PORTS_COUNT = 3;
cPortHandler* ports[PORTS_COUNT];

cSysMessageHandler* sysMsgHandler;


void offLed(){
  digitalWrite(LED_BUILTIN,HIGH);
}

void onLed(){
  digitalWrite(LED_BUILTIN,LOW);
}

long long lastUpdate = 0;

void setup() {  
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN,LOW);

  Serial1.begin(DEFAULT_BAUD_RATE);
  Serial2.begin(DEFAULT_BAUD_RATE);
  Serial3.begin(DEFAULT_BAUD_RATE);  

  ports[0] = new cPortHandler(&Serial1);
  ports[1] = new cPortHandler(&Serial2);
  ports[2] = new cPortHandler(&Serial3);

  sysMsgHandler = new cSysMessageHandler(ports, PORTS_COUNT);

  delay(400);
  //request all devices with listener addresses
  for (int i = 0; i<PORTS_COUNT; ++i)
    ports[i]->queuePackage(PING_BROADCAST);

  startWatchDog();
  

  lastUpdate = millis();
}

bool processPort(int portIndex, long dt){
  if (ports[portIndex]->processData(dt)){    
    uint8_t* receivedPackage = ports[portIndex]->getReceivedPackage();
    sSysMessageInfo state =  sysMsgHandler->getMessageInfo(receivedPackage);

    if (state.needSysHandling){    
      sysMsgHandler->processSysMessage(receivedPackage, portIndex);
    }
    
    if (state.needDefaultHandling){
      for (int i = 0; i<PORTS_COUNT; ++i)
        if (i!=portIndex){
          ports[i]->queuePackage(receivedPackage);
        }
    }
    ports[portIndex]->clearReceivedPackage();
    return true;
  }
  return false;
}

void loop() {
  resetWatchDog();
  
  long long currentTime = millis();
  long dt = currentTime - lastUpdate;
  if (currentTime<lastUpdate)
    dt = currentTime;
  lastUpdate = currentTime;

  bool haveData = false;

  if (processPort(0, dt))
    haveData = true;
  if (processPort(1, dt))
    haveData = true;
  if (processPort(2, dt))
    haveData = true;

  for (int i = 0; i<PORTS_COUNT; ++i){
    if (ports[i]->isOverflow()){
      overflowTime = OVERFLOW_TIME;
    }
    if (ports[i]->isDataError() && errorTime<=0){
      errorTime = ERROR_TIME;
    }
  }
  if (sysMsgHandler->isDataError() && errorTime<=0){
    errorTime = ERROR_TIME;
  }
  sysMsgHandler->update(dt);

  bool canSleep = true;
  for (int i = 0; i<PORTS_COUNT; ++i){
    if (ports[i]->startSending())
      canSleep = false;
  }
  

  if (errorTime>0){    
    errorTime-=dt;
    if (errorTime>0){
      if (currentTime / ERROR_BLINK_TIME % 2 == 0){
        onLed();
      }
      else{
        offLed();  
      }
    }
    else{
      offLed();
    }    
  }
  else{
    if (overflowTime>0){
      overflowTime-=dt;
      if (overflowTime>0){
        if (currentTime / OVERFLOW_BLINK_TIME % 2 == 0){
          onLed();
        }
        else{
          offLed();  
        }
      }
      else{
        offLed();
      }
    }
    else{
      //NO ERROR
      //SHOW DATA ACTIVITY
      if (haveData){
        onLed();
      }
      else{
          offLed();
        if (canSleep)
          delay(10);
      }
    }
  }
}



