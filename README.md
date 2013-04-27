## Projet de L2 C++: L'optimisation du planning d'une grande Ecole d'informatique.

Je me suis chargé de la partie Model et Controller tandis que mon binome c'est occupé de la Vue.

### Fonctionnalités
Notre programme tient compte lors de la génération de l'emploi du temps:
- de l'ensemble des salles (plan de l'école) et de leur disponibilité (ou non)
- de l'ensemble des enseignements (cursus)
- de l'ensemble des élèves (promos, groupes), cependant par m�conaissance du syst�me nous ne traitons pas les cas de majeures/mineures.
- de l'ensemble des enseignants et de leur disponibilité (ou non)
- de l'ensemble des contraintes d'agenda (jours travaillés ou non, périodes de vacances)
- Non ubiquité des élèves et enseignants.
- Capacité des différentes salles (nottament des amphis)
Notre interface permet de :
- Saisir les contraintes générales (cursus, salles) ainsi que celles des différents acteurs.
- La présentation de la vue de son planning individuel à chacun des acteurs.

### Options
Nous avons mis en place beaucoups d'efforts à la rédaction d'un code compréhensible, conventionné et facilement débugable, directement via une sortie console.
La gestion de l'interface via des fichiers .ui nous a permis un respect complet du Modèle MVC.
Notre interface respecte le principe du KISS (Keep It Simple Stupid) et met un point d'honneur à la sécurisation des entrées utilisateur.

### Utilisation
Aide intègréé au programme.

### Installation
Un fichier .pro (QtCreator) est fourni avec les sources.
La compilation requiert l'utilisation des parties: core gui et sql de QT
Une Base de Données SQLite (stowe.db) permet de charger directement un exemple de données pour l'emploi du temps, celle-ci doit être placée dans le même répertoire que l'exe.
