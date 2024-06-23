#include <WiFi.h>
#include <PubSubClient.h>
#include "DHT.h"
#include "HX711.h"
#include <ESP32Servo.h>

// Remplacez par votre SSID et mot de passe
const char* ssid = "RIOC-TP-IoT";
const char* password = "GRIT-RIOC_2024";

// Adresse de votre serveur MQTT (Node-RED avec Mosquitto)
const char* mqtt_server = "10.19.4.45";

// Pin configuration
#define DHTPIN 4
#define DHTTYPE DHT11
#define DOUT  5  // Broche de données du HX711
#define SCK  18  // Broche de l'horloge du HX711
#define SERVO_PIN 21 // Broche du servomoteur

WiFiClient espClient;
PubSubClient client(espClient);
DHT dht(DHTPIN, DHTTYPE); // Constructeur pour déclarer notre capteur DHT
HX711 scale; // Création d'une instance de la classe HX711
Servo myServo; // Création d'une instance de la classe Servo

float calibration_factor = 1.0; // Facteur de calibration initial
long emptyReading = 0; // Lecture brute sans charge
long weightKnownReading = 0; // Lecture brute avec poids connu
float knownWeight = 0.330; // Poids connu en kg (330g)

String weather = ""; // Variable pour stocker la valeur de la météo

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connexion à ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connecté");
  Serial.println("Adresse IP : ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  payload[length] = '\0'; // Terminer la chaîne de caractères
  String message = String((char*)payload);

  if (String(topic) == "home/weather") {
    weather = message;
    Serial.print("Weather updated to: ");
    Serial.println(weather);

    // Contrôler le servomoteur en fonction de la valeur de weather
    if (weather == "rainy") {
      Serial.println("Weather is rainy, activating servo.");
      myServo.write(180); // Tourner le servo de 180 degrés
      delay(1000); // Attendre 1 seconde pour s'assurer que le servo a terminé son mouvement
    } else {
      Serial.println("Weather is not rainy, deactivating servo.");
      myServo.write(90); // Remettre le servo à 0 degré
      delay(1000); // Attendre 1 seconde pour s'assurer que le servo a terminé son mouvement
    }
  }
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Connexion au serveur MQTT...");
    
    if (client.connect("ESP32Client")) {
      Serial.println("connecté");
      // S'abonner au sujet pour la météo
      client.subscribe("home/weather");
    } else {
      Serial.print("échec, rc=");
      Serial.print(client.state());
      Serial.println(" nouvelle tentative dans 5 secondes");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  
  dht.begin();
  scale.begin(DOUT, SCK); // Initialisation du capteur de poids
  myServo.attach(SERVO_PIN); // Initialisation du servomoteur
  myServo.write(90); // Initialisation à la position neutre

  // Tare à vide pour obtenir une lecture stable
  scale.tare();

  // Lire la valeur brute sans charge
  Serial.println("Mesure de la valeur brute sans charge...");
  delay(2000);
  emptyReading = scale.read();
  Serial.print("Lecture brute sans charge: ");
  Serial.println(emptyReading);

  // Attendre que l'utilisateur place le poids connu sur la balance
  Serial.println("Placez un poids connu de 330g sur la balance.");
  delay(5000); // Attendre 5 secondes pour placer le poids connu

  // Lire la valeur brute avec le poids connu
  weightKnownReading = scale.read();
  Serial.print("Lecture brute avec poids connu: ");
  Serial.println(weightKnownReading);

  // Calculer le facteur de calibration
  calibration_factor = (weightKnownReading - emptyReading) / knownWeight;
  Serial.print("Facteur de calibration calculé: ");
  Serial.println(calibration_factor);
  Serial.println("Capteur de température et humidité DHT11 et capteur de poids HX711 initialisés.");
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Lire les données du capteur DHT11
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);

  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Échec de réception des données du DHT11");
    return;
  }

  Serial.print("Humidité: ");
  Serial.print(h);
  Serial.print("%  Température: ");
  Serial.print(t);
  Serial.print("°C, ");
  Serial.print(f);
  Serial.println("°F");

  // Lire les données du capteur de poids
  if (scale.is_ready()) {
    long reading = scale.read();
    Serial.print("Poids brut: ");
    Serial.println(reading);
    float weight = (reading - emptyReading) / calibration_factor; // Convertir en kilogrammes
    Serial.print("Poids: ");
    Serial.print(weight);
    Serial.println(" kg");

    // Créer une chaîne JSON contenant les valeurs
    String payload = "{\"temperature\": " + String(t) + ", \"humidity\": " + String(h) + ", \"weight\": " + String(weight) + "}";

    // Publier les données sur MQTT
    client.publish("home/sensors", payload.c_str());
  } else {
    Serial.println("HX711 non prêt");
  }
  delay(5000); // Mesurer toutes les 5 secondes
}