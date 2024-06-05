---
layout: default
nav_order: 4
title: Études et choix techniques
---

# Études et choix techniques

<p style="text-align:justify;">Pour réaliser ce projet, nous avons utilisé un capteur DHT11 (capteur d'humidité et de température), deux servomoteurs, une balance et une carte ESP32.
Tous ces éléments nous permettent de récupérer les données de la serre.</p>

<p style="text-align:justify;">Nous devions également récupérer les données de l'environnement dans lequel la serre sera située. Pour ce faire, nous avons décidé d'utiliser les données de l'API OpenWeatherMap pour coupler les données de la serre aux données d'Amiens.</p>

Nous avons installé un serveur Node-RED, un serveur MQTT et un phpMyAdmin sur une VM Ubuntu pour :
* récupérer les données d'OpenWeatherMap,
* communiquer et récupérer les données de notre ESP32,
* avoir un historique des données et un dashboard de la ville d'Amiens,
* avoir un historique des données et un dashboard de la serre
