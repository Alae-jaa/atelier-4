#include <iostream>
#include <string>
#include <vector>
using namespace std;


// Classe de base : Ressource//

class Ressource {
protected:
    int id;
    string titre;
    string auteur;
    int annee;

public:
    Ressource(int id, string titre, string auteur, int annee)
        : id(id), titre(titre), auteur(auteur), annee(annee) {}

    virtual void afficherInfos() const {
        cout << "ID: " << id << ", Titre: " << titre 
             << ", Auteur: " << auteur << ", Année: " << annee << endl;
    }

    virtual void telecharger() const {
        cout << "Téléchargement générique d'une ressource..." << endl;
    }

    // Surcharge de l'opérateur ==
    bool operator==(const Ressource& r) const {
        return id == r.id;
    }

    // Accesseurs
    string getTitre() const { return titre; }
    string getAuteur() const { return auteur; }
    int getAnnee() const { return annee; }

    virtual ~Ressource() {}
};


// Classe Telechargeable//

class Telechargeable {
public:
    virtual void telecharger() const {
        cout << "Téléchargement d’un contenu téléchargeable..." << endl;
    }

    void afficherMessage() const {
        cout << "Contenu disponible pour téléchargement." << endl;
    }

    virtual ~Telechargeable() {}
};


// Classe Livre

class Livre : public Ressource, public Telechargeable {
    int nbPages;

public:
    Livre(int id, string titre, string auteur, int annee, int nbPages)
        : Ressource(id, titre, auteur, annee), nbPages(nbPages) {}

    void afficherInfos() const override {
        cout << "[Livre] ";
        Ressource::afficherInfos();
        cout << "Nombre de pages: " << nbPages << endl;
    }

    void telecharger() const override {
        cout << "Téléchargement du livre \"" << titre << "\" en format PDF..." << endl;
    }
};


// Classe Magazine//

class Magazine : public Ressource, public Telechargeable {
    int numero;

public:
    Magazine(int id, string titre, string auteur, int annee, int numero)
        : Ressource(id, titre, auteur, annee), numero(numero) {}

    void afficherInfos() const override {
        cout << "[Magazine] ";
        Ressource::afficherInfos();
        cout << "Numéro: " << numero << endl;
    }

    void telecharger() const override {
        cout << "Téléchargement du magazine \"" << titre << "\" en format numérique..." << endl;
    }
};


// Classe Video//

class Video : public Ressource, public Telechargeable {
    double duree; // durée en minutes

public:
    Video(int id, string titre, string auteur, int annee, double duree)
        : Ressource(id, titre, auteur, annee), duree(duree) {}

    void afficherInfos() const override {
        cout << "[Vidéo] ";
        Ressource::afficherInfos();
        cout << "Durée: " << duree << " minutes" << endl;
    }

    void telecharger() const override {
        cout << "Téléchargement de la vidéo \"" << titre << "\" en MP4..." << endl;
    }
};


// Classe Mediatheque//

class Mediatheque {
    vector<Ressource*> ressources;

public:
    void ajouter(Ressource* r) {
        ressources.push_back(r);
    }

    void afficher() const {
        cout << "\n=== Contenu de la Médiathèque ===" << endl;
        for (auto r : ressources)
            r->afficherInfos();
    }

    // Recherche par titre
    void rechercher(string titre) const {
        cout << "\nRecherche par titre : " << titre << endl;
        for (auto r : ressources)
            if (r->getTitre() == titre)
                r->afficherInfos();
    }

    // Recherche par année
    void rechercher(int annee) const {
        cout << "\nRecherche par année : " << annee << endl;
        for (auto r : ressources)
            if (r->getAnnee() == annee)
                r->afficherInfos();
    }

    // Recherche par auteur + année
    void rechercher(string auteur, int annee) const {
        cout << "\nRecherche par auteur et année : " << auteur << ", " << annee << endl;
        for (auto r : ressources)
            if (r->getAuteur() == auteur && r->getAnnee() == annee)
                r->afficherInfos();
    }

    ~Mediatheque() {
        for (auto r : ressources)
            delete r;
    }
};


// Fonction principale//

int main() {
    Mediatheque m;

    // Création de ressources
    Livre* l1 = new Livre(1, "Le Petit Prince", "Saint-Exupéry", 1943, 120);
    Magazine* m1 = new Magazine(2, "Science & Vie", "Equipe Rédaction", 2024, 350);
    Video* v1 = new Video(3, "Inception", "Christopher Nolan", 2010, 148);

    // Ajout à la médiathèque
    m.ajouter(l1);
    m.ajouter(m1);
    m.ajouter(v1);

    // Affichage général
    m.afficher();

    // Test des téléchargements
    cout << "\n=== Test des téléchargements ===" << endl;
    l1->telecharger();
    m1->telecharger();
    v1->telecharger();

    // Test de l'opérateur ==
    cout << "\n=== Test de l'opérateur == ===" << endl;
    cout << ((*l1 == *m1) ? "Même ressource" : "Ressources différentes") << endl;

    // Test des recherches
    cout << "\n=== Test des recherches ===" << endl;
    m.rechercher("Inception");
    m.rechercher(2024);
    m.rechercher("Saint-Exupéry", 1943);

    return 0;
}
