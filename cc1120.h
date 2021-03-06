/* Address Config = No address check */
/* Bit Rate = 1.2 */
/* Carrier Frequency = 433.902 */
/* Deviation = 3.997803 */
/* Device Address = 0 */
/* Manchester Enable = false */
/* Modulation Format = ASK/OOK */
/* PA Ramping = false */
/* Packet Bit Length = 0 */
/* Packet Length = 3 */
/* Packet Length Mode = Variable */
/* Performance Mode = High Performance */
/* RX Filter BW = 25.000000 */
/* Symbol rate = 1.2 */
/* TX Power = 12.5 */
/* Whitening = false */
/***************************************************************
 *  SmartRF Studio(tm) Export
 *
 *  Radio register settings specifed with C-code
 *  compatible #define statements.
 *
 *  RF device: CC1120
 *
 ***************************************************************/

#ifndef SMARTRF_CC1120_H
#define SMARTRF_CC1120_H

#define SMARTRF_RADIO_CC1120
//#define SMARTRF_SETTING_IOCFG3           0xB0
//#define SMARTRF_SETTING_IOCFG2           0x08
//#define SMARTRF_SETTING_IOCFG1           0xB0
#define SMARTRF_SETTING_IOCFG0           0x09
//#define SMARTRF_SETTING_SYNC3            0xAA
//#define SMARTRF_SETTING_SYNC2            0xAA
//#define SMARTRF_SETTING_SYNC1            0xAA
//#define SMARTRF_SETTING_SYNC0            0xAA
#define SMARTRF_SETTING_SYNC_CFG1        0x1F
#define SMARTRF_SETTING_MODCFG_DEV_E     0x1B
#define SMARTRF_SETTING_DCFILT_CFG       0x1C
#define SMARTRF_SETTING_PREAMBLE_CFG1    0x00
#define SMARTRF_SETTING_IQIC             0xC6
#define SMARTRF_SETTING_CHAN_BW          0x0A
#define SMARTRF_SETTING_MDMCFG1          0x06
#define SMARTRF_SETTING_MDMCFG0          0x4A
#define SMARTRF_SETTING_AGC_REF          0x20
#define SMARTRF_SETTING_AGC_CS_THR       0x19
#define SMARTRF_SETTING_AGC_CFG1         0x0A
#define SMARTRF_SETTING_FIFO_CFG         0x00
#define SMARTRF_SETTING_FS_CFG           0x14
#define SMARTRF_SETTING_PKT_CFG2         0x07
#define SMARTRF_SETTING_PKT_CFG1         0x00
#define SMARTRF_SETTING_PKT_CFG0         0x20
#define SMARTRF_SETTING_PA_CFG2          0x3C
#define SMARTRF_SETTING_IF_MIX_CFG       0x00
#define SMARTRF_SETTING_FREQOFF_CFG      0x23 // 0x22
#define SMARTRF_SETTING_FREQ2            0x6C
#define SMARTRF_SETTING_FREQ1            0x79  
#define SMARTRF_SETTING_FREQ0            0x99
#define SMARTRF_SETTING_FS_DIG1          0x00
#define SMARTRF_SETTING_FS_DIG0          0x5F
#define SMARTRF_SETTING_FS_CAL1          0x40
#define SMARTRF_SETTING_FS_CAL0          0x0E
#define SMARTRF_SETTING_FS_DIVTWO        0x03
#define SMARTRF_SETTING_FS_DSM0          0x33
#define SMARTRF_SETTING_FS_DVC0          0x17
#define SMARTRF_SETTING_FS_PFD           0x50
#define SMARTRF_SETTING_FS_PRE           0x6E
#define SMARTRF_SETTING_FS_REG_DIV_CML   0x14
#define SMARTRF_SETTING_FS_SPARE         0xAC
#define SMARTRF_SETTING_FS_VCO0          0xB4
#define SMARTRF_SETTING_XOSC5            0x0E
#define SMARTRF_SETTING_XOSC1            0x03
#define SMARTRF_SETTING_SERIAL_STATUS    0x08

