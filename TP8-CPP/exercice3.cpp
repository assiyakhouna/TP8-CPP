#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;
class Plugin {
public:
    virtual string nom() const = 0;

    virtual string traiter(const string& texte) = 0;

    virtual ~Plugin() {}

    static unique_ptr<Plugin> creerPlugin(const string& type);
};
class CorrecteurOrthographique : public Plugin {
public:
    string nom() const override {
        return "Correcteur Orthographique";
    }

    string traiter(const string& texte) override {
        string resultat = texte;

        size_t pos = resultat.find("bonjor");

        if (pos != string::npos) {
            resultat.replace(pos, 6, "bonjour");
        }

        return resultat;
    }
};
class TraducteurAnglais : public Plugin {
public:
    string nom() const override {
        return "Traducteur Anglais";
    }

    string traiter(const string& texte) override {
        string resultat = texte;

        size_t pos = resultat.find("bonjour");
        if (pos != string::npos) {
            resultat.replace(pos, 7, "hello");
        }

        pos = resultat.find("merci");
        if (pos != string::npos) {
            resultat.replace(pos, 5, "thank you");
        }

        return resultat;
    }
};
class AnalyseurStyle : public Plugin {
public:
    string nom() const override {
        return "Analyseur de Style";
    }

    string traiter(const string& texte) override {
        int compteur = 0;
        int mots = 0;

        for (char c : texte) {
            if (c == ' ') {
                mots++;
            }

            if (c == '.' || c == '!' || c == '?') {
                if (mots + 1 > 10) {
                    compteur++;
                }
                mots = 0;
            }
        }

        if (mots > 10) {
            compteur++;
        }

        return texte + "\nNombre de phrases longues : "
               + to_string(compteur);
    }
};
unique_ptr<Plugin> Plugin::creerPlugin(const string& type) {

    if (type == "correcteur") {
        return make_unique<CorrecteurOrthographique>();
    }

    if (type == "traducteur") {
        return make_unique<TraducteurAnglais>();
    }

    if (type == "analyseur") {
        return make_unique<AnalyseurStyle>();
    }

    return nullptr;
}

int main() {

    vector<unique_ptr<Plugin>> plugins;

    plugins.push_back(Plugin::creerPlugin("correcteur"));
    plugins.push_back(Plugin::creerPlugin("traducteur"));
    plugins.push_back(Plugin::creerPlugin("analyseur"));
string texte;

cout << "Entrez votre texte : ";
getline(cin, texte);
for (auto& plugin : plugins) {

    if (plugin != nullptr) {
        texte = plugin->traiter(texte);

        cout << "\nPlugin : " << plugin->nom() << endl;
        cout << "Texte apres traitement : " << endl;
        cout << texte << endl;
    }
}
    return 0;
}