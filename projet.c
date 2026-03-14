#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
typedef struct Sensors { 
float temperature; 
float humidity; 
float rainfall; 
int lightIntensity; 
} Sensors; 
typedef struct Plant { 
char name[50]; 
float minTemperature; 
float maxTemperature; 
float idealHumidity; 
} Plant; 
// Structure pour un nœud de l'arbre météorologique 
typedef struct WeatherNode { 
int day; // Jour du relevé 
int rainfall; 
float temperature; 
float humidity; 
int lightIntensity; 
struct WeatherNode *left;  // Sous-arbre gauche (jours précédents) 
struct WeatherNode *right; // Sous-arbre droit (jours suivants) 
} WeatherNode; 
typedef struct Zone { 
char name[50]; 
char type[20]; 
Sensors sensors; 
struct Zone *next; 
float energyProduced; // Energie produite par les panneaux solaires 
float energyConsumed; // Energie consommée par les appareils 
Plant *plants; // Liste des plantes associées à cette zone 
int plantCount; // Nombre de plantes dans la zone 
WeatherNode *weatherTree; // Arbre binaire des relevés météorologiques 
} Zone; 
// Gestion des zones 
 
void addZone(Zone **head, char *name, char *type) { 
    Zone *newZone = (Zone *)malloc(sizeof(Zone)); 
    strcpy(newZone->name, name); 
    strcpy(newZone->type, type); 
 
    // Initialisation des capteurs avec des valeurs par défaut 
    newZone->sensors.temperature = 25.0; 
    newZone->sensors.humidity = 50.0; 
    newZone->sensors.rainfall = 0.0; 
    newZone->sensors.lightIntensity = 1000; 
 
    newZone->energyProduced = 0.0; 
    newZone->energyConsumed = 0.0; 
    newZone->plants = NULL; 
    newZone->plantCount = 0; 
 
    newZone->next = *head; 
    *head = newZone; 
 
    printf("Zone ajoutée : %s (%s)\n", name, type); 
} 
 
 
void displayZones(Zone *head) { 
    if (head == NULL) { 
        printf("Aucune zone n'est disponible.\n"); 
        return; 
    } 
 
    printf("\n=== Liste des zones ===\n"); 
    while (head != NULL) { 
        printf("Zone : %s (%s)\n", head->name, head->type); 
        printf("  Température : %.1f°C\n", head->sensors.temperature); 
        printf("  Humidité : %.1f%%\n", head->sensors.humidity); 
        printf("  Pluie : %.1f mm/h\n", head->sensors.rainfall); 
        printf("  Luminosité : %d lux\n", head->sensors.lightIntensity); 
        printf("  Energie produite : %.1f kWh\n", head->energyProduced); 
        printf("  Energie consommée : %.1f kWh\n", head->energyConsumed); 
         
        if (head->energyProduced < head->energyConsumed) { 
            printf("ALERTE : Manque d'énergie dans la zone %s.\n", head->name); 
        } 
 
        // Affichage des plantes associées à la zone 
        if (head->plantCount > 0) { 
            printf("  Nombre de plantes : %d\n", head->plantCount); 
            for (int i = 0; i < head->plantCount; ++i) { 
                Plant *plant = &head->plants[i]; 
                printf("    Plante : %s\n", plant->name); 
                printf("      Température idéale : %.1f°C - %.1f°C\n", plant
>minTemperature, plant->maxTemperature); 
                printf("      Humidité idéale : %.1f%%\n", plant->idealHumidity); 
            } 
        } else { 
            printf("  Aucune plante dans cette zone.\n"); 
        } 
 
        head = head->next; 
    } 
} 
 
 
 
Zone *searchZone(Zone *head, char *name) { 
    while (head != NULL) { 
        if (strcmp(head->name, name) == 0) { 
            return head; 
        } 
        head = head->next; 
    } 
    return NULL; 
} 
 