// Pins
#define GDO0_PIN        2
#define RESET_PIN       7
#define SS_PIN          10

#define SERIAL_RX       0x09

#define R_BIT           0x80

// CC1120 registers
#define IOCFG3          0x00
#define IOCFG2          0x01
#define IOCFG1          0x02
#define IOCFG0          0x03
#define SYNC3           0x04
#define SYNC2           0x05
#define SYNC1           0x06
#define SYNC0           0x07
#define SYNC_CFG1       0x08
#define SYNC_CFG0       0x09
#define DEVIATION_M     0x0A
#define MODCFG_DEV_E    0x0B
#define DCFILT_CFG      0x0C
#define PREAMBLE_CFG1   0x0D
#define PREAMBLE_CFG0   0x0E
#define FREQ_IF_CFG     0x0F
#define IQIC            0x10
#define CHAN_BW         0x11
#define MDMCFG1         0x12
#define MDMCFG0         0x13
#define SYMBOL_RATE2    0x14
#define SYMBOL_RATE1    0x15
#define SYMBOL_RATE0    0x16
#define AGC_REF         0x17
#define AGC_CS_THR      0x18
#define AGC_GAIN_ADJUST 0x19
#define AGC_CFG3        0x1A
#define AGC_CFG2        0x1B
#define AGC_CFG1        0x1C
#define AGC_CFG0        0x1D
#define FIFO_CFG        0x1E
#define DEV_ADDR        0x1F
#define SETTLING_CFG    0x20
#define FS_CFG          0x21
#define WOR_CFG1        0x22
#define WOR_CFG0        0x23
#define WOR_EVENT0_MSB  0x24
#define WOR_EVENT0_LSB  0x25
#define PKT_CFG2        0x26
#define PKT_CFG1        0x27
#define PKT_CFG0        0x28
#define RFEND_CFG1      0x29
#define RFEND_CFG2      0x2A
#define PA_CFG2         0x2B
#define PA_CFG1         0x2C
#define PA_CFG0         0x2D
#define PKT_LEN         0x2E
#define EXT_ADDR        0x2F
#define FIFO            0x3F

// Extended register space
#define IF_MIX_CFG        0x00
#define FREQOFF_CFG       0x01
#define FREQ2             0x0C
#define FREQ1             0x0D
#define FREQ0             0x0E
#define FS_DIG1           0x12
#define FS_DIG0           0x13
#define FS_CAL1           0x16
#define FS_CAL0           0x17
#define FS_DIVTWO         0x19
#define FS_DSM0           0x1B
#define FS_DVC0           0x1D
#define FS_PFD            0x1F
#define FS_PRE            0x20
#define FS_REG_DIV_CML    0x21
#define FS_SPARE          0x22
#define FS_VCO0           0x27
#define XOSC5             0x32
#define XOSC1             0x36
#define RSSI1             0x71
#define RSSI0             0x72
#define MARCSTATE         0x73
#define PARTNUMBER        0x8F
#define PARTVERSION       0x90
#define SERIAL_STATUS     0x91
#define MODEM_STATUS1     0x92
#define MODEM_STATUS0     0x93
#define MARC_STATUS1      0x94
#define MARC_STATUS0      0x95
#define NUM_RXBYTES       0xD7
#define FIFO_NUM_RXBYTES  0xD9

// CC1120 command strobes
#define SRES            0x30
#define SFSTXON         0x31
#define SXOFF           0x32
#define SCAL            0x33
#define SRX             0x34
#define STX             0x35
#define SIDLE           0x36
#define SAFC            0x37
#define SWOR            0x38
#define SPWD            0x39
#define SFRX            0x3A
#define SFTX            0x3B
#define SWORRST         0x3C
#define SNOP            0x3D

#endif // CC1120_H
