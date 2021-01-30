/**********************************
*Demo by Huex
*2021.01
*
**********************************/

#define MY_BUTTON_PIN 0 //按键0
#define ETH_CLK_MODE ETH_CLOCK_GPIO17_OUT
#define ETH_PHY_POWER -1
#define ETH_ADDR 0

// Type of the Ethernet PHY (LAN8720 or TLK110)
#define ETH_TYPE ETH_PHY_LAN8720
// I²C-address of Ethernet PHY (0 or 1 for LAN8720, 31 for TLK110)

// Pin# of the I²C clock signal for the Ethernet PHY
#define ETH_MDC_PIN 23
// Pin# of the I²C IO signal for the Ethernet PHY
#define ETH_MDIO_PIN 18
static bool eth_connected = false;
#define LED_BLINK 5

//  IO15 IO2 IO14 IO12 RX TX 可用
//POWER 6-18


#include "ETH.h"
#include <WiFiUdp.h>
#include "mbs.h"


void WiFiEvent(WiFiEvent_t event)
{
    switch (event) {
    case SYSTEM_EVENT_ETH_START:
        ETH.setHostname(espgo.ESPCFG.hostname);
        break;
    case SYSTEM_EVENT_ETH_CONNECTED:
        Serial.print("ETH Connected");
        break;
    case SYSTEM_EVENT_ETH_GOT_IP:
         Serial.print("ETH MAC: ");
         Serial.print(ETH.macAddress());
         Serial.print(", IPv4: ");
         Serial.print(ETH.localIP());
         if (ETH.fullDuplex()) {
             Serial.print(", FULL_DUPLEX");
         }
         Serial.print(", ");
         Serial.print(ETH.linkSpeed());
         Serial.println("Mbps");

        eth_connected = true;
        break;
    case SYSTEM_EVENT_ETH_DISCONNECTED:
        Serial.println("ETH Disconnected");
        eth_connected = false;
        break;
    case SYSTEM_EVENT_ETH_STOP:
        Serial.println("ETH Stopped");
        eth_connected = false;
        break;
    default:
        break;
    }
}
void setup()
{
    Serial.begin(115200);
    WiFi.onEvent(WiFiEvent);
    ETH.begin(ETH_ADDR, ETH_PHY_POWER, ETH_MDC_PIN, ETH_MDIO_PIN, ETH_TYPE, ETH_CLK_MODE);
    mbs_setup();

}

void loop()
{
    mbs_loop();
}