void applyRules(Zone *zone) { 
    if (zone == NULL) return; 
 
    if (zone->sensors.temperature > 35.0) { 
        printf("Irrigation activée dans la zone %s.\n", zone->name); 
    } 
    if (zone->sensors.rainfall > 50.0) { 
        printf("Serres fermées dans la zone %s pour protéger les plantes.\n", zone
>name); 
    } 
    if (zone->sensors.humidity > 80.0) { 
        printf("Alerte d'humidité élevée dans la zone %s.\n", zone->name); 
    } 
    if (zone->sensors.temperature < 10.0) { 
        printf("Chauffage activé dans la zone %s.\n", zone->name); 
    } 
    if (zone->sensors.lightIntensity < 300) { 
        printf("Ajustement des panneaux solaires ou éclairage activé dans la zone 
%s.\n", zone->name); 
    } 
 
    // Gestion de l'énergie 
    if (zone->energyProduced < zone->energyConsumed) { 
        printf("Alerte : La zone %s consomme plus d'énergie que celle produite.\n", 
zone->name); 
    } else { 
        printf("Energie suffisante dans la zone %s.\n", zone->name); 
    } 
} 
 
// Gestion de l'énergie 
void updateEnergy(Zone *zone, float energyProduced, float energyConsumed) { 
    if (zone == NULL) { 
        printf("Zone non trouvée.\n"); 
        return; 
    } 
 
    zone->energyProduced = energyProduced; 
    zone->energyConsumed = energyConsumed; 
 
    printf("Energie mise à jour pour la zone %s : %.1f kWh produite, %.1f kWh 
consommée.\n", 
           zone->name, energyProduced, energyConsumed); 
} 
 
// Simulation des cultures 
 
void addPlantToZone(Zone *zone, const char *plantName, float minTemp, float 
maxTemp, float idealHumidity) { 
    if (zone == NULL) { 
        printf("Zone non trouvée.\n"); 
        return; 
    } 
 
    zone->plants = realloc(zone->plants, sizeof(Plant) * (zone->plantCount + 1)); 
    Plant *newPlant = &zone->plants[zone->plantCount++]; 
     
    strcpy(newPlant->name, plantName); 
    newPlant->minTemperature = minTemp; 
    newPlant->maxTemperature = maxTemp; 
    newPlant->idealHumidity = idealHumidity; 
 
    printf("Plante %s ajoutée à la zone %s.\n", plantName, zone->name); 
} 
 
void simulateCropGrowth(Zone *zone) { 
    if (zone == NULL) { 
        printf("Zone non trouvée.\n"); 
        return; 
    } 
 
    printf("Simulation de croissance des cultures dans la zone %s :\n", zone->name); 
    for (int i = 0; i < zone->plantCount; ++i) { 
        Plant *plant = &zone->plants[i]; 
        printf("Plante : %s\n", plant->name); 
         
        if (zone->sensors.temperature < plant->minTemperature || zone
>sensors.temperature > plant->maxTemperature) { 
            printf("  Alerte : Température inadéquate pour %s.\n", plant->name); 
        } else { 
            printf("  Température idéale pour %s.\n", plant->name); 
        } 
 
        if (zone->sensors.humidity != plant->idealHumidity) { 
            printf("  Alerte : Humidité inadéquate pour %s.\n", plant->name); 
        } else { 
            printf("  Humidité idéale pour %s.\n", plant->name); 
        } 
    } 
} 
 
// Insérer un relevé météorologique dans l'arbre 
WeatherNode *insertWeatherRecord(WeatherNode *root, int day, float temperature, 
float humidity, int lightIntensity, int rain ) { 
    if (root == NULL) { 
        WeatherNode *newNode = (WeatherNode *)malloc(sizeof(WeatherNode)); 
        newNode->day = day; 
        newNode->temperature = temperature; 
        newNode->humidity = humidity; 
        newNode->lightIntensity = lightIntensity; 
        newNode->rainfall= rain; 
        newNode->left = newNode->right = NULL; 
        return newNode; 
    } 
 
    if (day < root->day) { 
        root->left = insertWeatherRecord(root->left, day, temperature, humidity, 
lightIntensity, rain); 
    } else if (day > root->day) { 
        root->right = insertWeatherRecord(root->right, day, temperature, humidity, 
lightIntensity , rain); 
    } else { 
        // Si le jour existe déjà, on met à jour les valeurs 
        root->temperature = temperature; 
        root->humidity = humidity; 
        root->lightIntensity = lightIntensity; 
        root->rainfall=rain; 
    } 
    return root; 
} 
 
// Afficher les relevés météorologiques (in-order : du plus ancien au plus récent) 
void displayWeatherRecords(WeatherNode *root) { 
    if (root == NULL) return; 
 
    displayWeatherRecords(root->left); 
    printf("Jour %d : Température: %.1f°C, Humidité: %.1f%%, Lumière: %d lux , pluie 
: %d \n", 
           root->day, root->temperature, root->humidity, root->lightIntensity ,root
>rainfall); 
    displayWeatherRecords(root->right); 
} 
 
 
// Rechercher un relevé météorologique par jour 
WeatherNode *searchWeatherRecord(WeatherNode *root, int day) { 
    if (root == NULL || root->day == day) return root; 
 
    if (day < root->day) return searchWeatherRecord(root->left, day); 
    return searchWeatherRecord(root->right, day); 
} 
 
 
void updateSensors(Zone *zone, float temperature, float humidity, float rainfall, int 
lightIntensity, int day) { 
    if (zone == NULL) { 
        printf("Zone non trouvée.\n"); 
        return; 
    } 
 
    // Mise à jour des capteurs 
    zone->sensors.temperature = temperature; 
    zone->sensors.humidity = humidity; 
    zone->sensors.rainfall = rainfall; 
    zone->sensors.lightIntensity = lightIntensity; 
 
    // Enregistrer dans l'arbre météo 
    zone->weatherTree = insertWeatherRecord(zone->weatherTree, day, 
temperature, humidity, lightIntensity , rainfall); 
 
    printf("Capteurs mis à jour et enregistrés pour la zone %s (Jour %d).\n", zone
>name, day); 
} 
 
// Programme principal 
 
int main(void) { 
    Zone *farm = NULL; 
    int choice; 
    char name[50], type[20]; 
    float temp, humidity, rainfall, energyProduced, energyConsumed; 
    int light; 
     
    // Ajouter des zones manuellement 
    do { 
        printf("\n=== Menu ===\n"); 
        printf("1. Ajouter une zone\n"); 
        printf("2. Mettre à jour les capteurs\n"); 
        printf("3. Appliquer les règles automatiques\n"); 
        printf("4. Afficher toutes les zones\n"); 
        printf("5. Mettre à jour l'énergie\n"); 
        printf("6. Ajouter une plante à une zone\n"); 
        printf("7. Simuler la croissance des cultures\n"); 
        printf("8. Ajouter un relevé météo\n"); 
        printf("9. Afficher les relevés météo d'une zone\n"); 
        printf("10. Rechercher un relevé météo par jour\n"); 
        printf("11. Quitter\n"); 
        printf("Choix : "); 
        scanf("%d", &choice); 
        getchar(); // Consomme le caractère '\n' 
         
        switch (choice) { 
            case 1: 
                printf("Nom de la zone : "); 
                fgets(name, sizeof(name), stdin); 
                name[strcspn(name, "\n")] = '\0'; 
                printf("Type de la zone (Serre/Champ/Réservoir) : "); 
                fgets(type, sizeof(type), stdin); 
                type[strcspn(type, "\n")] = '\0'; 
                addZone(&farm, name, type); 
                break; 
                 
            case 2: 
                printf("Nom de la zone à mettre à jour : "); 
                fgets(name, sizeof(name), stdin); 
                name[strcspn(name, "\n")] = '\0'; 
                Zone *zone = searchZone(farm, name); 
                if (zone) { 
                    int day; 
                    printf("Jour du relevé : "); 
                    scanf("%d", &day); 
                    printf("Nouvelle température (°C) : "); 
                    scanf("%f", &temp); 
                    printf("Nouvelle humidité (%%) : "); 
                    scanf("%f", &humidity); 
                    printf("Nouvelle pluie (mm/h) : "); 
                    scanf("%f", &rainfall); 
                    printf("Nouvelle luminosité (lux) : "); 
                    scanf("%d", &light); 
                    updateSensors(zone, temp, humidity, rainfall, light,day); 
                } else { 
                    printf("Zone non trouvée.\n"); 
                } 
                break; 
                 
            case 3: 
                printf("Application des règles...\n"); 
                Zone *current = farm; 
                while (current != NULL) { 
                    applyRules(current); 
                    current = current->next; 
                } 
                break; 
                 
            case 4: 
                displayZones(farm); 
                break; 
                 
                 
            case 5: 
                printf("Nom de la zone : "); 
                fgets(name, sizeof(name), stdin); 
                name[strcspn(name, "\n")] = '\0'; 
                Zone *zoneToUpdate = searchZone(farm, name); 
                if (zoneToUpdate) { 
                    printf("Energie produite (kWh) : "); 
                    scanf("%f", &energyProduced); 
                    printf("Energie consommée (kWh) : "); 
                    scanf("%f", &energyConsumed); 
                    updateEnergy(zoneToUpdate, energyProduced, energyConsumed); 
                } else { 
                    printf("Zone non trouvée.\n"); 
                } 
                break; 
                 
            case 6: 
                printf("Nom de la zone : "); 
                fgets(name, sizeof(name), stdin); 
                name[strcspn(name, "\n")] = '\0'; 
                Zone *zoneForPlant = searchZone(farm, name); 
                if (zoneForPlant) { 
                    char plantName[50]; 
                    float minTemp, maxTemp, idealHumidity; 
                    printf("Nom de la plante : "); 
                    fgets(plantName, sizeof(plantName), stdin); 
                    plantName[strcspn(plantName, "\n")] = '\0'; 
                    printf("Température min de la plante (°C) : "); 
                    scanf("%f", &minTemp); 
                    printf("Température max de la plante (°C) : "); 
                    scanf("%f", &maxTemp); 
                    printf("Humidité idéale de la plante (%%) : "); 
                    scanf("%f", &idealHumidity); 
                    addPlantToZone(zoneForPlant, plantName, minTemp, maxTemp, 
idealHumidity); 
                } else { 
                    printf("Zone non trouvée.\n"); 
                } 
                break; 
                 
            case 7: 
                printf("Nom de la zone pour la simulation : "); 
                fgets(name, sizeof(name), stdin); 
                name[strcspn(name, "\n")] = '\0'; 
                Zone *zoneForSimulation = searchZone(farm, name); 
                if (zoneForSimulation) { 
                    simulateCropGrowth(zoneForSimulation); 
                } else { 
                    printf("Zone non trouvée.\n"); 
                } 
                break; 
                 
            case 8: 
                printf("Nom de la zone : "); 
                fgets(name, sizeof(name), stdin); 
                name[strcspn(name, "\n")] = '\0'; 
                Zone *zoneForWeather = searchZone(farm, name); 
                if (zoneForWeather) { 
                    int day; 
                    printf("Jour du relevé : "); 
                    scanf("%d", &day); 
                    printf("Température (°C) : "); 
                    scanf("%f", &temp); 
                    printf("Humidité (%%) : "); 
                    scanf("%f", &humidity); 
                    printf("Luminosité (lux) : "); 
                    scanf("%d", &light); 
                    printf("Pluie (mm) : "); 
                    scanf("%f", &rainfall); 
                    updateSensors(zoneForWeather, temp, humidity, rainfall, light, day); 
                } else { 
                    printf("Zone non trouvée.\n"); 
                } 
                break; 
 
            case 9: 
                printf("Nom de la zone : "); 
                fgets(name, sizeof(name), stdin); 
                name[strcspn(name, "\n")] = '\0'; 
                Zone *zoneForDisplay = searchZone(farm, name); 
                if (zoneForDisplay) { 
                    printf("Relevés météorologiques pour la zone %s :\n", zoneForDisplay
>name); 
                    displayWeatherRecords(zoneForDisplay->weatherTree); 
                } else { 
                    printf("Zone non trouvée.\n"); 
                } 
                break; 
 
 
            case 10: 
                printf("Nom de la zone : "); 
                fgets(name, sizeof(name), stdin); 
                name[strcspn(name, "\n")] = '\0'; 
                Zone *zoneForSearch = searchZone(farm, name); 
                if (zoneForSearch) { 
                    int day; 
                    printf("Jour à rechercher : "); 
                    scanf("%d", &day); 
                    WeatherNode *result = searchWeatherRecord(zoneForSearch
>weatherTree, day); 
                    if (result) { 
                        printf("Jour %d : Température: %.1f°C, Humidité: %.1f%%, Lumière: 
%d lux\n", 
                               result->day, result->temperature, result->humidity, result
>lightIntensity); 
                    } else { 
                        printf("Aucun relevé trouvé pour le jour %d.\n", day); 
                    } 
                } else { 
                    printf("Zone non trouvée.\n"); 
                } 
                break; 
 
            case 11: 
                printf("Programme terminé.\n"); 
                break; 
default: 
printf("Choix invalide. Réessayez.\n"); 
} 
} while (choice != 12); 
return 0; 
}
