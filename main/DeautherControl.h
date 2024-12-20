#ifndef DEAUTHER_CONTROL_H
#define DEAUTHER_CONTROL_H

class DeautherControl {
private:
    static bool isActive;
    
public:
    static void initialize();
    static void shutdown();
    static void update();
    static bool startScan();
    static bool startAttack(int attackType);
    static bool stopAttack();
    static bool isInitialized();
};

#endif