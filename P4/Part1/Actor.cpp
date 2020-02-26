#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file (if you wish), Actor.h, StudentWorld.h, and StudentWorld.cpp
/*Actor(int imageID, int startX, int startY, Direction startDirection, float size, unsigned int depth);
	virtual ~Actor();
	virtual void doSomething(); //possible to mke this ABC
	bool isAlive() const;
	void setLifeState(bool liveState);
	StudentWorld* getWorld() const; //actors contain a pointer that points to wolrd they are in
private:
	bool m_alive;
	StudentWorld* m_world;*/

//implementation Actor class

Actor::Actor(int imageID, int startX, int startY, Direction startDirection, float size, unsigned int depth, StudentWorld* world) 
	: GraphObject(imageID, startX, startY, startDirection, size, depth) {

	m_world = world;
	m_alive = true;

}

Actor::~Actor() {}

bool Actor::isAlive() const {
	return m_alive;
}

void Actor::setLifeState(bool alive) { 
	m_alive = alive; 
}

StudentWorld* Actor::getWorld() const {
	return m_world;
}

void Actor::newPos(int& x, int& y, int distance, Direction dir) const {//accepts in x y cords and direction, updates coords of actor
	switch (dir) {
	case down:
		y -= distance;
		break;
	case up:
		y += distance;
		break;
	case left:
		x -= distance;
		break;

	case right:
		x += distance;
		

	}

}

//end actor implementation

//Earth implementation

Earth::Earth(int startX, int startY, StudentWorld* world)
	: Actor(TID_EARTH, startX, startY, right,  0.25, 3, world) {
	//TODO: make visability funct
	setVisible(true); //make gameobject visible 
}

Earth::~Earth(){}

void Earth::doSomething(){} //does nothing
//end Earth IMP
//Person class imp
Person::Person(int imageID, int startX, int startY, Direction startDirection, float size, unsigned int depth, int health, StudentWorld* world) 
	: Actor(imageID, startX, startY, startDirection, size, depth, world) {
		m_health = health;
	}

Person::~Person(){}

int Person::getHealth() const {
	return m_health;
}

void Person::setHealth(int health) {
	m_health = health;
}


//Tunnel man class imp

TunnelMan::TunnelMan(StudentWorld* world)
	:Person(TID_PLAYER, 30, 60, right, 1.0, 0, 10, world) {
	//TODO: needs more member vars
	m_sonar = 1;
	m_gold = 0;
	setVisible(true);
}
int TunnelMan::getGold() {
	return m_gold;
}
void TunnelMan::setGold(int num) {
	m_gold = num;
}

TunnelMan::~TunnelMan(){}
int TunnelMan::getSonars() {
	return m_sonar;
}
void TunnelMan::setSonar(int num) {
	m_sonar = num;
}

void TunnelMan::doSomething() {  //CHANGE
	if (getHealth() <= 0) {
		return; // player is dead
	}
	bool sound = false;
	for (int i = getX(); i < getX() + 4 && i < 60; i++) {
		for (int j = getY(); j < getY() + 4 && j < 60; j++) {
			if (getWorld()->removeEarth(i, j))
				
				sound = true;
		}
	}
 if (sound==true) {
		getWorld()->playSound(SOUND_DIG); //play once
		
	}

	//Check if a key is pressed
	int key;
	if (getWorld()->getKey(key)) //if key is pressed, do something
	{
		//user hit a key this tick!
		switch (key) //call userMove which will both then check if we can move to that area, and then it will move if possible
		{
		case KEY_PRESS_LEFT:
			userMove(left);
			break;
		case KEY_PRESS_RIGHT:
			userMove(right);
			break;
		case KEY_PRESS_UP:
			userMove(up);
			break;
		case KEY_PRESS_DOWN:
			userMove(down);
			break;





		case 'z':
		case 'Z':
		{//for SONAR
			if (m_sonar > 0) {
				m_sonar--;
				getWorld()->playSound(SOUND_SONAR);
				getWorld()->tunnelManUseSonar(this);
			}
		}break;
		case KEY_PRESS_ESCAPE: //ends game and kills tunnelman
			setHealth(0);
			break;

		case KEY_PRESS_TAB:
			if (m_gold > 0) {
				m_gold--;

				Goldnugget* newnug = new Goldnugget(true, false, false, getX(), getY(), getWorld());
				getWorld()->addActor(newnug);
				// getWorld()->dropGoldNugget(true, false, false, getX(), getY(), getWorld());
				//getWorld()->giveGold(1, this);
			}
		}
	}
}

