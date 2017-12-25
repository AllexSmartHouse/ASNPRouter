#ifndef PORT_HANDLER_H
#define PORT_HANDLER_H
#include <Arduino.h>
#include "ProtocolListener.h"

const uint8_t START_CHAR_POS = 0;
const uint8_t ADDRESS_POS = 1;
const uint8_t LENGTH_POS = 2;
const uint8_t DATA_START_POS = 3;

const uint8_t SYS_MSG = 0;

const uint8_t BROADCAST_ADDRESS = 0x00;

const uint8_t START_CHAR_LOW  = 0x04;
const uint8_t START_CHAR_HIGH = 0x05;
                                 //HIGH PRIORITY.   ALL ADDRESSES,    2 BYTE DATA, SYSMSG   PING  CHECKSUM
const uint8_t PING_BROADCAST[6] = {START_CHAR_HIGH, BROADCAST_ADDRESS,0x02,        0x00,    0x00, START_CHAR_HIGH +BROADCAST_ADDRESS +0x02 +0x00 +0x00};


class cPortHandler{
  public:
    static const long SEND_BUFFER_SIZE = 2048;
    static const long HALF_SEND_BUFFER_SIZE = SEND_BUFFER_SIZE / 2;
  
    static const long PACKAGE_SERVICE_DATA_SIZE = 1+1+1+1; //PACKAGE_START_CHAR + ADDRESS + DATA_SIZE + CHECKSUM
    static const long MAX_PACKAGE_DATA_SIZE = 255;
    static const long PACKAGE_BUFFER_SIZE = MAX_PACKAGE_DATA_SIZE + PACKAGE_SERVICE_DATA_SIZE;

    enum eWaitState{
      WAIT_START,
      WAIT_ADDRESS,
      WAIT_LENGTH,
      WAIT_CHECKSUM
    };

    void receive(uint8_t data, bool clear);
  private:
    uint8_t*        m_SendBuffer;
    int             m_SendBufferSize;

    uint8_t*        m_ReceiveBuffer;
    int             m_ReceiveBufferSize;
    uint8_t         m_Checksum;
    eWaitState      m_ReceiverState;

    SerialUART*     m_Stream;
    cProtocolListenersList m_ListenersList;

    bool            m_Overflow;
    bool            m_DataError;

    long            m_TimeFromLastData;
  public:
    cPortHandler(SerialUART* serial);

    ~cPortHandler(){
      delete [] m_SendBuffer;
      delete [] m_ReceiveBuffer;
    }
    
    void queuePackage(const uint8_t* data);
    
    bool startSending();

    bool processData(long dt);
    
    uint8_t* getReceivedPackage(){
      return m_ReceiveBuffer;
    }
    void clearReceivedPackage(){
      m_ReceiveBufferSize = 0;
    }

    void setAddressEnable(uint8_t address){
      m_ListenersList.setAddressEnable(address);
    }

    bool isOverflow(){return m_Overflow;}
    bool isDataError(){return m_DataError;}
};

#endif

