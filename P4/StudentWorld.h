#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include <string>
#include <vector>
#include "Actor.h"
#include<algorithm>
#include<cstdlib>
#include<list>
#include <stack>

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
	StudentWorld(std::string assetDir);
	virtual int init();
	virtual int move();
	virtual void cleanUp();
	virtual ~StudentWorld();


	int randIntGeneratorX(); //for inserting at radom locations
	int randIntGeneratorY(); 

	bool personCanMove(int x, int y, bool canMove) const; //if boulder or earth this is no
	bool atEarth(int x, int y) const; //determin e if the current cords are on earth object
	bool removeEarth(int x, int y); 
	//Actor* getActor(int x, int y); //returns a pointer to the acctor at those points
	void addBarrel(int amt);
	TunnelMan* findTunnelMan(Actor* act, int rad) const; 
	Protestor* findProtestor(Actor* act, int rad) const;//copy of findTunnelman but returns ptr of protestor for picking things up
	TunnelMan* getTunnelman() { return m_tunnelman; }
	//bool isDead(Actor* ptr);
	void giveSonar(int num);
	void tunnelManUseSonar(TunnelMan* man);//worldimple for sonar
	void giveGoldTunnelman(int num, TunnelMan* a); //world control
	void addActor(Actor* a);
	bool withinRad(int x1, int y1, int x2, int y2, int rad) const;// prevent duplicte code
	bool tunnelManInSight(int x, int y, Actor::Direction dir) const;
	//void dropGoldNugget();
	void annoyAllNearbyPeople(Actor* person, int rad, int points, bool annoyPlayertoo );
	bool noOverlap(int actX, int actY);
	Actor::Direction getProtestorDirection(Actor* p) const;
	void giveWaterTunnelman(int num);
	bool canSpawnPool(int x, int y) const; //can only spawn pool in 4 by 4 square without earth or another object and in a tunnel

private:

	std::vector<Actor*> m_actors; //pointer collection of all in game actors
	Earth* m_earth[60][60]; //ptr to earth matrix
	TunnelMan* m_tunnelman; //ptr to in game player
	int m_oilbarrels; //current amt for level

	GraphObject::Direction m_shortPath[64][64]; //for protestors leaving field
	int m_shortestLength[64][64];
	int m_ticksSpawnProtestor;
	int m_maxTicks;
	int m_currentticks;
	int m_numProtestors;


	struct Coords 
	{
	public:
		Coords(int x_val, int y_val)
		{
			m_x = x_val;
			m_y = y_val;
		}
		int x() const
		{
			return m_x;
		}
		int y() const
		{
			return m_y;
		}
	private:
		int m_x;
		int m_y;
	};

	bool canLeaveOilField(int x1, int y1, int startX, int startY) const;
	void dirCheck(int maze[56][60], std::stack<Coords>& qCords, int row, int col) const;
	void showDisplay();
	std::string setDisplay(int level, int score, int sonar, int barrelsleft, int lives, int health, int gold, int squrits) const;
	std::string format(int in, int digits, bool zeros) const;

};

#endif // STUDENTWORLD_H_
