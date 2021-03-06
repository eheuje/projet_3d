#include "freeflycamera.h"

#include <cmath>
#include <GL/glu.h>

FreeFlyCamera::FreeFlyCamera(const Vector3D & position) {
	_position = position;
	_phi = 0;
	_theta = 0;
	VectorsFromAngles();

	_speed = 0.04;
	_sensivity = 0.2;
	_verticalMotionActive = false;
	_keyconf["forward"] = SDLK_z;
	_keyconf["backward"] = SDLK_s;
	_keyconf["strafe_left"] = SDLK_q;
	_keyconf["strafe_right"] = SDLK_d;
	_keyconf["boost"] = SDLK_LSHIFT;
	_keystates[_keyconf["forward"]] = false;
	_keystates[_keyconf["backward"]] = false;
	_keystates[_keyconf["strafe_left"]] = false;
	_keystates[_keyconf["strafe_right"]] = false;
	_keystates[_keyconf["boost"]] = false;

	SDL_WM_GrabInput (SDL_GRAB_ON);
	SDL_ShowCursor (SDL_DISABLE);
}

void FreeFlyCamera::OnMouseMotion(const SDL_MouseMotionEvent & event) {

	_theta -= event.xrel * _sensivity;
	_phi -= event.yrel * _sensivity;
	VectorsFromAngles();
}

void FreeFlyCamera::OnMouseButton(const SDL_MouseButtonEvent & event) {
	if ((event.button == SDL_BUTTON_WHEELUP)
			&& (event.type == SDL_MOUSEBUTTONDOWN)) //coup de molette vers le haut
			{
		_verticalMotionActive = true;
		_timeBeforeStoppingVerticalMotion = 250;
		_verticalMotionDirection = 1;

	} else if ((event.button == SDL_BUTTON_WHEELDOWN)
			&& (event.type == SDL_MOUSEBUTTONDOWN)) //coup de molette vers le bas
			{
		_verticalMotionActive = true;
		_timeBeforeStoppingVerticalMotion = 250;
		_verticalMotionDirection = -1;
	}
}

void FreeFlyCamera::OnKeyboard(const SDL_KeyboardEvent & event) {
	for (KeyStates::iterator it = _keystates.begin(); it != _keystates.end();
			it++) {
		if (event.keysym.sym == it->first) {
			it->second = (event.type == SDL_KEYDOWN);
			break;
		}
	}
}

void FreeFlyCamera::animate(Uint32 timestep) {

	double realspeed = (_keystates[_keyconf["boost"]]) ? 10 * _speed : _speed;
	if (_keystates[_keyconf["forward"]]) {

		//Gestion des collision sur les murs principaux
		if(-this->_currentStare->getLongueurEtage()+1 < _target.X
		&& _target.X < this->_currentStare->getLongueurEtage()-1 && !_collisionTab[0])
			_position.X += _forward.X * (realspeed * timestep);

		if(-this->_currentStare->getLargeurEtage()+1 < _target.Z
		&& _target.Z < this->_currentStare->getLargeurEtage()-1 && !_collisionTab[1])
			_position.Z += _forward.Z * (realspeed * timestep);
	}
	if (_keystates[_keyconf["backward"]]){

		//Gestion des collision sur les murs principaux
		if(-this->_currentStare->getLongueurEtage()+1< _position.X-_forward.X
		&& _position.X-_forward.X < this->_currentStare->getLongueurEtage()-1 && !_collisionTab[2])
			_position.X -= _forward.X * (realspeed * timestep);
		if(-this->_currentStare->getLargeurEtage()+1 < _position.Z-_forward.Z
		&& _position.Z-_forward.Z < this->_currentStare->getLargeurEtage()-1 && !_collisionTab[3])
			_position.Z -= _forward.Z * (realspeed * timestep);
	}
	if (_keystates[_keyconf["strafe_left"]]){

		//Gestion des collision sur les murs principaux
		if(-this->_currentStare->getLongueurEtage()+3< _position.X+_forward.X*sin(90*M_PI/180)
		&& _position.X+_forward.X*sin(90*M_PI/180) < this->_currentStare->getLongueurEtage()-3 && !_collisionTab[4])
		_position.X += _left.X * (realspeed * timestep);
		if(-this->_currentStare->getLargeurEtage()+3 < _position.Z+_forward.Z*cos(90*M_PI/180)
		&& _position.Z+_forward.Z*cos(90*M_PI/180) < this->_currentStare->getLargeurEtage()-3 && !_collisionTab[5])
		_position.Z += _left.Z * (realspeed * timestep);
	}
	if (_keystates[_keyconf["strafe_right"]]){

		//Gestion des collision sur les murs principaux
		if(-this->_currentStare->getLongueurEtage()+3< _position.X+_forward.X*sin(-90*M_PI/180)
		&& _position.X+_forward.X*sin(-90*M_PI/180) < this->_currentStare->getLongueurEtage()-3 && !_collisionTab[6])
		_position.X -= _left.X * (realspeed * timestep);
		if(-this->_currentStare->getLargeurEtage()+3 < _position.Z+_forward.Z*cos(-90*M_PI/180)
		&& _position.Z+_forward.Z*cos(-90*M_PI/180) < this->_currentStare->getLargeurEtage()-3 && !_collisionTab[7])
		_position.Z -= _left.Z * (realspeed * timestep);
	}
	if (_verticalMotionActive) {
		if (timestep > _timeBeforeStoppingVerticalMotion)
			_verticalMotionActive = false;
		else
			_timeBeforeStoppingVerticalMotion -= timestep;
		_position += Vector3D(0, 0,
				_verticalMotionDirection * realspeed * timestep);
	}
	_target = _position + _forward;

	_collisionTab = NULL;

}

void FreeFlyCamera::setSpeed(double speed) {
	_speed = speed;
}

void FreeFlyCamera::setSensivity(double sensivity) {
	_sensivity = sensivity;
}

void FreeFlyCamera::setPosition(const Vector3D & position) {
	_position = position;
	_target = _position + _forward;
}

void FreeFlyCamera::VectorsFromAngles() {
	static const Vector3D up(0, 1, 0);
	if (_phi > 89)
		_phi = 89;
	else if (_phi < -89)
		_phi = -89;
	double r_temp = cos(_phi * M_PI / 180);
	_forward.Y = sin(_phi * M_PI / 180);
	_forward.Z = r_temp * cos(_theta * M_PI / 180);
	_forward.X = r_temp * sin(_theta * M_PI / 180);

	_left = up.crossProduct(_forward);
	_left.normalize();

	_target = _position + _forward;
}

void FreeFlyCamera::look() {
	gluLookAt(_position.X, _position.Y, _position.Z, _target.X, _target.Y,
			_target.Z, 0, 1, 0);
}

FreeFlyCamera::~FreeFlyCamera() {
	SDL_WM_GrabInput (SDL_GRAB_OFF);
	SDL_ShowCursor (SDL_ENABLE);
}
