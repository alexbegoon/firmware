#include "ArduinoBLEBluetooth.h"

#if !MESHTASTIC_EXCLUDE_BLUETOOTH

// UUID Definitions
const char *MESH_SERVICE_UUID_PTR = MESH_SERVICE_UUID;
const char *TORADIO_UUID_PTR = TORADIO_UUID;
const char *FROMRADIO_UUID_PTR = FROMRADIO_UUID;
const char *FROMNUM_UUID_PTR = FROMNUM_UUID;
const char *LOGRADIO_UUID_PTR = LOGRADIO_UUID;
const char *BATTERY_LEVEL_UUID_PTR = "2A19"; // Standard Battery Level UUID

static ArduinoBLEBluetooth *bleInstancePtr = nullptr;

#define SERVICE_UUID "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"
// Advertising parameters should have a global scope. Do NOT define them in 'setup' or in 'loop'
const uint8_t completeRawAdvertisingData[] = {0x02, 0x01, 0x06, 0x09, 0xff, 0x01, 0x01, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05};

/**
 * @brief Constructor initializes BLE instance pointer.
 */
ArduinoBLEBluetooth::ArduinoBLEBluetooth()
{
    bleInstancePtr = this; // Assign the static instance pointer
}

void ArduinoBLEBluetooth::setup()
{
    BLEService myService("fff0");
    BLEIntCharacteristic myCharacteristic("fff1", BLERead | BLEBroadcast);

    if (!BLE.begin()) {
        Serial.println("failed to initialize BLE!");
        while (1)
            ;
    }

    myService.addCharacteristic(myCharacteristic);
    BLE.addService(myService);

    // Build advertising data packet
    BLEAdvertisingData advData;
    // If a packet has a raw data parameter, then all the other parameters of the packet will be ignored
    advData.setRawData(completeRawAdvertisingData, sizeof(completeRawAdvertisingData));
    // Copy set parameters in the actual advertising packet
    BLE.setAdvertisingData(advData);

    // Build scan response data packet
    BLEAdvertisingData scanData;
    scanData.setLocalName("Test advertising raw data");
    // Copy set parameters in the actual scan response packet
    BLE.setScanResponseData(scanData);

    BLE.advertise();

    LOG_INFO("BLE Device is now advertising...");
    //    LOG_INFO("Setting up ArduinoBLEBluetooth...");
    //
    //    // Initialize BLE
    //    BLEDevice::init("ESP32-C6_Device");
    //    pServer = BLEDevice::createServer();
    //
    //    // Create Mesh Service
    //    meshService = pServer->createService(MESH_SERVICE_UUID_PTR);
    //
    //    // Create Characteristics with appropriate properties
    //    fromNum = meshService->createCharacteristic(
    //        FROMNUM_UUID_PTR,
    //        BLECharacteristic::PROPERTY_NOTIFY
    //    );
    //
    //    fromRadio = meshService->createCharacteristic(
    //        FROMRADIO_UUID_PTR,
    //        BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY
    //    );
    //
    //    toRadio = meshService->createCharacteristic(
    //        TORADIO_UUID_PTR,
    //        BLECharacteristic::PROPERTY_WRITE | BLECharacteristic::PROPERTY_WRITE_NR
    //    );
    //
    //    logRadio = meshService->createCharacteristic(
    //        LOGRADIO_UUID_PTR,
    //        BLECharacteristic::PROPERTY_NOTIFY
    //    );
    //
    //    // Create Device Info (Battery Service)
    //    deviceInfo = pServer->createService("180F"); // Battery Service UUID
    //    batteryLevel = deviceInfo->createCharacteristic(
    //        BATTERY_LEVEL_UUID_PTR,
    //        BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY
    //    );
    //
    //    // Start services
    //    meshService->start();
    //    deviceInfo->start();
    //
    //    // Start advertising
    //    BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
    //    pAdvertising->addServiceUUID(MESH_SERVICE_UUID_PTR);
    //    pAdvertising->setScanResponse(true);
    //    pAdvertising->setMinPreferred(0x06);  // Functions that help with iPhone connections issue
    //    pAdvertising->setMinPreferred(0x12);
    //    BLEDevice::startAdvertising();
    //    LOG_INFO("BLE Device is now advertising...");
}

void ArduinoBLEBluetooth::shutdown()
{
    // TODO
    return;

    //    LOG_INFO("Shutting down ArduinoBLEBluetooth...");
    //    BLEDevice::stopAdvertising();
    //    BLEDevice::deinit();
    //    LOG_INFO("BLE shutdown complete.");
}

void ArduinoBLEBluetooth::clearBonds()
{
    // TODO
}

bool ArduinoBLEBluetooth::isConnected()
{
    // TODO
    return false;
    //    return pServer->getConnectedCount() > 0;
}

int ArduinoBLEBluetooth::getRssi()
{
    // ESP32 BLE library does not provide RSSI directly
    LOG_WARN("RSSI retrieval not implemented.");
    return 0;
}

bool ArduinoBLEBluetooth::isActive()
{
    // TODO
    return false;
    //    return isConnected(); // Active if connected
}

void ArduinoBLEBluetooth::sendLog(const uint8_t *logMessage, size_t length)
{
    // TODO
    return;
    //    if (!isConnected()) {
    //        LOG_INFO("BLE not connected. Cannot send log.");
    //        return;
    //    }
    //
    //    // Convert logMessage to String for BLE
    //    std::string logStr(reinterpret_cast<const char*>(logMessage), length);
    //    logRadio->setValue(logStr);
    //    logRadio->notify();
    //    LOG_INFO("Log message sent via BLE.");
}

void ArduinoBLEBluetooth::deinit()
{
    // TODO
    LOG_INFO("Deinitializing ArduinoBLEBluetooth...");
    //    shutdown();
    // Any additional de-initialization if needed
}

#endif // MESHTASTIC_EXCLUDE_BLUETOOTH