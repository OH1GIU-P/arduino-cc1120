#include <RCSwitch.h>
#include <SPI.h>
#include "cc1120.h"

/*
 CHANBW
 8 kHz      0x19
 10 kHz     0x14
 12.5 kHz   0x10 
 15.38 kHz  0x0D
 18.18 kHz  0x0B
 20 kHz     0x0A
 25 kHz     0x08
 28.5 kHz   0x07
 33.3 kHz   0x06
 40 kHz     0x05
 50 kHz     0x04

 433.902 MHz
 FREQ2 0x6C
 FREQ1 0x79
 FREQ0 0x99
*/
 
RCSwitch rcs = RCSwitch();

#define PRINT_INFO          1
#define RCS_RX              "Received "
#define RCS_SEP             " / "
#define RCS_UNKNOWN_ENC     "Unknown encoding"
#define RCS_BIT             "bit "
#define RCS_PROTOCOL        "Protocol: "

struct cc_status {
 uint8_t res : 4;
 uint8_t state : 3;
 uint8_t chip_ready : 1;
};
union cc_st {
  struct cc_status ccst;
  uint8_t v;
};

union cc_st ccstatus;

//volatile uint32_t duration = 0;
//volatile bool     chg      = false;

void setup() {
  Serial.begin(19200);
  pinMode(RESET_PIN, OUTPUT);
  pinMode(SS_PIN, OUTPUT);
  pinMode(GDO0_PIN, INPUT);
  digitalWrite(SS_PIN, HIGH);
  digitalWrite(RESET_PIN, HIGH);

  SPI.begin();

  strobeSPI(SNOP);
#ifdef PRINT_INFO  
  printStatus();
#endif

  uint8_t v;

  writeSPI(IOCFG0, SERIAL_RX);
  writeSPI(SYNC_CFG1, SMARTRF_SETTING_SYNC_CFG1);
  writeSPI(MODCFG_DEV_E, SMARTRF_SETTING_MODCFG_DEV_E);
  writeSPI(DCFILT_CFG, SMARTRF_SETTING_DCFILT_CFG);
  writeSPI(PREAMBLE_CFG1, SMARTRF_SETTING_PREAMBLE_CFG1);
  writeSPI(IQIC, SMARTRF_SETTING_IQIC);
  writeSPI(CHAN_BW, SMARTRF_SETTING_CHAN_BW);
  writeSPI(MDMCFG0, SMARTRF_SETTING_MDMCFG0);
  writeSPI(MDMCFG1, SMARTRF_SETTING_MDMCFG1);
  writeSPI(AGC_REF, SMARTRF_SETTING_AGC_REF);
  writeSPI(AGC_CS_THR, SMARTRF_SETTING_AGC_CS_THR);
  writeSPI(AGC_CFG1, SMARTRF_SETTING_AGC_CFG1);
  writeSPI(FIFO_CFG, SMARTRF_SETTING_FIFO_CFG);
  writeSPI(FS_CFG, SMARTRF_SETTING_FS_CFG);
  writeSPI(PKT_CFG0, SMARTRF_SETTING_PKT_CFG0);
  writeSPI(PKT_CFG1, SMARTRF_SETTING_PKT_CFG1);
  writeSPI(PKT_CFG2, SMARTRF_SETTING_PKT_CFG2);
  writeSPI(PA_CFG2, SMARTRF_SETTING_PA_CFG2);

  writeExtAddrSPI(IF_MIX_CFG, SMARTRF_SETTING_IF_MIX_CFG);
  writeExtAddrSPI(FREQOFF_CFG, SMARTRF_SETTING_FREQOFF_CFG);
  writeExtAddrSPI(FREQ2, SMARTRF_SETTING_FREQ2);
  writeExtAddrSPI(FREQ1, SMARTRF_SETTING_FREQ1);
  writeExtAddrSPI(FREQ0, SMARTRF_SETTING_FREQ0);
  writeExtAddrSPI(FS_DIG1, SMARTRF_SETTING_FS_DIG1);
  writeExtAddrSPI(FS_DIG0, SMARTRF_SETTING_FS_DIG0);
  writeExtAddrSPI(FS_CAL1, SMARTRF_SETTING_FS_CAL1);
  writeExtAddrSPI(FS_CAL0, SMARTRF_SETTING_FS_CAL0);
  writeExtAddrSPI(FS_DIVTWO, SMARTRF_SETTING_FS_DIVTWO);
  writeExtAddrSPI(FS_DSM0, SMARTRF_SETTING_FS_DSM0);
  writeExtAddrSPI(FS_DVC0, SMARTRF_SETTING_FS_DVC0);
  writeExtAddrSPI(FS_PFD, SMARTRF_SETTING_FS_PFD);
  writeExtAddrSPI(FS_PRE, SMARTRF_SETTING_FS_PRE);
  writeExtAddrSPI(FS_REG_DIV_CML, SMARTRF_SETTING_FS_REG_DIV_CML);
  writeExtAddrSPI(FS_SPARE, SMARTRF_SETTING_FS_SPARE);
  writeExtAddrSPI(FS_VCO0, SMARTRF_SETTING_FS_VCO0);
  writeExtAddrSPI(XOSC5, SMARTRF_SETTING_XOSC5);
  writeExtAddrSPI(XOSC1, SMARTRF_SETTING_XOSC1);
  writeExtAddrSPI(SERIAL_STATUS, SMARTRF_SETTING_SERIAL_STATUS);

#ifdef PRINT_INFO
  v = readExtAddrSPI(PARTVERSION);
  Serial.print(F("PARTVERSION "));
  Serial.println(v, HEX);
  v = readExtAddrSPI(PARTNUMBER);
  Serial.print(F("PARTNUMBER "));
  Serial.println(v, HEX);
#endif

  strobeSPI(SRX);
  delay(5);
  v = readExtAddrSPI(MARCSTATE);
  Serial.print(F("MARCSTATE "));
  Serial.println(v, BIN);

  rcs.enableReceive(0);
  //attachInterrupt(digitalPinToInterrupt(GDO0_PIN), isr, CHANGE);
}

