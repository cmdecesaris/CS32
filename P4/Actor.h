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
	virtual bool isPerson() { return false; }
	virtual bool isProtestor() { return false; }


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
	virtual void annoyPerson(int amt) = 0;
	virtual bool isPerson() { return true; }

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
	int getWater() { return m_water; }
	void setWater(int num) { m_water += num; }
	virtual void annoyPerson(int amt); //tunnelman specfic

	//virtual void annoy(int amt, Actor* annoyer);
	//TODO more funct for Tunnel man
private:
	//TODO add in all the private vars of tunnelmans invetory such as water, oil etc
	int m_gold;
	int m_water;
	int m_sonar;
	void userMove(Direction dir); //figureout user key to make tunnelman move
};

class Protestor : public Person {
public:
	Protestor(StudentWorld* world, int id);
	virtual ~Protestor();
	virtual void doSomething();
	bool isleavingField() const { return m_isleaving; }
	void setLeavingStats() { m_isleaving = true; }
	void setSquarestoMove(int squ) { m_squarestomove = squ; }
	int getSquarestoMove() { return m_squarestomove; }
	int getCurrentTicks() const { return m_currentticks; }
	void setCurrentTicks(int tic) { m_currentticks = tic; }
	int getWaitingTicks() const { return m_waitingticks; }
	virtual void annoyPerson(int amt);
	virtual bool isHardCore() { return false; } //rgular is false
	//virtual bool blocksMove()const { return true; }
	virtual void bribe(); //for bribing with gold, will leave after
	virtual bool isProtestor() { return true; }



private:
	int m_squarestomove;
	int m_waitingticks;
	bool  m_isleaving;
	int m_perpwaitingticks;
		int m_shoutwaitingticks;
		int m_currentticks;
	
		
};


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

class WaterPool : public StillActor
{
public:
	WaterPool(int startX, int startY, StudentWorld* world);
	~WaterPool();
	virtual void doSomething();
private:
};
//goldNugget
class Goldnugget :public StillActor {
public:
	Goldnugget(bool spawned, bool visability, bool perminate, bool forTunnelman, int startX, int startY, StudentWorld* world);//visability
	~Goldnugget(); 
	virtual void doSomething();
private:
	bool m_perminate;
	bool m_visible;
	bool m_forTunnelman;
	bool m_spawned;
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
class Squirt : public Actor
{
public:
	Squirt(int startX, int startY, Direction dir, StudentWorld* world);
	~Squirt();
	virtual void doSomething();
private:
	int m_distance;
};

class HardCoreProtestor : public Protestor {
public:
	HardCoreProtestor(StudentWorld* world);
	~HardCoreProtestor();
	virtual bool isHardCore() { return true; } //rgular is false
	//virtual void bribe(); //not needed via additon of isHardCore
	//virtual void doSomething();//ran out of time

	int getStaringticks() { return m_staringticks; }
	int setStaringticks(int num) { return(m_staringticks + num); }

private:
	int m_staringticks;

};


#endif // ACTOR_H_
