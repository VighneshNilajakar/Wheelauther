#include "ResourceManager.h"
#include <ESP8266WiFi.h>

void ResourceManager::initializeWiFi() {
    WiFi.mode(WIFI_AP_STA);
    WiFi.softAP("ESP8266_Project", "password123");
}

void ResourceManager::cleanupWiFi() {
    WiFi.disconnect();
    WiFi.mode(WIFI_OFF);
    WiFi.forceSleepBegin();
    delay(1); // Allow WiFi to enter sleep mode
}

bool ResourceManager::checkMemory() {
    uint32_t freeHeap = ESP.getFreeHeap();
    return (freeHeap > 4096); // Minimum required heap
}

void ResourceManager::monitorResources() {
    if (!checkMemory()) {
        freeResources();
    }
} 