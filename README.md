# Singly-Linked-List-Student-Manager-C

## 📝 Description du Projet (Project Description)

Ce projet est une implémentation en langage *C* d'une *Liste Simplement Chaînée (LSC)* pour la gestion des informations des étudiants dans une classe. Chaque nœud de la liste représente un étudiant avec son *nom*, *prénom*, et une *note* (float).

L'objectif est de mettre en œuvre les fonctions fondamentales des listes chaînées pour manipuler ces données.

## 🛠️ Structures de Données et Fonctions Implémentées

### 1. Structure de Données Globale

La gestion de la liste s'appuie sur les éléments suivants :

```c
// Structure du Nœud
typedef struct Etudiant {
    char nom[50];
    char prenom[50];
    float note;
    struct Etudiant *suivant; // Pointeur vers le nœud suivant
} Etudiant;

// Structure de Contrôle de la Liste
typedef struct {
    Etudiant *Debut; // Pointeur vers le premier élément
    Etudiant *Fin;   // Pointeur vers le dernier élément (pour une insertion rapide à la fin)
    int Nb_etudiants; // Nombre total d'étudiants
} ListeEtudiants;