void TunnelMan::userMove(Direction dir) {
	if (getDirection() != dir) {
		setDirection(dir); //face tunnelman in right dir
	}
	else {
		switch (dir) {
		case right: {
			if (getWorld()->personCanMove(getX() + 1, getY(), true)) {
				moveTo(getX() + 1, getY());
			}
		}break;
		case left:{ 
			if (getWorld()->personCanMove(getX() - 1, getY(), true)) {
				moveTo(getX()-1, getY());
			}
		}break;
		case up: {
			if (getWorld()->personCanMove(getX(), getY() + 1, true)) {
				moveTo(getX(), getY() + 1);
			}
		}break;
		case down: {
			if (getWorld()->personCanMove(getX(), getY()-1, true)) {
				moveTo(getX(), getY()-1);
			}
		}

		}

	}
	return;
}

//stillActor class

StillActor::StillActor(int imageID, int startX, int startY, Direction startDirection, float size, unsigned int depth,  StudentWorld* world)
	:Actor(imageID, startX, startY, startDirection, size, depth, world)
{
	m_ticks = -1; //defualt is no ticks, some objects do not have a timer
	m_visible = false;//assuming none of these items should be visible initally
}
StillActor::~StillActor() {}

void StillActor::makeStillActorVisible() {
	setVisible(true);
	m_visible = true;
}

bool StillActor::isVisible() const {
	return m_visible;
}

void StillActor::setTicks(int num) {
	m_ticks = num; //will be called on each object, num will be specfic tot he player's current level
}

int StillActor::ticksRemaining() const {
	return m_ticks;
}

//end StillActor class

//OilBarrel Clas
OilBarrel::OilBarrel(int startX, int startY, StudentWorld* world)
	: StillActor(TID_BARREL, startX, startY, right, 1.0, 2, world) {

	getWorld()->addBarrel(1); //add a barrel
}

OilBarrel::~OilBarrel() {
	getWorld()->addBarrel(-1); //subtract the amt in the world
}

void OilBarrel::doSomething() {
	if (isAlive() == false) {
		//setVisible(false);
		return; //do nothing its dead
		}

	//TODO make a function to track where tunnel man is  DONE
	Actor* tunnelman = getWorld()->findTunnelMan(this, 4);//rad of 4
	if(isVisible()==false && tunnelman!= nullptr)
		makeStillActorVisible();
		

	Actor* tunnelpickup = getWorld()->findTunnelMan(this, 3);
	if (tunnelpickup != nullptr) {
		setLifeState(false); //it should be set to false and get deleted in move 
		
		getWorld()->playSound(SOUND_FOUND_OIL);
	}

}
//SOnar

Sonar::Sonar(int startX, int startY, StudentWorld* world) : StillActor(TID_SONAR, startX, startY, right, 1.0, 2, world) {
	makeStillActorVisible();// sonar kit starts visible
	int level = getWorld()->getLevel();
	setTicks(std::max(100, 30 - 10 * level)); //according to specs
}

Sonar::~Sonar(){}

void Sonar::doSomething() {
	if (isAlive() == false) {
		return; //do nothing shold be deleted by move
	}

	//get tunnelman if closer
	Actor* tunnelman = getWorld()->findTunnelMan(this, 3);
	if (tunnelman != nullptr) {
		setLifeState(false); //consider the sonar dead
		getWorld()->playSound(SOUND_GOT_GOODIE);
		getWorld()->giveSonar(1);
	}
	if (ticksRemaining() == 0) {
		setLifeState(false);
	}
	if (ticksRemaining() > 0) {
		setTicks(ticksRemaining() - 1);
	}
}

