#include "ArduinoBLEBluetooth.h"

#if !MESHTASTIC_EXCLUDE_BLUETOOTH

const char *MESH_SERVICE_UUID_PTR = MESH_SERVICE_UUID;
const char *TORADIO_UUID_PTR = TORADIO_UUID;
const char *FROMRADIO_UUID_PTR = FROMRADIO_UUID;
const char *FROMNUM_UUID_PTR = FROMNUM_UUID;
const char *LOGRADIO_UUID_PTR = LOGRADIO_UUID;

static ArduinoBLEBluetooth *bleInstancePtr = nullptr;

/**
 * @brief Constructor initializes BLE services and characteristics.
 */
ArduinoBLEBluetooth::ArduinoBLEBluetooth()
    : meshService(MESH_SERVICE_UUID_PTR), // Mesh Service UUID
      fromNum(FROMNUM_UUID_PTR, BLENotify, ""), fromRadio(FROMRADIO_UUID_PTR, BLERead | BLENotify, ""),
      toRadio(TORADIO_UUID_PTR, BLEWrite | BLEWriteWithoutResponse, ""), logRadio(LOGRADIO_UUID_PTR, BLENotify, ""),
      deviceInfo("180F"), // Battery Service UUID
      batteryLevel("2A19", BLERead | BLENotify)
{
    bleInstancePtr = this; // Assign the static instance pointer
}

void ArduinoBLEBluetooth::setup()
{
    LOG_INFO("Setting up ArduinoBLEBluetooth...");

    // Begin BLE
    if (!BLE.begin()) {
        LOG_ERROR("Failed to initialize BLE!");

        while (1)
            ; // Halt execution
    }

    // Set the local name of the device
    BLE.setDeviceName("ESP32-C6_Device");
    BLE.setLocalName("ESP32-C6_Device");
    BLE.setAdvertisedService(meshService);
    BLE.setAdvertisedService(deviceInfo);

    // Add characteristics to Mesh Service
    meshService.addCharacteristic(toRadio);
    meshService.addCharacteristic(fromRadio);
    meshService.addCharacteristic(fromNum);
    meshService.addCharacteristic(logRadio);

    // Add Battery Service and its characteristic
    deviceInfo.addCharacteristic(batteryLevel);

    // Add services to BLE
    BLE.addService(meshService);
    BLE.addService(deviceInfo);

    // Start advertising
    BLE.advertise();
    LOG_INFO("BLE Device is now advertising...");
}

void ArduinoBLEBluetooth::shutdown()
{
    LOG_INFO("Shutting down ArduinoBLEBluetooth...");
    BLE.stopAdvertise();
    BLE.end();
    LOG_INFO("BLE shutdown complete.");
}

void ArduinoBLEBluetooth::clearBonds()
{
    // ArduinoBLE does not support bond management directly
    LOG_INFO("Clear Bonds: Not supported with ArduinoBLE.");
}

bool ArduinoBLEBluetooth::isConnected()
{
    return BLE.connected();
}

int ArduinoBLEBluetooth::getRssi()
{
    return peripheral.rssi();
}

bool ArduinoBLEBluetooth::isActive()
{
    // Active if advertising or connected
    return GAP.advertising() || BLE.connected();
}

void ArduinoBLEBluetooth::sendLog(const uint8_t *logMessage, size_t length)
{
    if (logRadio.written() || !BLE.connected()) {
        LOG_INFO("LogRadioCharacteristic not writable or BLE not connected.");
        return;
    }

    // Convert logMessage to String for ArduinoBLE
    String logStr = "";
    for (size_t i = 0; i < length; i++) {
        logStr += String((char)logMessage[i]);
    }

    logRadio.writeValue(logStr.c_str());
    LOG_INFO("Log message sent via BLE.");
}

void ArduinoBLEBluetooth::deinit()
{
    LOG_INFO("Deinitializing ArduinoBLEBluetooth...");
    // Any additional de-initialization if needed
}

#endif