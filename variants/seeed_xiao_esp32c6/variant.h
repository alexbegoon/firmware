#define LED_PIN 15
#define LED_STATE_ON 1 // State when LED is lit

#define BUTTON_PIN 22 // This is the Program Button
#define BUTTON_NEED_PULLUP

#define SOC_I2C_NUM 2

#define HAS_ETHERNET 0

#define PIN_ETHERNET_RESET 21
#define PIN_ETHERNET_SS 26
#define ETH_SPI_PORT SPI
#define AQ_SET_PIN 10

#define USE_RF95
#define LORA_MISO 20
#define LORA_SCK 19
#define LORA_MOSI 18
#define LORA_CS 17
#define LORA_RESET 1
#define LORA_DIO0 0
#define LORA_DIO1 16

#define HAS_GPS 0
#undef GPS_RX_PIN
#undef GPS_TX_PIN