//goldnug
//some planning
//student world needs a take gold function, should be able to give gold to Person class ptrs,
//in move if tab is pressed, make a gold nugget appear, requires making a new one 
//do something, when gold is 

Goldnugget::Goldnugget(bool visability, bool perminate, bool forTunnelman, int startX, int startY, StudentWorld* world) : 
	StillActor(TID_GOLD, startX, startY, right, 1.0, 2, world) {
	m_visible = false;
	if (visability == true) {
		m_visible = true;
		makeStillActorVisible();
	}
	setTicks(100); //inital timer (will not be decrimented if perminate
	m_perminate = perminate;
	m_forTunnelman = forTunnelman;
}
Goldnugget::~Goldnugget(){}

void Goldnugget::doSomething() {
	if (!isAlive()) {
		return; //do nothing if dead
	}

	//assume it is perminate
	//if tunnel man is near by
	TunnelMan* man = getWorld()->findTunnelMan(this, 4);
	if (man != nullptr && !isVisible()) {
		makeStillActorVisible(); //if tunnelman is near by a nugget make visible
		return;
	}
	TunnelMan* grab = getWorld()->findTunnelMan(this, 4);
	if (grab != nullptr && m_forTunnelman) {
		setLifeState(false);
		getWorld()->giveGoldTunnelman(1, grab); //give that gold to tunnelman invetroy
		getWorld()->playSound(SOUND_GOT_GOODIE);
	}
	//TODO GOLD FOR PROTERTER
	//SCORING

	if (!m_perminate) {
		setTicks(ticksRemaining() - 1); //count down
		if (ticksRemaining() <= 0) {
			setLifeState(false);
		}
	}
}
//Boulder
//Boulder

Boulder::Boulder(int startX, int startY, StudentWorld* world) : Actor(TID_BOULDER, startX, startY, down, 1.0, 1, world) {
	setVisible(true);
	m_state = stable; //all should start out stable
	m_waitticks = 30;
	hasFallen = false;
	
}

Boulder::~Boulder() {}

void Boulder::doSomething() {
	bool fallen = false;
	if (hasFallen==true&& getWorld()->atEarth(getX()+1,getY()-1)) {
		getWorld()->playSound(SOUND_FALLING_ROCK);


		setLifeState(false);
	}
	if (isAlive() == false) {
		return; // do nothing
	}
	bool canFall = true;
	if (m_state == stable) {
		
		if (getX() + 3 > 59 || getY() - 1 < 0|| getY()==0) {//tentative check for boundary, plus three to account for size
			canFall = false;

		}
	}
	//take out earth around boulder
	for (int i = 0; i < 4; i++) {
	getWorld()->removeEarth(getX(), getY()+i);
	getWorld()->removeEarth(getX() + 1, getY()+i);
	getWorld()->removeEarth(getX() + 2, getY()+i);
	getWorld()->removeEarth(getX() + 3, getY()+i);
	}
	if (getWorld()->atEarth(getX(), getY() - 1) == false && getWorld()->atEarth(getX() + 1, getY() - 1)==false && getWorld()->atEarth(getX() + 2, getY() - 1)==false && getWorld()->atEarth(getX() + 3, getY() - 1)==false) {
		if (canFall == true) {
			m_state = waiting;
			m_waitticks--;
			if (m_waitticks <= 0) {
				m_state = falling;
				//getWorld()->playSound(SOUND_FALLING_ROCK);
			}

		}
		if (m_state == falling) {
			//while(getWorld()->atEarth(getX() + 1, getY() - 1) == false && getWorld()->atEarth(getX() + 2, getY() - 1) == false && getWorld()->atEarth(getX() + 3, getY() - 1) == false) {
			//getWorld()->playSound(SOUND_FALLING_ROCK);
			moveTo(getX(), getY() - 1);

			//TODO:ADD ANNOYANCE for 
			hasFallen = true;

			//}




		}
	}
	if (hasFallen == true) {
		//getWorld()->playSound(SOUND_FALLING_ROCK);
	}


	/*if ((getWorld()->atEarth(getX(), getY() + 1) == true) && m_state== falling) {
		setLifeState(false);
	}*/
	

}

	

