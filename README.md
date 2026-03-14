🌱 Smart Farm — Simulation de Ferme Intelligente en C

Application en C pour simuler et gérer une ferme intelligente avec suivi environnemental, gestion des cultures et optimisation énergétique.

##  Fonctionnalités

-  **Gestion des zones** — ajout, affichage et recherche de zones (serres, champs) via liste chaînée
-  **Capteurs environnementaux** — suivi de la température, humidité, pluviométrie et luminosité
-  **Gestion des cultures** — ajout de plantes avec leurs conditions idéales de croissance
-  **Simulation de croissance** — évaluation des conditions pour chaque plante dans sa zone
-  **Bilan énergétique** — suivi de l'énergie produite (solaire) et consommée
-  **Relevés météo** — stockage et recherche des données via arbre binaire de recherche
-  **Règles automatiques** — déclenchement d'actions (irrigation, chauffage, lumière) selon les seuils

---

##  Structures de Données

| Structure | Type | Rôle |
|-----------|------|------|
| `Sensors` | Struct simple | Capteurs environnementaux d'une zone |
| `Plant` | Struct simple | Données d'une plante (nom, temp min/max, humidité idéale) |
| `Zone` | Liste chaînée | Zones de la ferme avec capteurs, plantes et énergie |
| `WeatherNode` | Arbre binaire de recherche | Relevés météorologiques indexés par jour |

---

##  Structure du projet

```
smart-farm-c/
├── projet.c     # Code source complet
└── README.md
```

---

##  Compilation & Exécution

```bash
# Compiler
gcc projet.c -o smart_farm

# Exécuter
./smart_farm
```

> Compatible avec **GCC** sur Linux, macOS et Windows (MinGW).

---

##  Fonctions principales

| Fonction | Rôle |
|----------|------|
| `addZone()` | Ajoute une zone à la liste chaînée |
| `displayZones()` | Affiche toutes les zones et leurs capteurs |
| `searchZone()` | Recherche une zone par nom |
| `applyRules()` | Applique les règles automatiques selon les capteurs |
| `updateEnergy()` | Met à jour le bilan énergétique d'une zone |
| `addPlantToZone()` | Ajoute une plante à une zone |
| `simulateCropGrowth()` | Simule la croissance des cultures |
| `updateSensors()` | Met à jour les capteurs et enregistre un relevé météo |
| `insertWeatherRecord()` | Insère un relevé dans l'arbre binaire |
| `searchWeatherRecord()` | Recherche un relevé météo par jour |
| `displayWeatherRecords()` | Affiche les relevés en ordre croissant (in-order) |

---

##  Stack technique

| Outil | Détail |
|-------|--------|
| Langage | C (C99) |
| Compilateur | GCC |
| Structures | Liste chaînée · Arbre binaire de recherche |
| Mémoire | Allocation dynamique (`malloc`, `realloc`, `free`) |

---
