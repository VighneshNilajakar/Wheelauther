#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

class ResourceManager {
public:
    static void initializeWiFi();
    static void cleanupWiFi();
    static bool checkMemory();
    static void freeResources();
    static void monitorResources();
};

#endif 