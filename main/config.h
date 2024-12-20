#ifndef CONFIG_H
#define CONFIG_H

// WiFi Settings
#define WIFI_SSID "ESP-Project"
#define WIFI_PASSWORD "12345678"

// Motor Pins
#define MOTOR_LEFT_PIN1  D1
#define MOTOR_LEFT_PIN2  D2
#define MOTOR_RIGHT_PIN1 D3
#define MOTOR_RIGHT_PIN2 D4

// Deauther Settings
#define SCAN_TIME 10000
#define ATTACK_TIME 60000
#define MAX_NETWORKS 64
#define CHANNEL_HOP_INTERVAL 200

#endif