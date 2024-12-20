#ifndef TEST_FRAMEWORK_H
#define TEST_FRAMEWORK_H

class TestFramework {
public:
    static void runAllTests();
    static void testModeSwitching();
    static void testMotorControl();
    static void testDeautherFunctions();
    static void testResourceManagement();
};

#endif 