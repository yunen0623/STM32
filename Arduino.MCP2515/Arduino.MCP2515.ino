#include <SPI.h>
#include <mcp2515.h>
struct can_frame canMsg;
struct can_frame canMsg1;
MCP2515 mcp2515(53); //CSS

void setup() {
  canMsg1.can_id  = 0x1876AC23 | CAN_EFF_FLAG;
  canMsg1.can_dlc = 8;
  canMsg1.data[0] = 0x05;
  canMsg1.data[1] = 0x06;
  canMsg1.data[2] = 0x07;
  canMsg1.data[3] = 0x08;
  canMsg1.data[4] = 0x09;
  canMsg1.data[5] = 0x0A;
  canMsg1.data[6] = 0x0B;
  canMsg1.data[7] = 0x0C;
  
  while (!Serial);
  Serial.begin(115200);
  
  mcp2515.reset();
  mcp2515.setBitrate(CAN_125KBPS,MCP_8MHZ);
  //mcp2515.setLoopbackMode();
  mcp2515.setNormalMode();
  //mcp2515.setFilterMask(0,true,0);
  //mcp2515.setFilter(0,true,0);
  Serial.println("********MCP2515&STM32_CAN_Test*********");
  Serial.println("********Send Message*********");
  mcp2515.sendMessage(&canMsg1);
  Serial.print(canMsg1.can_id, HEX); // print ID
  Serial.print(" "); 
  Serial.print(canMsg1.can_dlc, HEX); // print DLC
  Serial.print(" ");
    
  for (int i = 0; i<canMsg1.can_dlc; i++)  
  {  
    Serial.print(canMsg1.data[i],HEX);
    Serial.print(" ");
  }
  Serial.println();
  delay(100);
}

void loop() {
  //mcp2515.sendMessage(&canMsg1);
  //delay(100);

  if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK)
  {
    Serial.print(canMsg.can_id, HEX); // print ID
    Serial.print(" "); 
    Serial.print(canMsg.can_dlc, HEX); // print DLC
    Serial.print(" ");
    
    for (int i = 0; i<canMsg.can_dlc; i++)  
    {  // print the data
      Serial.print(canMsg.data[i],HEX);
      Serial.print(" ");
    }
    Serial.println();
    delay(100);
    /*Serial.print("送出訊息");
    mcp2515.sendMessage(&canMsg1);
    Serial.print(canMsg1.can_id, HEX); // print ID
    Serial.print(" "); 
    Serial.print(canMsg1.can_dlc, HEX); // print DLC
    Serial.print(" ");
    for (int i = 0; i<canMsg1.can_dlc; i++) 
    {  // print the data
      Serial.print(canMsg1.data[i],HEX);
      Serial.print(" ");
    }
    Serial.println();
    delay(100);*/
  }
}
