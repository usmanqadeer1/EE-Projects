
#include "RF24Network.h"
#include "RF24.h"
#include "RF24Mesh.h"
#include <SPI.h>
uint8_t nodeID;
/***** Configure the chosen CE,CS pins *****/
RF24 radio(7, 8);
RF24Network network(radio);
RF24Mesh mesh(radio, network);

struct payload_t {
  unsigned long ms;
  unsigned long counter;
};

struct nodeDATA {
  float voltage;
  float lightsenstivity;
  float resistanceRod;
  float temperature;
};

uint32_t ctr = 0;


int check=0;
int queryNode=1;
int j=0;
int timeout[100];
int t=0;
void setup() {
  Serial.begin(115200);

  // Set the nodeID to 0 for the master node
  mesh.setNodeID(0);
  Serial.println(mesh.getNodeID());
  // Connect to the mesh
  mesh.begin(100);

}

uint32_t displayTimer = 0;
uint32_t delayTimer = 0;
uint32_t delayTimer1 = 0;
void loop() {

  mesh.update();
  mesh.DHCP();
  nodeDATA nd;
  
  if (network.available()) {
    RF24NetworkHeader header;
    network.peek(header);
    uint32_t dat = 0;
    char text[32] = "";
    switch (header.type) {
      // Display the incoming millis() values from the sensor nodes
      case 'M':
        network.read(header, &nd, sizeof(nd));
        Serial.print("Received ");
        Serial.print("Voltage : ");
        Serial.print(nd.voltage);
        Serial.print(",  Temperature : ");
        Serial.print(nd.temperature);
        Serial.print(",  Light Senstivity : ");
        Serial.print(nd.lightsenstivity);
        Serial.print(",  Resistance : ");
        Serial.print(nd.resistanceRod);
        Serial.print("  from Node :    ");
        Serial.println(mesh.getNodeID(header.from_node));
        
        break;
      default:
        network.read(header, 0, 0);
        Serial.println(header.type);
        break;
    }
  }
  
  
    if(millis() - delayTimer > 1000)
    {
      delayTimer = millis();
      ctr++;
      payload_t payload = {999, ctr};
      for (int i = 0; i < mesh.addrListTop; i++) 
      {
        if (mesh.addrList[i].nodeID == queryNode) 
        {  
          Serial.println(queryNode);
          
          RF24NetworkHeader header(mesh.addrList[i].address, OCT);
         
          if(network.write(header, &payload, sizeof(payload))){
            Serial.println("Send OK");
            timeout[i]=0;
                
          }
          else{ 
            Serial.println("Send Fail");
            timeout[i]++;
          }
          
          if(timeout[i]==10)
          {
            Serial.print("Timeout for Node :");
            Serial.print(mesh.addrList[i].nodeID);
            Serial.println("   Removed!");
            timeout[i]=0;
            t=i;
            while(t<mesh.addrListTop-1)
            {
               mesh.addrList[t]=mesh.addrList[t+1];
               t++;
            }
            mesh.addrListTop--; 
            i--;
          }
          
        }
      }
    }
    
  if(millis() - displayTimer > 5000){
    displayTimer = millis();
    Serial.println(" ");
    Serial.println(F("********Assigned Addresses********"));
     for(int i=0; i<mesh.addrListTop; i++){
       Serial.print("NodeID: ");
       Serial.print(mesh.addrList[i].nodeID);
       Serial.print(" RF24Network Address: 0");
       Serial.println(mesh.addrList[i].address,OCT);
     }
    Serial.println(F("**********************************"));
    
    queryNode=mesh.addrList[j].nodeID;
    j=(j+1)%mesh.addrListTop;
  }
}                                                                                                                                                                
