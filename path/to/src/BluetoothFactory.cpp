#include "BluetoothCommon.h"

#ifdef CONFIG_IDF_TARGET_ESP32C6
#include "ArduinoBLEBluetooth.h"
#else
#include "NimbleBluetooth.h"
#endif

BluetoothApi *createBluetoothInstance()
{
#ifdef CONFIG_IDF_TARGET_ESP32C6
    return new ArduinoBLEBluetooth();
#else
    return new NimbleBluetooth();
#endif
}