void loop() {
//  if (chg) {
//    chg = false;
//    Serial.println(duration); 
//  }
  if (rcs.available()) {
    uint32_t v = rcs.getReceivedValue();
    if (v != 0) {
      Serial.print(F(RCS_RX));
      Serial.print(v);
      Serial.print(F(RCS_SEP));
      Serial.print(rcs.getReceivedBitlength());
      Serial.print(F(RCS_BIT));
      Serial.print(F(RCS_PROTOCOL));
      Serial.println(rcs.getReceivedProtocol());
    } 
    else {
      Serial.print(F(RCS_UNKNOWN_ENC));
    }
    rcs.resetAvailable();
  }
//  uint8_t v = readExtAddrSPI(RSSI1);
//  if (v < 127) Serial.println(v);
}

void printStatus() {
  Serial.println();
  Serial.print(F("Chip ready: "));
  Serial.println(ccstatus.ccst.chip_ready, HEX);
  Serial.print(F("State: "));
  Serial.println(ccstatus.ccst.state, HEX);
  Serial.println();  
}

//void isr() {
//  static uint32_t lastTi = 0;
//  
//  uint32_t ti = micros();
//  duration = ti - lastTi;
//  chg = true;
//  lastTi = ti;
//}

uint8_t readSPI(uint8_t addr) {
  digitalWrite(SS_PIN, LOW);
  ccstatus.v = SPI.transfer(R_BIT | addr);
  uint8_t v = SPI.transfer(0x00);
  digitalWrite(SS_PIN, HIGH);
  return v;
}

void writeSPI(uint8_t addr, uint8_t value) {
  digitalWrite(SS_PIN, LOW);
  ccstatus.v = SPI.transfer(addr);
  ccstatus.v = SPI.transfer(value);
  digitalWrite(SS_PIN, HIGH);
}

void strobeSPI(uint8_t cmd)
{
  digitalWrite(SS_PIN, LOW);
  ccstatus.v = SPI.transfer(R_BIT | cmd);
  digitalWrite(SS_PIN, HIGH);
}

uint8_t readExtAddrSPI(uint8_t addr) {
  uint8_t v;
  digitalWrite(SS_PIN, LOW);
  ccstatus.v = SPI.transfer(R_BIT | EXT_ADDR);
  SPI.transfer(addr);
  v = SPI.transfer(0xff);
  digitalWrite(SS_PIN, HIGH);
  return v;
}

void writeExtAddrSPI(uint8_t addr, uint8_t value) {
  digitalWrite(SS_PIN, LOW);
  ccstatus.v = SPI.transfer(EXT_ADDR);
  ccstatus.v = SPI.transfer(addr);
  ccstatus.v = SPI.transfer(value);
  digitalWrite(SS_PIN, HIGH);
}
