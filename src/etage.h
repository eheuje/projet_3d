#ifndef ETAGE_H_INCLUDED
#define ETAGE_H_INCLUDED

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <vector>
#include "elements_decor/Mur.h"
#include "elements/element_decor.h"
#include "elements/element.h"
#include "elements/Element_Interactif_Decor.h"
#include "elements_interactif/elements_interactif_decor/Elevator.h"

using namespace std;

class Etage {

protected:

	double longueur_etage;
	double hauteur_etage;
	double largeur_etage;
	double base;
	Elevator* elevator;

	// vector<ElementDecor*> decor;
	vector<ElementDecor*> decor;
	vector<ElementInteractifDecor*> decorInteractif;

	int texture_plafond;
	int texture_murs;
	int texture_sol;

public:

	vector<Mur*> elevatorDoors;

	Etage(); // Non implémenté donc inutilisable
	Etage(const Etage &); // Constructeur de copie, non implémenté donc interdit
	Etage(double, double, double, int, int, int, double);

	void draw();
	void drawSurface();
	void drawElementsDecor();
	void drawElevatorDoor();
	void openElevatorDoors();
	void closeElevatorDoors();
	void addElementDecor(ElementDecor*);
	void addElementDecorInteractif(ElementInteractifDecor*);
	void removeElementDecor(ElementDecor*);
	void clearElementsDecor();

	double getLargeurEtage() const {
		return largeur_etage;
	}

	double getLongueurEtage() const {
		return longueur_etage;
	}

};

#endif // ETAGE_H_INCLUDED
