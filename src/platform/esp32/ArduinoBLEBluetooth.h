#pragma once

#include "BluetoothCommon.h"
#include "main.h"
#include "utility/GAP.h"
#include <Arduino.h>
#include <ArduinoBLE.h>

class ArduinoBLEBluetooth : public BluetoothApi
{
  private:
    BLEDevice peripheral;
    BLEService meshService;
    BLECharacteristic fromNum;
    BLECharacteristic fromRadio;
    BLECharacteristic toRadio;
    BLECharacteristic logRadio;
    BLEService deviceInfo;
    BLEService batteryService;
    BLEUnsignedCharCharacteristic batteryLevel;

  public:
    ArduinoBLEBluetooth();
    void setup() override;
    void shutdown() override;
    void clearBonds() override;
    bool isConnected() override;
    int getRssi() override;
    void deinit() override;
    bool isActive() override;
    void sendLog(const uint8_t *logMessage, size_t length) override;
};