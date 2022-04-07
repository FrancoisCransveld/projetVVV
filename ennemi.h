
enum typeEnnemi={voiture,moto,camion,SUV};
typedef enum typeEnnemi TypeEnnemi;
struct ennemi{
  Coordonnee pos;
  int vie;
  TypeEnnemi type;
};
typedef struct ennemi Ennemi;

typedef struct elementEnnemi ElementEnnemi;
struct elementEnnemi{
  Ennemi e;
  ElementEnnemi* suivant;
  ElementEnnemi* precedent;
};

typedef struct listeEnnemi ListeEnnemi;
struct elementEnnemi{
  int nombre;
  ElementEnnemi* premierListe;
};
