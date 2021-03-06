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

	int texture_plafond;
	int texture_murs;
	int texture_sol;

	/**
	 * QUETES
	 */
	vector<bool> quete;
	int nbrQuete;

public:

	vector<ElementDecor*> decor;
	vector<ElementInteractifDecor*> decorInteractif;
	vector<Element*> elements;

	Etage(); // Non implémenté donc inutilisable
	Etage(const Etage &); // Constructeur de copie, non implémenté donc interdit
	Etage(double, double, double, int, int, int, double, int);

	void draw();
	void drawSurface();
	void drawElementsDecor();
	// void drawElevatorDoor();
	void openElevatorDoors();
	void closeElevatorDoors();
	void addElementDecor(ElementDecor*);
	void addElementDecorInteractif(ElementInteractifDecor*);
	void removeElementDecor(ElementDecor*);
	void clearElementsDecor();

	void initElementInteractifDecor();

	double getLargeurEtage() const {
		return largeur_etage;
	}

	double getLongueurEtage() const {
		return longueur_etage;
	}

	vector<ElementDecor*> getDecor() const {
		return decor;
	}

	vector<ElementInteractifDecor*> getDecorInteractif() const {
		return decorInteractif;
	}

	vector<Element*> getElements() const {
		return elements;
	}

	Elevator* getElevator() const {
		return elevator;
	}

	vector<bool> getQuete() const {
		return quete;
	}

	void setQueteValue(int i, bool val){
		this->quete[i] = val;
	}

	/**
	 * DEBUG
	 *
	 */
	void debugQuetes();

};

#endif // ETAGE_H_INCLUDED
