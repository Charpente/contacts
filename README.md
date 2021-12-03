# contacts
Dev logiciel avancé - Base de données de contacts
https://github.com/Charpente/contacts

NGUYEN Ngoc Dang
BURTIN Jean

Au lancement :
Mettre dans la textBox en haut de la fenetre le chemin vers le dossier contenant les fichiers .csv à importer et cliquer sur le bouton "load" pour obtenir la liste de contacts.

Fonctionnement :
Les contacts s'affichent dans la vue à gauche. Il est possible de les selectionner afin d'obtenir leurs informations dans le formulaire de droite. Le formulaire ne permet pas la modification des contacts.

En dessous de la vue se trouve les champs permettant (dans l'ordre de haut en bas) de:
- supprimer les contact ayant un parametre choisi dans la combobox égal à la valeur inscrite dans la textbox
- modifier les contact ayant un parametre choisi dans la combobox égal à la valeur inscrite dans la combobox, en choisissant un autre parametre à affecter une nouvelle valeur
- rechercher un contact ayant un parametre choisi ayant une valeur choisie
- exporter dans un fichier csv les contacts ayant pour parametre choisi la valeur choisie. Le fichier sera crée dans le dossier build de la solution (build-TP../contact)

Ce qui n'a pas été mis en place :
- les threads
- les tests
- les stats
