#include <iostream>
#include <string>
using namespace std;

class SortieAudio {
public:
    virtual void ouvrir() = 0;
    virtual void jouer(const string& son) = 0;
    virtual void fermer() = 0;

    virtual ~SortieAudio() {}
};
class HautParleur : public SortieAudio {
public:
    void ouvrir() override {
        cout << "Haut-parleur ouvert" << endl;
    }

    void jouer(const string& son) override {
        cout << "Haut-parleur joue : " << son << endl;
    }

    void fermer() override {
        cout << "Haut-parleur ferme" << endl;
    }
};
class CasqueBT : public SortieAudio {
public:
    void ouvrir() override {
        cout << "Casque Bluetooth connecte" << endl;
    }

    void jouer(const string& son) override {
        cout << "Casque Bluetooth joue : " << son << endl;
    }

    void fermer() override {
        cout << "Casque Bluetooth deconnecte" << endl;
    }
};
class SortieHDMI : public SortieAudio {
public:
    void ouvrir() override {
        cout << "Sortie HDMI activee" << endl;
    }

    void jouer(const string& son) override {
        cout << "HDMI joue : " << son << endl;
    }

    void fermer() override {
        cout << "Sortie HDMI desactivee" << endl;
    }
};
void tester(SortieAudio* sortie) {
    sortie->ouvrir();
    sortie->jouer("Musique");
    sortie->fermer();
}
int main() {
    SortieAudio* appareils[3];

    appareils[0] = new HautParleur();
    appareils[1] = new CasqueBT();
    appareils[2] = new SortieHDMI();

    for (int i = 0; i < 3; i++) {
        tester(appareils[i]);
        cout << "------------------" << endl;
    }

    for (int i = 0; i < 3; i++) {
        delete appareils[i];
    }

    return 0;
}