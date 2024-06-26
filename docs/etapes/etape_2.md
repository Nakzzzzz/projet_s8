---
layout: default
title: Mise en place des serveurs (FI-WARE, MQTT,...)
parent: Etapes de fabrication
nav_order: 2
---

# Mise en place des serveurs (FI-WARE, MQTT,...)

Après la préparation de la maquette, l'étape suivante est la mise en place des serveurs.

C'est ici probablement l'une des étapes majeure pour le bon fonctionnement du projet. La mise en place des serveurs MQTT et FI-WARE etc,...

## Étapes d'Assemblage

1. **Mise en place du serveur MQTT** : Vous allez commencer par la mise en place d'un serveur MQTT qui est primordial ici, il va nous permettre de communiquer avec plusieurs autre serveurs en même temps en faisant office de pierre angulaire du projet.
2. **Mise en place du serveur Node-Red avec FI-WARE** : La prochaine étape est d'implémenter un serveur NodeRed à votre FI-WARE, l'objectif ici est d'ensuite pouvoir intéréagir facilement avec notre carte ESP32 et OpenWeatherMap.
3. **OpenWeatherMap** : Implémentez OpenWeatherMap sur votre serveur Node-Red, cela permettra de récupérer les données météorologique de la ville dans laquelle vous vous trouvez.
4. **Déscendre les données vers la carte ESP32** : Vérifiez que votre carte ESP32 arrive bien à lire les données descendue par votre serveur Node-Red.
5. **Base de données** : Implémentez une BDD de votre choix pour récupérer les infos de la carte ESP32 et de votre serveur Node-Red.

Vous pouvez retrouver un [schéma](../images/poster_grow.jpg) pour mieux comprendre les connexions dans ces connectivités

## Vérifications à Effectuer

- Assurez-vous que toutes les pièces sont correctement alignées.
- Vérifiez la stabilité et la solidité de l'assemblage.

## Problèmes Communs et Solutions

- Si des pièces ne s'emboîtent pas correctement, vérifiez leur alignement et leur dimension
