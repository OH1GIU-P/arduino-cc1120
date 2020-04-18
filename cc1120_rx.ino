#include <SPI.h>
#include "cc1120.h"

#define PRINT_INFO 1

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

volatile bool packetAvailable = false;
uint8_t rxFifo[RXFIFO_SIZE];

void setup() {
  Serial.begin(9600);
  clearRxFifo();
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

  // CRC off
  uint8_t v = readSPI(PKT_CFG1);
  bitClear(v, 2);
  bitClear(v, 3);
  writeSPI(PKT_CFG1, v);
  // SYNC off
  v = readSPI(SYNC_CFG0);
  bitClear(v, 2);
  bitClear(v, 3);
  bitClear(v, 4);
  writeSPI(SYNC_CFG0, v);

  writeSPI(IOCFG0, RXFIFO_THR_PKT);
  writeSPI(SYNC_CFG1, SMARTRF_SETTING_SYNC_CFG1);
  writeSPI(MODCFG_DEV_E, SMARTRF_SETTING_MODCFG_DEV_E);
  writeSPI(DCFILT_CFG, SMARTRF_SETTING_DCFILT_CFG);
  writeSPI(PREAMBLE_CFG1, SMARTRF_SETTING_PREAMBLE_CFG1);
  writeSPI(IQIC, SMARTRF_SETTING_IQIC);
  writeSPI(CHAN_BW, SMARTRF_SETTING_CHAN_BW);
  writeSPI(MDMCFG0, SMARTRF_SETTING_MDMCFG0);
  writeSPI(SYMBOL_RATE2, SMARTRF_SETTING_SYMBOL_RATE2);
  writeSPI(AGC_REF, SMARTRF_SETTING_AGC_REF);
  writeSPI(AGC_CS_THR, SMARTRF_SETTING_AGC_CS_THR);
  writeSPI(AGC_CFG1, SMARTRF_SETTING_AGC_CFG1);
  writeSPI(AGC_CFG0, SMARTRF_SETTING_AGC_CFG0);
  writeSPI(FIFO_CFG, SMARTRF_SETTING_FIFO_CFG);
  writeSPI(FS_CFG, SMARTRF_SETTING_FS_CFG);
  writeSPI(PKT_CFG0, SMARTRF_SETTING_PKT_CFG0);
  writeSPI(PA_CFG2, SMARTRF_SETTING_PA_CFG2);
  writeSPI(PA_CFG0, SMARTRF_SETTING_PA_CFG0);
  writeSPI(PKT_LEN, SMARTRF_SETTING_PKT_LEN);

  writeExtAddrSPI(IF_MIX_CFG, SMARTRF_SETTING_IF_MIX_CFG);
  writeExtAddrSPI(FREQOFF_CFG, SMARTRF_SETTING_FREQOFF_CFG);
  writeExtAddrSPI(FREQ2, SMARTRF_SETTING_FREQ2);
  writeExtAddrSPI(FREQ1, SMARTRF_SETTING_FREQ1);
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

#ifdef PRINT_INFO
  v = readSPI(CHAN_BW);
  Serial.print(F("CHAN_BW "));
  Serial.println(v, HEX);;
  v = readExtAddrSPI(PARTVERSION);
  Serial.print(F("PARTVERSION "));
  Serial.println(v, HEX);
  v = readExtAddrSPI(PARTNUMBER);
  Serial.print(F("PARTNUMBER "));
  Serial.println(v, HEX);

  v = readExtAddrSPI(FREQ1);
  Serial.print(F("FREQ1 "));
  Serial.println(v, HEX);
#endif

  attachInterrupt(digitalPinToInterrupt(GDO0_PIN), isr, RISING);

  strobeSPI(SRX);
  delay(5);
  v = readExtAddrSPI(MARCSTATE);
  Serial.print(F("MARCSTATE "));
  Serial.println(v, BIN);
}

void loop() {
}

void isr() {
  if (packetAvail()) {
    packetAvailable = true;
  }
  else {
    packetAvailable = false;
  }
}

void clearRxFifo() {
  memset(rxFifo, 0, sizeof(rxFifo));  
}

void printStatus() {
  Serial.println();
  Serial.print(F("Chip ready: "));
  Serial.println(ccstatus.ccst.chip_ready, HEX);
  Serial.print(F("State: "));
  Serial.println(ccstatus.ccst.state, HEX);
  Serial.println();  
}

bool packetAvail() {
  if (digitalRead(GDO0_PIN)) {
    return true;
  }
  return false;
}

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
