/**********************************
*RS485 demo by Huex
*2020.09
**********************************/

#include "mbs.h"
#include "Arduino.h"

HardwareSerial RS485serial(1);
Ticker Mbsback;

unsigned char rs485_rx_count = 0;
#define MBS_MESSAGE_SIZE 22
u8_t Uart485_Rx[MBS_MESSAGE_SIZE];
bool SerialBusy;
unsigned long Serialmills;
unsigned long TimeOutValue = 50;

#define RS485_EN 4 //rs485使能接口


void mbs_regTime()
{
    digitalWrite(RS485_EN, HIGH);
    byte buff[] = { 0x01, 0x03, 0x00, 0x02, 0x00, 0x08, 0xE5, 0xCC };
      RS485serial.write(buff, sizeof(buff));
    // // delayMicroseconds(13*64);
    RS485serial.flush();
    digitalWrite(RS485_EN, LOW);
    delay(60); //等待数据返回 超过50ms即可
    /*
    读取RS485serial并处理结果
    */
}

void mbs_write(u8_t func, u8_t value)
{
    byte buff[8];
    buff[0] = 0x01;
    buff[1] = 0x06;
    buff[2] = 0x00;
    RS485serial.write(buff, sizeof(buff));
    delay(10);
}
void mbs_setup()
{
    pinMode(RS485_EN, OUTPUT);
    digitalWrite(RS485_EN, LOW);
    RS485serial.begin(9600, SERIAL_8N1, 33, 32); //32 33 //引用第一路
    Mbsback.attach(0.3, mbs_regTime); //每200ms读取一次操作
}
void mbs_loop()
{
}