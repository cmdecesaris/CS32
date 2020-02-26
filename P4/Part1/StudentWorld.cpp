#include "StudentWorld.h"
#include <string>
using namespace std;

GameWorld* createStudentWorld(string assetDir)
{
	return new StudentWorld(assetDir);
}

// Students:  Add code to this file (if you wish), StudentWorld.h, Actor.h and Actor.cpp
StudentWorld::~StudentWorld() {
	cleanUp();  //function should destory dynamically aloocated memory
}



bool StudentWorld::personCanMove(int x, int y, bool canMoveEarth) const { //in implementation canMoveEarth is true for the tunnelman person only, false for protestors
	//boundary
	if (x < 0 || x>56 || y > 60 || y < 0) {
		return false;
	}
	for (size_t i = 0; i < m_actors.size(); i++) {
		//Ensure that actor is within radius of 3 of spot being examined
		

		
		if (withinRad(m_actors[i]->getX(), m_actors[i]->getY(), x, y, 2)) {
			if (m_actors[i]->blocksMove())
				return false;
		} 
	}
	return true;

}
bool StudentWorld::atEarth(int x, int y) {

	//loop throguh all earth till val we want, if its null pass over it
	for (int i = 0; i < 60; i++) {
		for (int j = 0; j < 60; j++) {
			if (m_earth[i][j] == nullptr) {
				continue;
			}
			if (m_earth[i][j]->getX() == x && m_earth[i][j]->getY() == y) {
				return true;
			}
			
		}
	}
	return false; //indicates that the  spot is not dirt


} //determin e if the current cords are on earth object

void StudentWorld::addBarrel(int amt) {
	m_oilbarrels = m_oilbarrels +amt;
}
bool StudentWorld::removeEarth(int x, int y) {
	//same loop through earth for loop, skip over null but destroy the target it not null
	for (int i = 0; i < 60; i++) {
		for (int j = 0; j < 60; j++) {
			if (m_earth[i][j] == nullptr) {
				continue;
			}
			if (m_earth[i][j]->getX() == x && m_earth[i][j]->getY() == y) {
				delete m_earth[i][j];
				m_earth[i][j]=nullptr;
				return true;
			}

		}
	}
	return false;
}
void StudentWorld::giveSonar(int num) {
	int sonars = m_tunnelman->getSonars();
	m_tunnelman->setSonar(sonars + num);
} 

void StudentWorld::giveGoldTunnelman(int num, TunnelMan* a) {
	int gold = a->getGold();
	a->setGold(gold + num);
}
/*(int i = 30; i <= 33; i++) { //place in mine shaft by deleting dirt
			for (int k = 4; k <= 59; k++) */
int StudentWorld::randIntGeneratorX() {
	
	return (rand() % 56 );
}
int StudentWorld::randIntGeneratorY() {
	return (rand() % 60 -2 );
}
void StudentWorld::addActor(Actor* a) {
	m_actors.push_back(a);
}
bool StudentWorld::isDead(Actor* ptr) { //will delete this actor,
	if (ptr->isAlive() == false) {
		
		delete ptr;
		return true;
	}
	return false;

}
Actor* StudentWorld::getActor(int x, int y) {
//	//TODO STL iteration through m_actors vector, find the indicated one at that pos and return it
//	return;
	for (size_t i = 0; i < m_actors.size(); i++) {
		if (m_actors[i]->getX() == x && m_actors[i]->getY() == y) {
			return m_actors[i]; //ptr to actor will be returned
		}
	}
	return nullptr; //if none is found

} //returns a pointer to the acctor at those points

void StudentWorld::tunnelManUseSonar(TunnelMan* man) {
	int man_x = man->getX();
	int man_y = man->getY();
	//for every actor find if they are in the 12 unit distance of tunnel man if yes, make visuleb
	for (size_t i = 0; i < m_actors.size(); i++) {
		int act_x = m_actors[i]->getX();
		int act_y = m_actors[i]->getY();
		double phyphag_square = (act_x - man_x) * (act_x - man_x) + (act_y - man_y) * (act_y - man_y);
		double dist = (double)sqrt((double)phyphag_square);
		if (dist <= 12.00) {
			m_actors[i]->setVisible(true); //make it visible 
			//TODO: CODE IN THE KEY FOR USING SONAR in TUNNELMANCLASS
		}
	}
}
bool StudentWorld::withinRad(int x1, int y1, int x2, int y2, int rad)const {
	double phyphag_square =(double) ((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
	double dist = (double)sqrt((double)phyphag_square);

	if (dist <= (double)rad) {
		return true;
	}
	return false;
}
TunnelMan* StudentWorld::findTunnelMan(Actor* act, int rad) const {
	int act_x = act->getX();
	int act_y = act->getY();

	int tun_x = m_tunnelman->getX();
	int tun_y = m_tunnelman->getY();
	//math functions
	double distSqa = (double)((act_x - tun_x) * (act_x - tun_x)) + ((act_y - tun_y) * (act_y - tun_y));
	double dist = sqrt(distSqa);

	if (dist <= (double)rad) { //if tunnel man is in proximity to item
		return m_tunnelman;
	}

	return nullptr; //if we don't find tunnelman 
}

