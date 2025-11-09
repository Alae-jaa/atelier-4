#include <iostream>
#include <string>
#include <vector>
using namespace std;


// Classe Client//

class Client {
private:
    string nom;
    string CIN;
    int idClient;

public:
    Client(string nom, string CIN, int idClient)
        : nom(nom), CIN(CIN), idClient(idClient) {}

    void afficherInfos() const {
        cout << "Client: " << nom << " | CIN: " << CIN << " | ID: " << idClient << endl;
    }

    string getNom() const { return nom; }

    // La Banque et l’AgentBancaire peuvent accéder à certaines infos privées
    friend class AgentBancaire;
    friend class Banque;
};


// Classe CompteBancaire//

class CompteBancaire {
private:
    string numeroCompte;
    double solde;
    string codeSecret;
    Client* proprietaire; // association avec un client

public:
    CompteBancaire(string numero, double soldeInit, string code, Client* proprietaire)
        : numeroCompte(numero), solde(soldeInit), codeSecret(code), proprietaire(proprietaire) {}

    void deposer(double montant) {
        solde += montant;
        cout << "Dépôt de " << montant << " effectué sur le compte " << numeroCompte << endl;
    }

    void retirer(double montant) {
        if (montant > solde)
            cout << "Solde insuffisant sur le compte " << numeroCompte << endl;
        else {
            solde -= montant;
            cout << "Retrait de " << montant << " effectué sur le compte " << numeroCompte << endl;
        }
    }

    void afficherInfosPubliques() const {
        cout << "Compte N°: " << numeroCompte << " | Solde: " << solde 
             << " | Propriétaire: " << proprietaire->getNom() << endl;
    }

    // Les classes AgentBancaire et Banque peuvent accéder aux infos privées
    friend class AgentBancaire;
    friend class Banque;
};


// Classe AgentBancaire//

class AgentBancaire {
private:
    string nomAgent;
    int idAgent;

public:
    AgentBancaire(string nom, int id) : nomAgent(nom), idAgent(id) {}

    void afficherInfos() const {
        cout << "Agent Bancaire: " << nomAgent << " (ID: " << idAgent << ")" << endl;
    }

    // Accès aux informations confidentielles grâce au friend
    void consulterCodeSecret(const CompteBancaire& c) const {
        cout << "Code secret du compte " << c.numeroCompte << ": [CONFIDENTIEL] " << c.codeSecret << endl;
    }

    // Transfert entre deux comptes
    void effectuerTransfert(CompteBancaire& source, CompteBancaire& destination, double montant) const {
        cout << "Tentative de transfert de " << montant << " DH depuis " << source.numeroCompte
             << " vers " << destination.numeroCompte << "..." << endl;
        if (montant > source.solde) {
            cout << "Échec du transfert : solde insuffisant." << endl;
        } else {
            source.solde -= montant;
            destination.solde += montant;
            cout << "Transfert effectué avec succès !" << endl;
        }
    }
};


// Classe Banque//

class Banque {
private:
    string nomBanque;
    vector<Client*> clients;
    vector<CompteBancaire*> comptes;

public:
    Banque(string nom) : nomBanque(nom) {}

    void ajouterClient(Client* c) {
        clients.push_back(c);
    }

    void ajouterCompte(CompteBancaire* c) {
        comptes.push_back(c);
    }

    void afficherClients() const {
        cout << "\n=== Liste des clients de la banque " << nomBanque << " ===" << endl;
        for (auto c : clients)
            c->afficherInfos();
    }

    void afficherComptes() const {
        cout << "\n=== Liste des comptes bancaires ===" << endl;
        for (auto c : comptes)
            c->afficherInfosPubliques();
    }

    // Rapport interne d’audit
    void afficherRapportAudit() const {
        cout << "\n=== Rapport d'Audit Interne (" << nomBanque << ") ===" << endl;
        for (auto c : comptes) {
            cout << "Compte N°: " << c->numeroCompte
                 << " | Client: " << c->proprietaire->getNom()
                 << " | Solde: " << c->solde
                 << " | Code secret: " << c->codeSecret << endl;
        }
    }

    ~Banque() {
        for (auto c : comptes) delete c;
        for (auto cl : clients) delete cl;
    }
};


// Fonction principale//

int main() {
    // Création de la banque
    Banque b("Banque Centrale");

    // Création de clients
    Client* c1 = new Client("Alae", "CIN12345", 1);
    Client* c2 = new Client("Sara", "CIN67890", 2);

    b.ajouterClient(c1);
    b.ajouterClient(c2);

    // Création de comptes
    CompteBancaire* compte1 = new CompteBancaire("CPT1001", 5000, "1234", c1);
    CompteBancaire* compte2 = new CompteBancaire("CPT2002", 8000, "9999", c2);

    b.ajouterCompte(compte1);
    b.ajouterCompte(compte2);

    // Création d’un agent
    AgentBancaire agent("Karim", 101);
    agent.afficherInfos();

    // Opérations
    compte1->deposer(1500);
    compte2->retirer(1000);

    agent.effectuerTransfert(*compte1, *compte2, 2000);

    // Consultations confidentielles
    cout << "\n=== Consultation confidentielle par l'agent ===" << endl;
    agent.consulterCodeSecret(*compte1);
    agent.consulterCodeSecret(*compte2);

    // Affichages publics
    b.afficherClients();
    b.afficherComptes();

    // Rapport d’audit interne
    b.afficherRapportAudit();

    return 0;
}
