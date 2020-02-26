#include "Actor.h"
#include "StudentWorld.h"
using namespace std;
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
	m_water = 5;
	setVisible(true);
}
void TunnelMan::annoyPerson(int amt) {
	getWorld()->playSound(SOUND_PLAYER_ANNOYED);
	setHealth(getHealth() - amt);

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
	if (sound == true) {
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

				Goldnugget* newnug = new Goldnugget(true, true, false, false, getX(), getY(), getWorld());
				getWorld()->addActor(newnug);
				// getWorld()->dropGoldNugget(true, false, false, getX(), getY(), getWorld());
				//getWorld()->giveGold(1, this);
			}break;
		case KEY_PRESS_SPACE:
			if (m_water > 0) {
				//Add squirt into world
				getWorld()->playSound(SOUND_PLAYER_SQUIRT);
				m_water--;

				Direction myDir = getDirection();
				Squirt* newSquirt;
				if (myDir == up){
					newSquirt = new Squirt(getX(), getY() + 4, myDir, getWorld());
				getWorld()->addActor(newSquirt);
			}
				else if (myDir == down) {
					newSquirt = new Squirt(getX(), getY() - 4, myDir, getWorld());
					getWorld()->addActor(newSquirt);
				}
				else if (myDir == left) {
					newSquirt = new Squirt(getX() - 4, getY(), myDir, getWorld());
					getWorld()->addActor(newSquirt);

				}
				else if (myDir == right) {
					newSquirt = new Squirt(getX() + 4, getY(), myDir, getWorld());
					getWorld()->addActor(newSquirt);

				}
				//Let StudentWorld class manage the squirt

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
	 //subtract the amt in the world
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
		getWorld()->increaseScore(1000);
		getWorld()->playSound(SOUND_FOUND_OIL);
		getWorld()->addBarrel(-1);
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
		getWorld()->increaseScore(75);

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

Goldnugget::Goldnugget(bool spawned, bool visability, bool perminate, bool forTunnelman, int startX, int startY, StudentWorld* world) : 
	StillActor(TID_GOLD, startX, startY, right, 1.0, 2, world) {
	m_spawned = spawned;
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
		getWorld()->increaseScore(25);

		getWorld()->playSound(SOUND_GOT_GOODIE);
	}
	//TODO GOLD FOR PROTERTER
	Protestor* pros = getWorld()->findProtestor(this, 4);
	if (pros != nullptr) {
		setLifeState(false);
		pros->bribe();
		//increase score

	}
	//SCORING

	if (!m_perminate && m_spawned == true) {
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

void Boulder::doSomething() { //REWRITE
	bool hasFallen = false;
	
	
	if (isAlive() == false) {
		return;
	}
	if (m_state == stable) {
		for (int i = 0; i < 4; i++) {
			getWorld()->removeEarth(getX(), getY()+i);
			getWorld()->removeEarth(getX() + 1, getY()+i);
			getWorld()->removeEarth(getX() + 2, getY()+i);
			getWorld()->removeEarth(getX() + 3, getY()+i);
			}
	}
	if (m_state==stable&&getWorld()->atEarth(getX(), getY() - 1) == false && getWorld()->atEarth(getX() + 1, getY() - 1) == false && getWorld()->atEarth(getX() + 2, getY() - 1) == false && getWorld()->atEarth(getX() + 3, getY() - 1) == false) {
		m_state = waiting;
		//while (m_waitticks>0) {
	}
	else if (m_state == waiting) {
		if (m_waitticks) {
			m_waitticks--;
		}

			
		else {
			m_state = falling;

				getWorld()->playSound(SOUND_FALLING_ROCK);
		}

	}

	else{ 
			if(m_state==falling&&getWorld()->atEarth(getX() + 1, getY() - 1) == false && getWorld()->atEarth(getX() + 2, getY() - 1) == false && getWorld()->atEarth(getX() + 3, getY() - 1) == false && getWorld()->atEarth(getX() , getY() - 1) == false) {
				//	//getWorld()->playSound(SOUND_FALLING_ROCK);
				TunnelMan* t = getWorld()->findTunnelMan(this, 3);
				if (t != nullptr) {
					t->annoyPerson(100);
				}
				Protestor* p = getWorld()->findProtestor(this, 3);
				if (p != nullptr) {
					p->annoyPerson(100);
				}
				//getWorld()->annoyAllNearbyPeople(this, 10, 10, true);
				moveTo(getX(), getY() - 1);
				
			}
			if (m_state == falling && (getWorld()->atEarth(getX() + 1, getY() - 1)  ||  getWorld()->atEarth(getX() + 2, getY() - 1) || getWorld()->atEarth(getX() + 3, getY() - 1)  || getWorld()->atEarth(getX(), getY() - 1)) ) {

				setLifeState(false);
			}
			
			/*if ((getWorld()->atEarth(getX(), getY() - 1) && (getWorld()->atEarth(getX() + 1, getY() - 1) && getWorld()->atEarth(getX() + 2, getY() - 1) && getWorld()->atEarth(getX() + 3, getY() - 1)))) {
				m_state = stable;
				

			}*/
			//hasFallen = true;

		}
		
	
		
	
		//bool fallen = false;

	//if (isAlive() == false) {
	//	return; // do nothing
	//}
	//if (m_state == falling /*&& (getWorld()->atEarth(getX() + 1, getY() ) || getWorld()->atEarth(getX(), getY() ) || getWorld()->atEarth(getX() + 2, getY() ) || getWorld()->atEarth(getX()+3, getY() ))*/) {
	//	//	getWorld()->playSound(SOUND_FALLING_ROCK);
	//	



	//}
	//bool canFall = true;
	//if (m_state == stable) {
	//	
	//	if (getX() + 3 > 59 || getY() - 1 < 0|| getY()==0) {//tentative check for boundary, plus three to account for size
	//		canFall = false;

	//	}
	//}
	////take out earth around boulder
	//for (int i = 0; i < 4; i++) {
	//getWorld()->removeEarth(getX(), getY()+i);
	//getWorld()->removeEarth(getX() + 1, getY()+i);
	//getWorld()->removeEarth(getX() + 2, getY()+i);
	//getWorld()->removeEarth(getX() + 3, getY()+i);
	//}
	//if (m_state == stable && getWorld()->atEarth(getX(), getY() - 1) == false && getWorld()->atEarth(getX() + 1, getY() - 1)==false && getWorld()->atEarth(getX() + 2, getY() - 1)==false && getWorld()->atEarth(getX()+3 , getY() - 1)==false) {
	//	if (canFall == true) {
	//		m_state = waiting;
	//		m_waitticks--;
	//		if (m_waitticks <= 0) {
	//			m_state = falling;
	//			if (m_waitticks == 0)
	//			hasFallen = true;
	//		}

	//	}
	//	
	//}
	//if (m_state == falling) {


	//	while(getWorld()->atEarth(getX() + 1, getY() - 1) == false && getWorld()->atEarth(getX() + 2, getY() - 1) == false && getWorld()->atEarth(getX() + 3, getY() - 1) == false) {
	//	//getWorld()->playSound(SOUND_FALLING_ROCK);
	//	moveTo(getX(), getY() - 1);
	//	if (hasFallen) {
	//		getWorld()->playSound(SOUND_FALLING_ROCK);
	//		//TODO:ADD ANNOYANCE for 
	//		hasFallen = false;
	//		}
	//	

	//	}




	//}



}

	

//Protestor implementation
Protestor::Protestor(StudentWorld* world, int id)
	:Person(id, 58, 60, left, 1.0, 0, 5, world) {
	id = TID_PROTESTER;
	setVisible(true); 
	m_isleaving = false;
	setSquarestoMove((rand() % 53 + 8));
	m_currentticks=m_waitingticks= std::max((unsigned int)0, 3 - (getWorld()->getLevel()) / 4); //waiting ticks randomized 
	m_shoutwaitingticks = 0;
	m_perpwaitingticks = 200;

}
Protestor::~Protestor(){}

void Protestor::doSomething() {
	if (!isAlive()) {
		return;
	}
	if (getHealth() <= 0) {
		setLeavingStats();
	}
	
	if (getCurrentTicks() != 0) {
		setCurrentTicks(getCurrentTicks() - 1);
		return;
	}
	if (isleavingField()) {
		if (getX() == 60 || getX() == 56 && getY() == 60) {//leaving vicinity
			setLifeState(false);
		}
		int ax = getX();
		int ay = getY();
		Direction dir = getWorld()->getProtestorDirection(this);//meant to return direction to exit
		setDirection(dir);
		newPos(ax, ay, 1, dir);//update coords
		
		moveTo(ax , ay);
		//m_squarestomove++;
		
		
		

		return;
	}
	setCurrentTicks(getWaitingTicks());
	if (m_shoutwaitingticks > 0) {
		m_shoutwaitingticks--;
	}
	

	
	if (m_perpwaitingticks > 0) {
		m_perpwaitingticks--;
	}
	TunnelMan* tun = getWorld()->findTunnelMan(this, 4);
	if (tun != nullptr && m_shoutwaitingticks == 0 )
	{
		getWorld()->playSound(SOUND_PROTESTER_YELL);

		tun->annoyPerson(2);

		//Do not let protester shout for 15 ticks
		m_shoutwaitingticks = 15;

		//Do not do anything else this tick
		return;
	}
	//check line of sight of tunnelman, mak sure not blocked by anything. then face that direction and step toward him

	if (getWorld()->tunnelManInSight(getX(), getY(), right)) {
		setDirection(right);
		int bx = getX();
		int by = getY();
		newPos(bx,by,1,right);
		moveTo(bx, by);
		m_squarestomove--;//moved!
		return;
	}
	else if (getWorld()->tunnelManInSight(getX(), getY(), left)) {
		setDirection(left);
		int cx = getX();
		int cy = getY();
		newPos(cx, cy, 1, left);
		moveTo(cx, cy);
		m_squarestomove--; //moved!
		return;
	}
	else if (getWorld()->tunnelManInSight(getX(), getY(), up)) {
		setDirection(up);
		int dx = getX();
		int dy = getY();
		newPos(dx, dy, 1, up);
		moveTo(dx, dy);
		m_squarestomove--; //moved!
		return;
	}
	else if (getWorld()->tunnelManInSight(getX(), getY(), down)) {
		setDirection(down);
		int ex = getX();
		int ey = getY();
		newPos(ex, ey, 1, down);
		moveTo(ex, ey);
		m_squarestomove--; //moved!
		return;
	}
	

		//if not in line of sight then random movement
		//setSquarestoMove(getSquarestoMove() - 1);
		if (getSquarestoMove() <= 0) {
			while (true) {
				int rando = rand() % 4 + 1;
				Direction direct = (Direction)rando; //ITs posible!
				int nextX = getX();
				int nextY = getY();
				newPos(nextX, nextY, 1, direct);
				switch (direct) {
				case up:
					if (getWorld()->personCanMove(nextX, nextY, false)) {

						setDirection(up);
						int rando2 = rand() % 53 + 8;
						setSquarestoMove(rando2);
						goto OUTSIDE;
					}
					break;
				case down:
					if (getWorld()->personCanMove(nextX, nextY, false)) {

						setDirection(down);
						int rando2 = rand() % 53 + 8;
						setSquarestoMove(rando2);
						goto OUTSIDE;
					}
					break;
				case left:
					if (getWorld()->personCanMove(nextX, nextY, false)) {

						setDirection(left);
						int rando2 = rand() % 53 + 8;
						setSquarestoMove(rando2);
						goto OUTSIDE;
					}
					break;
				case right:
					if (getWorld()->personCanMove(nextX, nextY, false)) {

						setDirection(right);
						int rando2 = rand() % 53 + 8;
						setSquarestoMove(rando2);
						goto OUTSIDE;
					}
				}


			} OUTSIDE:;
				
		}

		if ((getDirection() == right || getDirection() == left)&& m_perpwaitingticks==0) {
			bool upGood = false;
			bool downGood = false;
			int x = getX();
			int y = getY();
			newPos(x, y, 1, up);
			if (getWorld()->personCanMove(x, y, false)) {
				upGood = true;
			}
			 x = getX();
			 y = getY();
			newPos(x, y, 1, down);
			if (getWorld()->personCanMove(x, y, false)) {
					downGood = true;
			}
			if (downGood && !upGood) {
				//turn down
				setDirection(down);
				int rando2 = rand() % 53 + 8;
				setSquarestoMove(rando2);
				m_perpwaitingticks = 200;
			}
			else if (!downGood && upGood) {
				//turn upward
				setDirection(up);
				int rando2 = rand() % 53 + 8;
				setSquarestoMove(rando2);
				m_perpwaitingticks = 200;
			}
			else if (downGood && upGood) {
				//new random chance
				int rando2 = rand() % 53 + 8;

				int rando3 = rand() % 1;
				if (rando3 == 0) {
					setDirection(down);
					setSquarestoMove(rando2);
					m_perpwaitingticks = 200;

				}
				else {
					setDirection(up);
					setSquarestoMove(rando2);
					m_perpwaitingticks = 200;

				}
			}
			
		}
		//

		if ((getDirection() == down || getDirection() == up) && m_perpwaitingticks == 0) {
			bool rGood = false;
			bool lGood = false;
			int x = getX();
			int y = getY();
			newPos(x, y, 1, right);
			if (getWorld()->personCanMove(x, y, false)) {
				rGood = true;
			}
			 x = getX();
			 y = getY();
			newPos(x, y, 1, left);
			if (getWorld()->personCanMove(x, y, false)) {
				lGood = true;
			}
			if (rGood && !lGood) {
				//turn right
				setDirection(right);
				int rando2 = rand() % 53 + 8;
				setSquarestoMove(rando2);
				m_perpwaitingticks = 200;
			}
			if (lGood && !rGood) {
				//turn left
				setDirection(left);
				int rando2 = rand() % 53 + 8;
				setSquarestoMove(rando2);
				m_perpwaitingticks = 200;
			}
			else if (lGood && rGood) {
				//new random chance
				int rando2 = rand() % 53 + 8;

				int rando3 = rand() % 1;
				if (rando3 == 0) {
					setDirection(left);
					setSquarestoMove(rando2);
					m_perpwaitingticks = 200;

				}
				else {
					setDirection(right);
					setSquarestoMove(rando2);
					m_perpwaitingticks = 200;

				}
			}

		}
		//we can now try to step forward, we have checked avaible directions to access and should b facing right one
		int myX = getX();
		int myY = getY();
		newPos(myX, myY, 1, getDirection());
		//new protestors will need to move to the field
		if (getX() > 56 && getDirection() == left)
			moveTo(myX, myY);
		else if (getWorld()->personCanMove(myX, myY, false))
			moveTo(myX, myY);
		else //cannot move so stop
			setSquarestoMove(0);

}
	
void Protestor::bribe() {

	if (isHardCore()) {
		int stare = std::max((unsigned int)50, 100 - getWorld()->getLevel() * 10);

		setCurrentTicks(getCurrentTicks() + stare);
		getWorld()->playSound(SOUND_PROTESTER_FOUND_GOLD);
		getWorld()->increaseScore(50);
	}
	else{
		getWorld()->playSound(SOUND_PROTESTER_FOUND_GOLD);
		getWorld()->increaseScore(25);
		setLeavingStats();
	}
}

	


		



void Protestor::annoyPerson(int amt) {
	setHealth(getHealth() - amt);
	getWorld()->playSound(SOUND_PROTESTER_ANNOYED);

}


//Hardcore
HardCoreProtestor::HardCoreProtestor(StudentWorld* world): Protestor( world, TID_HARD_CORE_PROTESTER){
	setHealth(getHealth() + 15);//hp of 20
	m_staringticks = 0;
	setVisible(true);

}
HardCoreProtestor::~HardCoreProtestor(){}





WaterPool:: WaterPool(int startX, int startY, StudentWorld* world):StillActor(TID_WATER_POOL, startX, startY, right, 1.0, 2, world) {
	isVisible();
	int level = getWorld()->getLevel();
	setTicks(std::max(100, 300 - 10 * level));
}
WaterPool::~WaterPool(){}
 void WaterPool::doSomething(){
	 if (!isAlive())
		 return;

	 Actor* Tun = getWorld()->findTunnelMan(this, 3); //in radius
	 if (Tun != nullptr) {
		 //The water pool must now die

		 //Play sound
		 getWorld()->playSound(SOUND_GOT_GOODIE);

		
		 getWorld()->giveWaterTunnelman(5);
		 getWorld()->increaseScore(100);

		 setLifeState(false);

	 }

	 if (ticksRemaining() <= 0) {
		 setLifeState(false);
	 }
	 
		 setTicks(ticksRemaining() - 1);
	 
 
	}


 Squirt::Squirt(int startX, int startY, Direction dir, StudentWorld* world)
	 : Actor(TID_WATER_SPURT, startX, startY, dir,  1.0, 1,world){

	 m_distance = 4;//iinital

	 setVisible(true); //starts visible
 }

 Squirt::~Squirt()
 {}

 void Squirt::doSomething()
 {
	 //if within 3 radius of protester, causes 2 points of annoyance and then dies
	 if (!isAlive()) {
		 return;
	 }
	 getWorld()->annoyAllNearbyPeople(this, 3, 2, false);
	 Protestor* man = getWorld()->findProtestor(this, 4);
	 if (man != nullptr && !isVisible()) {
		 setLifeState(false); //if tunnelman is near by a nugget make visible
		 return;
	 }

		// setLifeState(false);

	 //if has traveled full travel distance, sets its state to dead
	 if (m_distance <= 0) {
		 setLifeState(false);
	 }

	 //check if it can move in that direction, if we find earth, setdead, or boulder
	 int newX = getX();
	 int newY = getY();
	 newPos(newX, newY, 4, getDirection());
	 if (!getWorld()->personCanMove(newX, newY, false)) {
		 setLifeState(false);
	 }

	 //otherwise, the squirt moves one square forward in its currently-facing direction
	 moveTo(newX, newY);

	 //Also decrement the travel distance counter
	 m_distance--;
 }