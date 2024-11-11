#pragma once

#include "BluetoothCommon.h"
#include "main.h"
#include <Arduino.h>
#include <ArduinoBLE.h>

/**
 * @class ArduinoBLEBluetooth
 * @brief Handles BLE operations for ESP32.
 */
class ArduinoBLEBluetooth : public BluetoothApi
{
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