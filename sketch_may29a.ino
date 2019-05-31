#include <Ethernet.h> // the ethernet library must be compatible with the w5500 chip and the feather huzzah (this one for example : https://github.com/Wiznet/WIZ_Ethernet_Library)
#include <EthernetUdp.h>

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {
  0x98, 0x76, 0xB6, 0x11, 0x1F, 0x20
}; // depends on the ethernet shield 
byte target_mac[] = {0x94, 0xC6, 0x91, 0x17, 0x6D, 0x5C}; //depends on the target PC
byte gateway[] = {192,168,1,1};
byte subnet[] = {255,255,255,0};
IPAddress ip(192,168,1,133);
IPAddress remote(192,168,1,2);
IPAddress broadcastIP(192, 168, 1, 255);

unsigned int localPort = 8888;      // local port to listen on

EthernetUDP Udp;
char packetBuffer[UDP_TX_PACKET_MAX_SIZE];  // buffer to hold incoming packet,
char ReplyBuffer[] = "acknowledged";

// Initialize magic packet 
const int nMagicPacketLength = 102;
byte abyMagicPacket[nMagicPacketLength] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };

void setup()
{
  pinMode(0,OUTPUT);
  Serial.begin(115200); //communication initialization with the baud rate of the feather huzzah
  
  // Input for the push button
  pinMode(16,INPUT); 
  
  // disable SD SPI
  pinMode(4,OUTPUT);
  digitalWrite(4,HIGH);

  //enable ethernet
  pinMode(15, OUTPUT);    // make sure the the ETH controller is enabled
  digitalWrite(15, LOW);
  
  // start the Ethernet and UDP:
  Ethernet.begin(mac, ip, gateway, gateway, subnet);
  Udp.begin(localPort);

  // Make the magic packet for WoL
  for (int ix=6; ix<102; ix++)
      abyMagicPacket[ix]=target_mac[ix%6];
}

void loop()
{
    boolean a=digitalRead(16);
    Serial.println(a); // show button status on the monitor
    delay(1000);
    
    if (a==HIGH) // button normally open
    {
      digitalWrite(0,HIGH); 
    }
    if (a==LOW) // if button pressed send magic packet
    {
      digitalWrite(0,LOW);
      Udp.beginPacket(broadcastIP, 8888);
      Udp.write(abyMagicPacket,102);
      Udp.endPacket();
    }
}



    
