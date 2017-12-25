#include "SysMessageHandler.h"

const uint8_t TRACE_ERROR_BROADCAST[6] = {START_CHAR_HIGH, BROADCAST_ADDRESS,0x02,        0x00,    SYSMSG_TRACE_STATE, START_CHAR_HIGH +BROADCAST_ADDRESS +0x02 +0x00 +SYSMSG_TRACE_STATE};

cSysMessageHandler::cSysMessageHandler(cPortHandler** ports, int portsCount){
  m_Ports = ports;
  m_PortsCount = portsCount;
  m_CurrentTracePort = -1;
  m_MasterTracePort = 0;
  m_WaitTraceResponse = false;
  m_DataError = false;
}

sSysMessageInfo cSysMessageHandler::getMessageInfo(uint8_t* package){
  sSysMessageInfo state;
  state.needSysHandling = false;
  state.needDefaultHandling = true;
  if (package[START_CHAR_POS]==START_CHAR_HIGH && package[ADDRESS_POS]==BROADCAST_ADDRESS && package[LENGTH_POS]>=2){
    if (package[DATA_START_POS + 0] == SYS_MSG){
      state.needSysHandling = true;
      if (package[DATA_START_POS + 1]==SYSMSG_TRACE_STEP || (package[DATA_START_POS + 1]==SYSMSG_TRACE_STATE && package[LENGTH_POS]>2))
        state.needDefaultHandling = false;
    }
  }
  return state;
}

void cSysMessageHandler::processSysMessage(uint8_t* package, int portIndex){  
  if (package[ADDRESS_POS]==ADDRESS_BROADCAST){
    int dataLength = package[LENGTH_POS];
    if (dataLength>=2){
      if (package[DATA_START_POS+0]==SYS_MSG){
        switch (package[DATA_START_POS+1]){
          case SYSMSG_PONG:{
            int addressesCount = package[DATA_START_POS+2];
            if (dataLength==1+1+1+addressesCount){
              for (uint8_t i = 0; i<addressesCount; i++)
                m_Ports[portIndex]->setAddressEnable(package[DATA_START_POS+1+1+1+i]);
            }
            else{
              //INCORRECT SIZE
              m_DataError = true;
            }
          }; break;
          case SYSMSG_TRACE_START:{
            m_DataError = true;
            m_WaitTraceResponse= false;
            m_MasterTracePort = portIndex;
            m_CurrentTracePort = -1;            
            m_CurrentTracePortPortsCount = 0;
            if (m_CurrentTracePort==m_MasterTracePort)
              m_CurrentTracePort = 1;
          };break;
          case SYSMSG_TRACE_STEP:{
            processTraceStep(package, portIndex);
          };break;
          case SYSMSG_TRACE_STATE:{
            processTraceState(package, portIndex);
          };break;
          
        }
        
      }
    }       
  }
}

void cSysMessageHandler::toNextTracePort(){  
  m_CurrentTracePort = m_CurrentTracePort + 1;
  if (m_CurrentTracePort==m_MasterTracePort){
    toNextTracePort();
    return;
  }
  m_CurrentTracePortPortsCount = 0;
}

void cSysMessageHandler::processTraceStep(uint8_t* package, int portIndex){
  if (portIndex!=m_MasterTracePort){
    sendTraceError();
    return;
  }

  if (m_CurrentTracePort==-1){
    toNextTracePort();

    //send TRACE_STATE
    uint8_t buf[9];
    buf[0] = START_CHAR_HIGH;
    buf[1] = BROADCAST_ADDRESS;
    buf[2] = 5;
    
    buf[3] = SYS_MSG;
    buf[4] = SYSMSG_TRACE_STATE;
    
    buf[5] = 0x00; //router has not own address
    buf[6] = m_PortsCount;
    buf[7] = m_MasterTracePort;

    buf[8] = 0;
    for (int i = 0; i<8; ++i)
      buf[8] = buf[8] + buf[i];
    m_Ports[m_MasterTracePort]->queuePackage(buf);
  }
  
  if (m_CurrentTracePort<0 || m_CurrentTracePort==m_MasterTracePort || m_CurrentTracePort>=m_PortsCount){
    sendTraceError();
    return;
  }

  m_TraceTimeoutTimer = 0;
  m_WaitTraceResponse = true;
  m_Ports[m_CurrentTracePort]->queuePackage(package);
}

void cSysMessageHandler::processTraceState(uint8_t* package, int portIndex){
  if (portIndex!=m_CurrentTracePort){
    sendTraceError();
    return;
  }
  
  m_CurrentTracePortPortsCount--; //RESPONSE RECEIVED - remove one pended port
  int dataLength = package[LENGTH_POS];
  if (dataLength==5){
    int portsCount = package[DATA_START_POS+3];
    int masterPort = package[DATA_START_POS+4];
    if (portsCount>masterPort){      
      m_Ports[m_MasterTracePort]->queuePackage(package);
      m_CurrentTracePortPortsCount+=portsCount-1;
      if (m_CurrentTracePortPortsCount<0)
        toNextTracePort();
    }
    else{
      sendTraceError();
    }
  }
  else{
    sendTraceError();
  }
}

void cSysMessageHandler::sendTraceError(){
  m_DataError = true;
  m_Ports[m_MasterTracePort]->queuePackage(TRACE_ERROR_BROADCAST);  
}

void cSysMessageHandler::update(long dt){
  m_DataError = false;

  if (!m_WaitTraceResponse)
    return;
    
  m_TraceTimeoutTimer += dt;
  if (m_TraceTimeoutTimer>TRACE_TIMEOUT){
    m_WaitTraceResponse = false;
    m_CurrentTracePortPortsCount --;
    if (m_CurrentTracePortPortsCount <0){
      toNextTracePort();
    }
  }
}


