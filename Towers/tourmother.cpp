#include "tourmother.h"

tourMother::tourMother(position tPos): tPos(tPos)
{
   /*

    Definit position selon la ou on a cliquŽ
    Va chercher dans le fichier correspondant a la tour construite:
	   name
	   air
	   buildPrice
	   buildTime
	   speciaux
    Rajoute un event pour le graphic engine affiche la tour

    */

   investment = buildPrice;
}

tourMother::~tourMother()
{
   // rajoute un event "supprime la tour" au graphic truc
   // dis a game_engine de rajouter investment * 0,3 a joueur.money
}

void tourMother::setInvestment(int valueInvested)
{
   investment += valueInvested;
}

void tourMother::upgrade(int upgradeID)
{
   int upgradePrice; // va le chercher ds le fichier nomDeLaTour[upgradeID].up
   /*
    ouvre le ficher juste selon l'ID
    demande a game_engine de verifier que joueur.money >= upgradeCost
	   si(vrai)
		  change:
			 skinID;
			 attack
			 fireTime
			 range
			 speciaux
			 setInvestment(upgradePrice);

	   si(faux)
		  rien
    */

}

/*
 /!\ ATTENTION : definition des fichiers
		 nomDeLaTour.tower:
			name
			air
			buildPrice
			buildTime
			cheminVersLeTilesetDeCetteTour
		nomDeLaTour[upgradeID].up:
		   UpgradePrice
		   IDDuTileDeCetUpgradeDansLeTilesetDeCetteTout
		   AjouteAAttack
		   AjouteAFireTime
		   AjouteARange
		   Speciaux

 */
