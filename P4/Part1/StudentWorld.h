#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include <string>
#include <vector>
#include "Actor.h"
#include<algorithm>
#include<cstdlib>

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
	StudentWorld(std::string assetDir)
		: GameWorld(assetDir)
	{
	}
	~StudentWorld();
	virtual int init()
	{
		/*(int i = 30; i <= 33; i++) { //place in mine shaft by deleting dirt
			for (int k = 4; k <= 59; k++) */
		int numBoulders = std::min((int)(getLevel() / 2 + 2), 9);
		for (int i = 0; i < numBoulders; i++) {
			int x = randIntGeneratorX();
			int y = randIntGeneratorY();
			while ((x > 26 && x <= 33) && (y >= 4 && y < 60)) { //no spawining in the shaft
				x = randIntGeneratorX();
				y = randIntGeneratorY();
			}
			m_actors.push_back(new Boulder(x, y, this));

		}
		int numOilbarrels = std::min((int)(getLevel()  + 2), 21);
		for (int i = 0; i < numOilbarrels; i++) {
			int x = randIntGeneratorX();
			int y = randIntGeneratorY();
			while ((x >= 27 && x <= 33) && (y >= 4 && y < 60)) { //no spawining in the shaft
				x = randIntGeneratorX();
				y = randIntGeneratorY();
			}

			m_actors.push_back(new OilBarrel(x, y, this));

		}
		int numGold = std::min((int)(5-getLevel()/2), 2);
		for (int i = 0; i < numGold; i++) {
			int x = randIntGeneratorX();
			int y = randIntGeneratorY();
			while ((x >= 27 && x <= 33) && (y >=4 && y < 60)) { //no spawining in the shaft
				x = randIntGeneratorX();
				y = randIntGeneratorY();
			}

			m_actors.push_back(new Goldnugget(false, false, true, x, y, this));

		}

		//TODO MAKE TIS RANDOM
	//	m_actors.push_back(new OilBarrel(randIntGeneratorX(), randIntGeneratorY(), this));
	//	m_actors.push_back(new OilBarrel(randIntGeneratorX(), randIntGeneratorY(), this));
	//	m_actors.push_back(new OilBarrel(randIntGeneratorX(), randIntGeneratorY(), this));
		m_actors.push_back(new Sonar(0,60,this));
	 	//m_actors.push_back(new Goldnugget(false, false, true, 10, 60, this));
		//m_actors.push_back(new Boulder(randIntGeneratorX(), randIntGeneratorY(), this));

		

		//TODO: add all actors to the m_actors vector

		//add all earth objects
		for (int i = 0; i < 60; i++) {
			for (int j = 0; j < 60; j++) {
				m_earth[i][j] = new Earth(i, j, this); //earth's world ptr is this student world
					
				
			}
		}
		for (int i = 30; i <= 33; i++) { //place in mine shaft by deleting dirt
			for (int k = 4; k <= 59; k++) {
				delete m_earth[i][k];
				m_earth[i][k] = nullptr;
			}
		}
	


		m_tunnelman = new TunnelMan(this); //new tunnelman to have this studentworld as his world
		
		return GWSTATUS_CONTINUE_GAME;
	}

	virtual int move()
	{
		//TODO: random sonar, water and rand gold spawner must go here
		// This code is here merely to allow the game to build, run, and terminate after you hit enter a few times.
		// Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
		m_tunnelman->doSomething();
		//add for loop to make all other actorss do something when they are formed
		//test random sonar spawn
		for (size_t i = 0; i < m_actors.size(); i++) {
			m_actors[i]->doSomething();
		}
		if (m_tunnelman->getHealth() <= 0) {
			decLives(); //decrease lives
			return GWSTATUS_PLAYER_DIED; //tell user he dead
		}
		//erase all dead actors from m_actor
	/*	std::vector<Actor*>::iterator it;
		it = m_actors.begin();
		while (it != m_actors.end()) {
			if (isDead(*it) == true) {
				m_actors.erase(it);
				it = m_actors.begin();
			}
		}
*/
		if (m_oilbarrels <= 0){
			playSound(SOUND_FINISHED_LEVEL);
			return GWSTATUS_FINISHED_LEVEL; //should move to next level
		}

		for (int i = 0; i < m_actors.size(); ++i) {
			if (m_actors[i]->isAlive() == false) {
				m_actors[i]->setVisible(false);
				delete m_actors[i];
				m_actors.erase(m_actors.begin() + i);
				i--;
			}
		}
		return GWSTATUS_CONTINUE_GAME;
		
	}

	virtual void cleanUp()
	{
		delete m_tunnelman; 

		for (int i = 0; i < 60; i++) {
			for (int j = 0; j < 60; j++) {
				if (m_earth[i][j] != nullptr) { //if earth
					delete m_earth[i][j]; //delete memoty
					m_earth[i][j] = nullptr; //set ptr to null to avoud random pointing
				}
			}
		}

		//add more for other objects
		int intial = m_actors.size();
		for (size_t i = 0; i < m_actors.size(); i++) {
			delete m_actors[i]; //transverse and delete

			m_actors.erase(m_actors.begin()); //remove vector
		}
		return;
		
	}
	int randIntGeneratorX(); //for inserting at radom locations
	int randIntGeneratorY(); 

	bool personCanMove(int x, int y, bool canMove) const;
	bool atEarth(int x, int y); //determin e if the current cords are on earth object
	bool removeEarth(int x, int y);
	Actor* getActor(int x, int y); //returns a pointer to the acctor at those points
	void addBarrel(int amt);
	TunnelMan* findTunnelMan(Actor* act, int rad) const; 
	bool isDead(Actor* ptr);
	void giveSonar(int num);
	void tunnelManUseSonar(TunnelMan* man);
	void giveGoldTunnelman(int num, TunnelMan* a);
	void addActor(Actor* a);
	bool withinRad(int x1, int y1, int x2, int y2, int rad) const;// prevent duplicte code
	//void dropGoldNugget();
private:

	std::vector<Actor*> m_actors; //pointer collection of all in game actors
	Earth* m_earth[60][60]; //ptr to earth matrix
	TunnelMan* m_tunnelman; //ptr to in game player
	int m_oilbarrels; //current amt for level

	//class Location { //class designed to keep track of 
	//public:
	//	Location(int r, int c) : m_r(r), m_c(c) {}
	//	int r() const { return m_r; }
	//	int c() const {
	//		return m_c;}
	//private:
	//	int m_r;
	//	int m_c;
	//};
 //vector of ingame actors





};

#endif // STUDENTWORLD_H_
