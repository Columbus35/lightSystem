#include <WiFi.h>

class WiFiConnector {
public:
void connect(){
    connectWifi();
}    
private:
    const char* ssid = "Wifi user name";
    const char* password = "wifi password";
    const char *ntpServer = "pool.ntp.org";
    const long gmtOffset_sec = 3600L * 3;
    const int daylightOffset_sec = 0;

    void connectWifi() {
        boolean ledState = false;

        Serial.print("Connecting to WiFi network ");
        WiFi.begin(ssid, password);
        while (WiFi.status() != WL_CONNECTED) {
            delay(500);
            Serial.print(".");
            ledState = !ledState;
            digitalWrite(LED_BUILTIN, ledState);
        }
        Serial.println("");
        Serial.print("Connected to WiFi with IP: ");
        Serial.println(WiFi.localIP());
        syncTime();
    }


    void syncTime() {
    boolean ledState = false;
    Serial.print("Syncing time with NTP server ");
    struct tm timeinfo;

    // Set time configuration
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    delay(2000); // Short delay to ensure time is set

    // Wait for a maximum of 10 seconds for successful synchronization
    int retry = 0;
    const int maxRetries = 20;

    while (!getLocalTime(&timeinfo) && retry < maxRetries) {
        Serial.print(".");
        ledState = !ledState;
        digitalWrite(LED_BUILTIN, ledState);
        retry++;
        delay(500);
    }

    if (retry >= maxRetries) {
        Serial.println("\nError: Failed to synchronize time!");
    } else {
        Serial.println("\nTime synchronized successfully.");
        Serial.print("Current time: ");
        Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
        digitalWrite(LED_BUILTIN, HIGH); // Keep LED on when finished
    }
}
};