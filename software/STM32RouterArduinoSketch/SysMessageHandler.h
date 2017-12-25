#ifndef SYS_MESSAGE_HANDLER_H
#define SYS_MESSAGE_HANDLER_H
#include <Arduino.h>
#include "ProtocolListener.h"
#include "PortHandler.h"



const uint8_t SYSMSG_TRACE_START  = 0x10;
const uint8_t SYSMSG_TRACE_STEP   = 0x11;
const uint8_t SYSMSG_TRACE_STATE  = 0x12;

const uint8_t SYSMSG_PONG = 0x01;

const long TRACE_TIMEOUT = 500;

struct sSysMessageInfo{
  bool needSysHandling;
  bool needDefaultHandling;
};

class cSysMessageHandler{
private:
  cPortHandler**    m_Ports;
  int               m_PortsCount;

  int               m_CurrentTracePortPortsCount;
  int               m_CurrentTracePort;  
  int               m_MasterTracePort;
  int               m_TraceTimeoutTimer;
  bool              m_WaitTraceResponse;
  
  bool              m_DataError;
  void processTraceStep(uint8_t* package, int portIndex);
  void processTraceState(uint8_t* package, int portIndex);
  void toNextTracePort();
  void sendTraceError();
public:
  cSysMessageHandler(cPortHandler** ports, int portsCount);

  sSysMessageInfo getMessageInfo(uint8_t* package);

  void processSysMessage(uint8_t* package, int portIndex);

  void update(long dt);

  bool isDataError(){return m_DataError;}

  
};

#endif

