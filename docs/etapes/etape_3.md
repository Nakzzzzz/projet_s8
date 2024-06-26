---
layout: default
title: Réalisation de la partie Software
parent: Etapes de fabrication
nav_order: 1
---

# Réalisation de la partie Software

Cette section décrit la dernière étape du processus de fabrication : la réalisation de la partie Software

## Liste des Matériaux

- capteur de température et d'humidité DHT11
- balance HX711
- d'une réserve à eau
- ppompe à eau DC 3-6V
- carte ESP32
  
## Procédure de Préparation

  1. **Réfléxion / Adaptation** : La première étape est bien sûr la réflexion qui doit être faite autour du code. Quelles actions voulons-nous avoir et en fonction de quoi. Ici, si vous ne changez rien, le servomoteur fonctionnera par défaut lorsqu'il recevra un temps pluvieux depuis OpenWeatherMap
2. **Branchement** : Branchez les capteurs sur les bonnes broches de la carte ESP32, il peut être utile d'utiliser une breadboard pour ce genre de branchement.
3. **Téléversement** : Une fois que tout est bien branché et adapté à votre besoin, vous pouvez téléverser le [code](../../project/PROJETS8FINAL.ino) depuis l'IDE Arduino vers la carte ESP32.
4. **Installation dans la serre** : Une fois que le code a été téléversé, vous pouvez alimenter votre carte et la déposer avec ses capteurs [dans la serre](../images/SCHEMASERRE.jpg)

## Conseils de sécurité du code 

- **Toujours** vérifier le branchement de vos composants électronique pour éviter un potentiel court-circuit.

---
