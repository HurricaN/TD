#ifndef TOURMOTHER_H_
#define TOURMOTHER_H_

#include "../common.h"

class tourMother
{
   public:
   tourMother(position tPos = position(0,0));
   virtual ~tourMother();

   void setInvestment(int valueInvested);
   virtual void upgrade(int upgradeID) = 0;


   protected:
   string name;

   int buildPrice;

   float buildTime; // definit le temps de chaque upgarde : upgradeTime = buildTime * arrondiSupperieur(upgradeID / 2))
   position tPos; // Caracteristiques INCHANGEABLES AU COURS DE LA PARTIE

   int skinID;	// Fonctions de l'upgrade
   float fireTime;
   int attack;
   int range;
   bool air;
   int investment; // somme de prix de construction + prix de tous les upgrade -> definit le prix de vente PrixDeVente = investement * 0,3

};

#endif /* TOURMOTHER_H_ */
