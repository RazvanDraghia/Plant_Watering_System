#include<Wifi.h>
#include<Firebase_ESP_Client.h>
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"

#define WIFI_SSID "TP-Link_2B94_5G"
#define WIFI_PASSWORD "05167470"
#define API_KEY "AIzaSyCDEiDgxfSdy7Rglhv5zI-NxdAkC2xNTLU"
#define DATABASE_URL "https://plant-watering-system-8b102-default-rtdb.europe-west1.firebasedatabase.app/"
#define MOISTURE_SENSOR_PIN 34    // Pinul analogic pentru senzorul de umiditate
#define RELAY_PIN 27              // Pinul digital pentru controlul releului
#define MOISTURE_THRESHOLD 500    // Pragul de umiditate (ajustabil după testare)

FirebaseData firebaseData;

void setup() {
    Serial.begin(115200);

    // Conectare la WiFi
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Conectare la WiFi...");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nConectat la WiFi!");

    // Inițializare Firebase (opțional)
    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
    Firebase.reconnectWiFi(true);

    // Configurare pin releu ca OUTPUT
    pinMode(RELAY_PIN, OUTPUT);
    digitalWrite(RELAY_PIN, HIGH); // Inițial, pompa este oprită (releu pe HIGH)
}

void loop() {
    // Citim nivelul de umiditate de la senzor
    int moistureLevel = analogRead(MOISTURE_SENSOR_PIN);
    Serial.print("Nivelul de umiditate citit: ");
    Serial.println(moistureLevel);

    // Dacă umiditatea este sub prag, activăm pompa
    if (moistureLevel < MOISTURE_THRESHOLD) {
        digitalWrite(RELAY_PIN, LOW); // Activăm releul (pompa pornită)
        Serial.println("Solul este uscat. Activăm pompa de apă!");

        // Opțional: Trimitere date în Firebase
        if (Firebase.setInt(firebaseData, "/moisture", moistureLevel) &&
            Firebase.setBool(firebaseData, "/pumpStatus", true)) {
            Serial.println("Date trimise cu succes către Firebase.");
        } else {
            Serial.print("Eroare la trimiterea datelor: ");
            Serial.println(firebaseData.errorReason());
        }
    } else {
        // Dacă solul este umed, oprim pompa
        digitalWrite(RELAY_PIN, HIGH); // Dezactivăm releul (pompa oprită)
        Serial.println("Solul este suficient de umed. Pompa este oprită.");

        // Opțional: Trimitere date în Firebase
        if (Firebase.setInt(firebaseData, "/moisture", moistureLevel) &&
            Firebase.setBool(firebaseData, "/pumpStatus", false)) {
            Serial.println("Date trimise cu succes către Firebase.");
        } else {
            Serial.print("Eroare la trimiterea datelor: ");
            Serial.println(firebaseData.errorReason());
        }
    }

    delay(10000); // Așteaptă 10 secunde înainte de următoarea citire
}