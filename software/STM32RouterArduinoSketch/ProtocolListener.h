#ifndef PROTOCOL_LISTENER_H
#define PROTOCOL_LISTENER_H
#include <Arduino.h>

const uint8_t ADDRESS_BROADCAST         = 0;

class cProtocolListenersList{
  private:
    bool*        m_Addresses;
  public:
    cProtocolListenersList(){
      m_Addresses = new bool[256];
      m_Addresses[ADDRESS_BROADCAST] = true;
      for (int i = ADDRESS_BROADCAST+1; i<256; i++)
        m_Addresses[i] = 0;
    }

    ~cProtocolListenersList(){
      delete [] m_Addresses;
    }

    bool isAddressEnable(uint8_t address){
      return m_Addresses[address];
    }

    void setAddressEnable(uint8_t address){
      m_Addresses[address] = true;
    }
};

#endif
