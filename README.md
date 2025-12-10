# Système de gestion de commandes pour robot

## Description
Ce projet consiste à développer un système de gestion de commandes pour un robot avec priorité des actions.  
Le robot peut exécuter des mouvements normaux et gérer des situations d'urgence comme l'arrêt ou le contournement d'obstacles.

## Fonctionnalités principales
- *Gestion de commandes avec priorité* : deux niveaux de priorité (NORMALE et URGENTE).  
- *Système de double file* : commandes normales et urgentes stockées séparément.  
- *Exécution prioritaire* : les commandes urgentes sont exécutées avant les normales.  
- *Simulation de capteurs* : détection aléatoire d’obstacles et ajout automatique de commandes d’urgence et de contournement.  
- *Journal des événements* : toutes les commandes exécutées sont sauvegardées dans journal_robot.txt avec timestamp et indication d'urgence.  
- *Calcul de position* : mise à jour et affichage de la position du robot après chaque commande.  
- *Tâche supplémentaire* : possibilité de savoir la position du Robot après chaque exécution de commande .Le Robot est initialement à la position (0,0).

## Instructions pour exécuter
1. Ouvrir *Code Blocks*.  
2. Ouvrir le projet Projet-robotique.  
3. Cliquer sur *Run* pour exécuter le programme.  
4. Suivre les instructions à l’écran :  
   - Ajouter des commandes : type, durée, vitesse, priorité  
   - Répondre aux commandes de contournement si un obstacle est détecté  
   - Observer l’exécution des commandes et la position du robot  
   - Vérifier le fichier journal_robot.txt pour l’historique complet

## Exemple de commandes
- Type de mouvement : AVANCER (0), RECULER (1), TOURNER_GAUCHE (2), TOURNER_DROITE (3), ARRET_URGENCE (4)  
- Durée : en secondes (≥ 0)  
- Vitesse : en m/s (≥ 0)  
- Priorité : NORMALE (0) ou URGENTE (1)  

Remarque : ARRET_URGENCE stope immédiatement le robot et vide les files de commandes.Ainsi le Programme s'arrête et le robot reste à la dernière position enregistrée.


