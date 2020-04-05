#ifndef cc1120_H
#define cc1120_H

/* Address Config = No address check */
/* Bit Rate = 19.2 */
/* Carrier Frequency = 423.875000 */
/* Deviation = 3.997803 */
/* Device Address = 0 */
/* Manchester Enable = false */
/* Modulation Format = 4-GFSK */
/* PA Ramping = false */
/* Packet Bit Length = 0 */
/* Packet Length = 255 */
/* Packet Length Mode = Variable */
/* Performance Mode = High Performance */
/* RX Filter BW = 25.000000 */
/* Symbol rate = 9.6 */
/* TX Power = 0 */
/* Whitening = false */

#define SMARTRF_SETTING_IOCFG3           0xB0
#define SMARTRF_SETTING_IOCFG2           0x06
#define SMARTRF_SETTING_IOCFG1           0xB0
#define SMARTRF_SETTING_IOCFG0           0x40
#define SMARTRF_SETTING_SYNC_CFG1        0x08
#define SMARTRF_SETTING_MODCFG_DEV_E     0x2B
#define SMARTRF_SETTING_DCFILT_CFG       0x1C
#define SMARTRF_SETTING_PREAMBLE_CFG1    0x18
#define SMARTRF_SETTING_IQIC             0xC6
#define SMARTRF_SETTING_CHAN_BW          0x08
#define SMARTRF_SETTING_MDMCFG0          0x05
#define SMARTRF_SETTING_SYMBOL_RATE2     0x73
#define SMARTRF_SETTING_AGC_REF          0x20
#define SMARTRF_SETTING_AGC_CS_THR       0x19
#define SMARTRF_SETTING_AGC_CFG1         0xA9
#define SMARTRF_SETTING_AGC_CFG0         0xCF
#define SMARTRF_SETTING_FIFO_CFG         0x00
#define SMARTRF_SETTING_FS_CFG           0x14
#define SMARTRF_SETTING_PKT_CFG0         0x20
#define SMARTRF_SETTING_PA_CFG2          0x1D
#define SMARTRF_SETTING_PA_CFG0          0x7D
#define SMARTRF_SETTING_PKT_LEN          0xFF

// Extended register space
#define SMARTRF_SETTING_IF_MIX_CFG       0x00
#define SMARTRF_SETTING_FREQOFF_CFG      0x22
#define SMARTRF_SETTING_FREQ2            0x69
#define SMARTRF_SETTING_FREQ1            0xF8
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

// Pins
#define RESET_PIN       7
#define SS_PIN          10

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
#define FREQ1             0x0D
#define FREQ2             0x0C
#define FS_DIG1           0x12
#define FS_DIG0           0x13
#define FS_CAL1           0x16
#define FS_CAL0           0x17
#define FS_DIVTWO         0x19
#define FS_DSM0           0x1B
#define FS_DVC0           0x1D
#define RSSI1             0x71
#define RSSI0             0x72
#define MARCSTATE         0x73
#define PARTNUMBER        0x8F
#define PARTVERSION       0x90
#define MODEM_STATUS1     0x92
#define MODEM_STATUS0     0x93
#define MARC_STATUS1      0x94
#define MARC_STATUS0      0x95
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
