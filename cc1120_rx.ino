#include <SPI.h>
#include "cc1120.h"

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

void setup() {
  Serial.begin(9600);
  pinMode(RESET_PIN, OUTPUT);
  pinMode(SS_PIN, OUTPUT);
  digitalWrite(SS_PIN, HIGH);
  digitalWrite(RESET_PIN, HIGH);

  SPI.begin();

  strobeSPI(SNOP);  
  printStatus();

  uint8_t v = readSPI(CHAN_BW);
  Serial.print(F("CHAN_BW "));
  Serial.println(v, HEX);
  writeSPI(CHAN_BW, 0x18);
  v = readSPI(CHAN_BW);
  Serial.print(F("CHAN_BW "));
  Serial.println(v, HEX);
  v = readExtAddrSPI(PARTVERSION);
  Serial.print(F("PARTVERSION "));
  Serial.println(v, HEX);
  v = readExtAddrSPI(PARTNUMBER);
  Serial.print(F("PARTNUMBER "));
  Serial.println(v, HEX);

  v = readExtAddrSPI(FREQ1);
  Serial.print(F("FREQ1 "));
  Serial.println(v, HEX);
  writeExtAddrSPI(FREQ1, 0x16);
  v = readExtAddrSPI(FREQ1);
  Serial.print(F("FREQ1 "));
  Serial.println(v, HEX);
}

void loop() {
}

void printStatus() {
  Serial.println();
  Serial.print(F("Chip ready: "));
  Serial.println(ccstatus.ccst.chip_ready, HEX);
  Serial.print(F("State: "));
  Serial.println(ccstatus.ccst.state, HEX);
  Serial.println();  
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
