Ce projet est un outil de communication entre un utilisateur et SON robot.
Via le terminal, l'utilisateur est demandé de faire entrer ses commandes qui peuvent être aussi bien urgentes que normales.
Toute commande entrée, sera ajoutée dans la file qui lui correspond selon son niveau de priorité.
Une fois l'utilisateur termine avec l'ajout de ses commandes l'execution commence:
Le programme débute avec la file urgente, avec chaque commande executée on a la nouvelle position du robot ainsi que la vérification d'obstacle à l'aide de la fonction
aléatoire simulation_capteur().
En cas de détection d'obstacle, le programme permet l'utilisateur de saisir une commande de contournement pour éviter cet obstacle.
Une fois la file urgente est vide, on passe  à la file des commandes normales et identiquement aux commandes urgentes on aura la détection des obstacles.
Finalement, toutes les commandes ,que ce soit commande de contournement ou commande sasie dès le début, seront inscrites avec leur détails dans un fichier texte ( les caractéristiques de la commande
ainsi que l'heure et la position du robot suite à cette commande)
Ainsi le programme nous permettra de voir tout l'historique en affichant le contenu du fichier.


