#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
class StudentWorld;
class Actor : public GraphObject {
public:
	Actor(int imageID, int startX, int startY, Direction startDirection, float size, unsigned int depth, StudentWorld* world);
	virtual ~Actor();
	virtual void doSomething()= 0; //possible to mke this ABC
	virtual bool blocksMove() const { return false; } //to be over written by objects that DO block movment, aka boulders
	bool isAlive() const;
	void setLifeState(bool liveState);
	StudentWorld* getWorld() const; //actors contain a pointer that points to wolrd they are in
	void newPos(int& x, int& y, int distance, Direction dir) const;
	virtual bool isBoulder() { return false; }
private:
	bool m_alive;
	StudentWorld* m_world;

};
//Person class for all 'people' actors who have a health bar, includes tunnelman and all protesters
class Earth : public Actor {
public:
	Earth(int startX, int startY, StudentWorld* world);
	~Earth();

	virtual void doSomething(); 
	
};
class Person : public Actor {
public: 
	Person(int imageID, int startX, int startY, Direction startDirection, float size, unsigned int depth, int health, StudentWorld* world); 
	virtual ~Person();
	int getHealth() const; //return health
	void setHealth(int health);
	
private:
	int m_health; //current health of person object
	
};


class TunnelMan : public Person{
public:
	TunnelMan(StudentWorld* world);
	~TunnelMan();
	virtual void doSomething();
	int getSonars();
	void setSonar(int num);
	int getGold();
	void setGold(int num);
	
	//TODO more funct for Tunnel man
private:
	//TODO add in all the private vars of tunnelmans invetory such as water, oil etc
	int m_gold;
	int m_water;
	int m_sonar;
	void userMove(Direction dir); //figureout user key to make tunnelman move
};

//stillActor class for oil, gold, and water, sonar these become visible as game
//progresses, 
//pseduo
/*
pub:
bool if visible const
void tick setter to give visibility start time, takes int
int ticks remaining const-gives ticks left
void makevisibleforstill, 

private:
bool m_visbile; //if yes make visible for real etc etc
 int cur_ticks; //count down


*/
class StillActor : public Actor {
	public:
		StillActor(int imageID, int startX, int startY, Direction startDirection, float size, unsigned int depth,  StudentWorld* world);
		~StillActor();
		bool isVisible() const;
		void setTicks(int ticks);
		int ticksRemaining() const;
		void makeStillActorVisible();
			//no need for doSomething, it will be overridden in all the StillActor derived classes
	private:
		int m_ticks;
		bool m_visible;
};
// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
class OilBarrel : public StillActor {
public: 
	OilBarrel(int startX, int startY, StudentWorld* world);
	~OilBarrel();
	virtual void doSomething();


};

class Sonar: public StillActor {
public:
	Sonar(int startX, int startY, StudentWorld* world);
	~Sonar();
	virtual void doSomething();

};
//goldNugget
class Goldnugget :public StillActor {
public:
	Goldnugget(bool visability, bool perminate, bool forTunnelman, int startX, int startY, StudentWorld* world);//visability
	~Goldnugget(); 
	virtual void doSomething();
private:
	bool m_perminate;
	bool m_visible;
	bool m_forTunnelman;
};

//Bolders
class Boulder : public Actor {
public:
	Boulder(int startX, int startY, StudentWorld* world);
	~Boulder();
	virtual void doSomething();
	virtual bool blocksMove() const { return true; }; // cannot pass through bolders 
	virtual bool isBoulder() { return true; }


private:
	enum boulderState {stable, waiting, falling};
	boulderState  m_state;
	int m_waitticks;
	bool hasFallen;
};

#endif // ACTOR_H_
