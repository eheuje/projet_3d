#include <GL/gl.h>
#include <GL/glu.h>
#include "Etage_Factory.h"
#include "../etage.h"
#include "../sdlglutils.h"
#include "../elements_decor/Mur.h"
#include "../elements_decor/Pilier.h"
#include "../elements_decor/fountain.h"
#include "../elements_decor/Escalier.h"
#include "../elements_decor/Guichet.h"
#include "../elements_decor/Table.h"
#include "../elements_decor/Chaise.h"
#include "../elements_interactif/elements_interactif_decor/Pnj.h"
#include "../elements_interactif/elements_interactif_decor/Porte.h"
#include "../elements_interactif/elements_interactif_decor/Button.h"

/**
 * Créer l'espace de stockage dans le vecteur pour 4 étages
 */
EtageFactory::EtageFactory()
{

//	Etage* e = NULL;
//
//	for (int i = 0; i < 5;i++){
//		this->etages.insert( i, e);
//	}

}

/**
 * Permet de Charger les étages et de les créer si ceux-ci ne le sont pas
 */
Etage* EtageFactory::loadEtage(int etage){

	Etage* e;

	if (this->etages.size() == etage){
		e = this->createEtage(etage);
		this->etages.insert(this->etages.begin()+etage,e);
	}else{
		e = this->etages.at(etage);
	}

	return e;
}

/**
 * Créer des étages
 */
Etage* EtageFactory::createEtage(int etage)
{
	int texture_plafond;
	int texture_sol;
	int texture_murs;
	int texture_happy;

	switch(etage)
	{
		case 0 :
		{
			texture_plafond = loadTexture("textures/plafond1.jpg");
			texture_sol = loadTexture("textures/floor.jpg");
			texture_murs = loadTexture("textures/wall.jpg");

			//creation de l'étage
			Etage* cave = new Etage(80,15,80,texture_plafond,texture_sol,texture_murs,0);
			cave->addElementDecor(new Table(0,0,0,0,10,7,2));

			return cave;

		}
		break;

		case 1 :
		{
			//chargement des textures
			int texture_pilier = loadTexture("textures/pilier1.jpg");
			int texture_guichet = loadTexture("textures/wall.jpg");
			texture_plafond = loadTexture("textures/plafond1.jpg");
			texture_sol = loadTexture("textures/carrelage1.jpg");
			texture_murs = loadTexture("textures/mur1.jpg");
			texture_happy = loadTexture("textures/smilet_happy.jpg");

			//creation de l'étage
			Etage* rez_de_chaussee = new Etage(80,15,80,texture_plafond,texture_sol,texture_murs,0);
			
			//ajout des élement de décor dans l'étage
			rez_de_chaussee->addElementDecor(new Pilier(20,0,-40,texture_pilier,2,15));
			rez_de_chaussee->addElementDecor(new Pilier(-20,0,-20,texture_pilier,2,15));
			rez_de_chaussee->addElementDecor(new Pilier(20,0,-20,texture_pilier,2,15));
			rez_de_chaussee->addElementDecor(new Pilier(-20,0,0,texture_pilier,2,15));
			rez_de_chaussee->addElementDecor(new Pilier(-20,0,0,texture_pilier,2,15));
			rez_de_chaussee->addElementDecor(new Pilier(20,0,0,texture_pilier,2,15));
			rez_de_chaussee->addElementDecor(new Pilier(-20,0,20,texture_pilier,2,15));
			rez_de_chaussee->addElementDecor(new Pilier(20,0,20,texture_pilier,2,15));
			rez_de_chaussee->addElementDecor(new Fountain(10.0, 3.0, 10.0));
			rez_de_chaussee->addElementDecor(new Guichet(80,0,30,20,15,10));
			rez_de_chaussee->addElementDecor(new Guichet(80,0,10,20,15,10));
			rez_de_chaussee->addElementDecor(new Guichet(80,0,-10,20,15,10));
			rez_de_chaussee->addElementDecor(new Escalier(70,0,80,70,-20,0));
			rez_de_chaussee->addElementDecor(new Escalier(37,0,80,70,20,0));

			rez_de_chaussee->addElementDecorInteractif(new Pnj(50,0,0,'N',"1"));
			rez_de_chaussee->addElementDecorInteractif(new Pnj(10,0,-10,'S',"2"));
			rez_de_chaussee->addElementDecorInteractif(new Pnj(35,0,-50,'E',"3"));
			rez_de_chaussee->addElementDecorInteractif(new Pnj(40,0,-20,'O',"4"));

			return rez_de_chaussee;
		}

		break;

		case 2 :
		{
			//chargement des textures
			texture_plafond = loadTexture("textures/plafond1.jpg");
			texture_sol = loadTexture("textures/moquette.jpg");
			texture_murs = loadTexture("textures/mur1.jpg");
			int texture_murs_bureau = loadTexture("textures/mur1.jpg");

			//creation de l'étage
			Etage* etage1 = new Etage(80,15,80,texture_plafond,texture_sol,texture_murs,0);
			
			//utilisé pour définir les coordonnées des murs ci-après
			vector<Point> points;

			points.push_back(Point (10,0,40));
			points.push_back(Point (10,0,0));
			Mur *mur1Salle1 = new Mur(80,0,40,points, 15,texture_murs_bureau);
			points.clear();

			points.push_back(Point (10,0,-30));
			points.push_back(Point (80,0,-30));
			Mur *mur2Salle1 = new Mur(10,0,-10,points, 15,texture_murs_bureau);
			points.clear();

			points.push_back(Point (-10,0,40));
			points.push_back(Point (-10,0,0));
			Mur *mur1Salle2 = new Mur(-80,0,40,points, 15,texture_murs_bureau);
			points.clear();

			points.push_back(Point (-10,0,-30));
			points.push_back(Point (-80,0,-30));
			Mur *mur2Salle2 = new Mur(-10,0,-10,points, 15,texture_murs_bureau);
			points.clear();

			etage1->addElementDecor(mur1Salle1);
			etage1->addElementDecor(mur1Salle2);
			etage1->addElementDecor(mur2Salle1);
			etage1->addElementDecor(mur2Salle2);
			etage1->addElementDecor(new Table(50,0,20,0,10,12,5));
			etage1->addElementDecor(new Chaise(52,0,19,0,5,4,3,'S'));
			etage1->addElementDecor(new Chaise(52,0,29,0,5,4,3,'N'));
			etage1->addElementDecor(new Chaise(49,0,26,0,5,4,3,'E'));
			etage1->addElementDecor(new Chaise(60,0,26,0,5,4,3,'W'));

			etage1->addElementDecorInteractif(new Pnj(-50,0,-13,'N',"5"));
			etage1->addElementDecorInteractif(new Pnj(50,0,-10,'E',"6"));
			etage1->addElementDecorInteractif(new Porte(10,0,0,'x',10,15));
			etage1->addElementDecorInteractif(new Porte(-10,0,0,'x',10,15));

			return etage1;

		} 
		break;

		case 3 :
		{

		}
		break;



		default :
		{

		}
		break;
	}

}
	

	

EtageFactory::~EtageFactory()
{

}

