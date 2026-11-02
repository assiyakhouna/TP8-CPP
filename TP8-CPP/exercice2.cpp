#include <iostream>
#include <vector>
#include <memory>
using namespace std;
struct Vec3 {
    float x;
    float y;
    float z;
};
class Lumiere {
public:
    virtual float intensite(const Vec3& position) = 0;

    virtual ~Lumiere() {}
};
class LumiereDirectionnelle : public Lumiere {
private:
    Vec3 direction;
    Vec3 couleur;

public:
    LumiereDirectionnelle(Vec3 d, Vec3 c) {
        direction = d;
        couleur = c;
    }

    float intensite(const Vec3& position) override {
        return 1.0;
    }
};
class LumierePonctuelle : public Lumiere {
private:
    Vec3 position;
    float attenuation;

public:
    LumierePonctuelle(Vec3 p, float a) {
        position = p;
        attenuation = a;
    }

    float intensite(const Vec3& point) override {
        return 1.0 / (1.0 + attenuation);
    }
};
class LumiereSpot : public Lumiere {
private:
    Vec3 position;
    Vec3 direction;
    float angleOuverture;

public:
    LumiereSpot(Vec3 p, Vec3 d, float angle) {
        position = p;
        direction = d;
        angleOuverture = angle;
    }

    float intensite(const Vec3& point) override {
        return 1.0;
    }
};
vector<unique_ptr<Lumiere>> lumieres;
float calculerEclairage(const Vec3& point) {
    float total = 0.0;

    for (const auto& lumiere : lumieres) {
        total += lumiere->intensite(point);
    }

    return total;
}
int main() {
// Creation des lumieres
lumieres.push_back(make_unique<LumiereDirectionnelle>(
    Vec3{1, 0, 0}, Vec3{1, 1, 1}
));

lumieres.push_back(make_unique<LumierePonctuelle>(
    Vec3{2, 3, 4}, 0.5
));

lumieres.push_back(make_unique<LumiereSpot>(
    Vec3{0, 0, 5}, Vec3{0, 0, -1}, 45
));
// Tester plusieurs points
Vec3 points[] = {
    {1, 2, 3},
    {4, 5, 6},
    {2, 3, 1}
};

// Afficher les resultats
for (int i = 0; i < 3; i++) {
    float resultat = calculerEclairage(points[i]);

    cout << "Eclairage du point " << i + 1
         << " : " << resultat << endl;
}
    return 0;
}