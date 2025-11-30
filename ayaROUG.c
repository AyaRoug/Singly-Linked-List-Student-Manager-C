#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct etudiant{
    char *nom;
    char *prenom;
    float note;
}etudiant;

typedef struct noeud{
    etudiant donnee;
    struct liste *suivant;
}noeud;
noeud *Debut, *Fin;
int Nb_etudiants;

void initialisation () {
    Debut = NULL ;
    Fin = NULL ;
    Nb_etudiants = 0;
}

noeud* AllouerPlacer(char *nom, char *prenom, float note){
    noeud *NOUVEAU=(noeud*)malloc(sizeof(noeud));
        if(NOUVEAU==NULL){
            return NULL;
        }
        // Allocation pour les chaînes de caractères
     NOUVEAU->donnee.nom = (char*)malloc(strlen(nom) + 1);
     NOUVEAU->donnee.prenom = (char*)malloc(strlen(prenom) + 1);
     strcpy(NOUVEAU->donnee.nom,nom);
     strcpy(NOUVEAU->donnee.prenom,prenom);
     NOUVEAU->donnee.note=note;
     NOUVEAU->suivant=NULL;
     return NOUVEAU;
}

void inserer_debut(char *nom, char *prenom, float note) {
    noeud *NOUVEAU = AllouerPlacer(nom, prenom, note);
    if (NOUVEAU == NULL) {
        printf("Erreur d'allocation\n");
        return;
    }
    if (Debut != NULL) {
        NOUVEAU->suivant = Debut;
    } else { // Si la liste était vide, Fin doit aussi pointer sur le nouveau nœud
        Fin = NOUVEAU;
    }
    Debut = NOUVEAU;
    Nb_etudiants++;
}

void inserer_fin(char *nom, char *prenom, float note) {
    noeud *N3 = AllouerPlacer(nom, prenom, note);
    if (N3 == NULL) {
        printf("Erreur d'allocation\n");
        return;
    }
    if (Debut == NULL) { // Liste vide
        Debut = N3;
        Fin = N3;
    } else {
        Fin->suivant = N3;
        Fin = N3;
    }
    Nb_etudiants++;
}

void Liberer(){
    noeud *courant = Debut;
    noeud *suivant;
    while (courant != NULL) {
        suivant = courant->suivant;
        // Libérer les chaînes de caractères
        free(courant->donnee.nom);
        free(courant->donnee.prenom);
        // Libérer le nœud
        free(courant);
        courant = suivant;
    }
    // Réinitialiser les variables globales
    Debut = NULL;
    Fin = NULL;
    Nb_etudiants = 0;
}
/*****************************/
typedef struct {
    noeud *debut_admis;
    noeud *fin_admis;
    noeud *debut_non_admis;
    noeud *fin_non_admis;
    int nb_admis;
    int nb_non_admis;
} Groupes;

Groupes diviserGroupes() {
    Groupes groupes = {NULL, NULL, NULL, NULL, 0, 0};
    noeud *courant = Debut;

    while (courant != NULL) {
        // Créer une copie de l'étudiant
        noeud *nouveau = AllouerPlacer(courant->donnee.nom,courant->donnee.prenom,courant->donnee.note);
        if (nouveau != NULL) {
            if (courant->donnee.note >= 10) {
                // Ajouter aux admis
                if (groupes.debut_admis == NULL) {
                    groupes.debut_admis = nouveau;
                    groupes.fin_admis = nouveau;
                } else {
                    groupes.fin_admis->suivant = nouveau;
                    groupes.fin_admis = nouveau;
                }
                groupes.nb_admis++;
            } else {
                // Ajouter aux non admis
                if (groupes.debut_non_admis == NULL) {
                    groupes.debut_non_admis = nouveau;
                    groupes.fin_non_admis = nouveau;
                } else {
                    groupes.fin_non_admis->suivant = nouveau;
                    groupes.fin_non_admis = nouveau;
                }
                groupes.nb_non_admis++;
            }
        }
        courant = courant->suivant;
    }

    return groupes;
}
/************************/
void afficherGroupe(noeud *debut, char *nom_groupe) {
    noeud *courant = debut;
    int compteur = 0;

    printf("\n=== %s ===\n", nom_groupe);
    printf("-----------------------------------\n");

    while (courant != NULL) {
        compteur++;
        printf("%d. Nom: %s, Prénom: %s, Note: %.2f\n",
               compteur,
               courant->donnee.nom,
               courant->donnee.prenom,
               courant->donnee.note);
        courant = courant->suivant;
    }

    if (compteur == 0) {
        printf("Aucun étudiant dans ce groupe.\n");
    } else {
        printf("Total: %d étudiant(s)\n", compteur);
    }
    printf("-----------------------------------\n");
}
// Fonction pour afficher les deux groupes
void afficherTousGroupes() {
    Groupes groupes = diviserGroupes();

    afficherGroupe(groupes.debut_admis, "ÉTUDIANTS ADMIS (Note >= 10)");
    afficherGroupe(groupes.debut_non_admis, "ÉTUDIANTS NON ADMIS (Note < 10)");

    // Libérer la mémoire des groupes temporaires
    libererGroupe(&groupes.debut_admis);
    libererGroupe(&groupes.debut_non_admis);
}

// Fonction utilitaire pour libérer un groupe
void libererGroupe(noeud **debut) {
    noeud *courant = *debut;
    noeud *suivant;

    while (courant != NULL) {
        suivant = courant->suivant;
        free(courant->donnee.nom);
        free(courant->donnee.prenom);
        free(courant);
        courant = suivant;
    }
    *debut = NULL;
}

// Tri par sélection (simple à implémenter)
void trierAdmisParMerite() {
    Groupes groupes = diviserGroupes();
    noeud *debut_admis = groupes.debut_admis;

    if (debut_admis == NULL || debut_admis->suivant == NULL) {
        printf("Pas assez d'étudiants admis pour trier.\n");
        return;
    }
    // Tri par sélection
    noeud *i, *j, *max;
    etudiant temp;
    for (i = debut_admis; i->suivant != NULL; i = i->suivant) {
        max = i;
        for (j = i->suivant; j != NULL; j = j->suivant) {
            if (j->donnee.note > max->donnee.note) {
                max = j;
            }
        }
        // Échanger les données
        if (max != i) {
            temp = i->donnee;
            i->donnee = max->donnee;
            max->donnee = temp;
        }
    }
    printf("\n=== ÉTUDIANTS ADMIS TRIÉS PAR MÉRITE ===\n");
    printf("-----------------------------------\n");
    noeud *courant = debut_admis;
    int rang = 0;
    while (courant != NULL) {
        rang++;
        printf("%d. %s %s - Note: %.2f\n",
               rang,
               courant->donnee.nom,
               courant->donnee.prenom,
               courant->donnee.note);
        courant = courant->suivant;
    }
    printf("-----------------------------------\n");
    // Libérer la mémoire
    libererGroupe(&debut_admis);
    libererGroupe(&groupes.debut_non_admis);
}

int main()
{
     initialisation();
    // Ajout d'étudiants de test
    inserer_debut("ROUG", "AYA", 16.5);
    inserer_fin("TASSI", "SAAD", 7.0);
    inserer_fin("NAIT", "FATIMA", 16.0);
    inserer_fin("AHMED", "Sophie", 11.5);
    inserer_fin("TASSI", "YASSINE", 8.5);
    inserer_fin("FATI", "AIT", 19.0);
    // Test des fonctions
    afficherTousGroupes();
    trierAdmisParMerite();
    // Libération finale
     Liberer();
    return 0;
}
