#ifndef ERROR_HANDLER_H
#define ERROR_HANDLER_H

enum ErrorCode {
    NO_ERROR,
    MEMORY_LOW,
    WIFI_INIT_FAILED,
    MODE_SWITCH_FAILED,
    MOTOR_ERROR,
    DEAUTHER_ERROR
};

class ErrorHandler {
public:
    static void handleError(ErrorCode code);
    static void logError(const char* message);
    static bool hasError();
    static void clearErrors();
};

#endif 