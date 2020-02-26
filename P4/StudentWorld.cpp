#include "StudentWorld.h"
#include <string>
#include <queue>
#include <stack>
using namespace std;


StudentWorld::StudentWorld(std::string assetDir)
	: GameWorld(assetDir)
{
}


int StudentWorld::init()
{
	
	m_currentticks=0;//keeps track
	//testing m_actors.push_back(new HardCoreProtestor(this));

//	m_actors.push_back(new Protestor(this));
	m_ticksSpawnProtestor = max((double)25, (double)200 - getLevel()); //spwan initaly


	int numBoulders = std::min((int)(getLevel() / 2 + 2), 9);
	for (int i = 0; i < numBoulders; i++) {
		int x = randIntGeneratorX();
		int y = randIntGeneratorY();
		while ((x > 26 && x <= 33) && (y >= 20 && y < 60)|| y<20 ) { //no spawining in the shaft
			
				x = randIntGeneratorX();
				y = randIntGeneratorY();
				
		}

		if (noOverlap(x, y)) {
			m_actors.push_back(new Boulder(x, y, this));

		}
		else { i--; }

		

	}
	int numOilbarrels = std::min((int)(getLevel() + 2), 21);
	for (int i = 0; i < numOilbarrels; i++) {
		int x = randIntGeneratorX();
		int y = randIntGeneratorY();
		while ((x >= 27 && x <= 33) && (y >= 4 && y < 60)) { //no spawining in the shaft
			x = randIntGeneratorX();
			y = randIntGeneratorY();
		}
		if (noOverlap(x, y)) {
			m_actors.push_back(new OilBarrel(x, y, this));

		}
		else { i--; }

	

	}
	int numGold = std::min((int)(5 - getLevel() / 2), 2);
	for (int i = 0; i < numGold; i++) {
		int x = randIntGeneratorX();
		int y = randIntGeneratorY();
		while ((x >= 27 && x <= 33) && (y >= 4 && y < 60)) { //no spawining in the shaft
			x = randIntGeneratorX();
			y = randIntGeneratorY();
		}
		if (noOverlap(x, y)) {
			m_actors.push_back(new Goldnugget(false, false, false, true, x, y, this));

		}
		else { i--; }



	}
	//TODO:MAKE OBJECT NOT SPAWN UNLESS 6 un apart DONE
	//TODO MAKE TIS RANDOMDONE
//	m_actors.push_back(new OilBarrel(randIntGeneratorX(), randIntGeneratorY(), this));
//	m_actors.push_back(new OilBarrel(randIntGeneratorX(), randIntGeneratorY(), this));
//	m_actors.push_back(new OilBarrel(randIntGeneratorX(), randIntGeneratorY(), this));
	//m_actors.push_back(new Sonar(0, 60, this));
	//m_actors.push_back(new Goldnugget(false, false, true, 10, 60, this));
	//m_actors.push_back(new Boulder(randIntGeneratorX(), randIntGeneratorY(), this));



	//TODO: add all actors to the m_actors vector

	//add all earth objects
	for (int i = 0; i < 60; i++) {
		for (int j = 0; j < 60; j++) {
			m_earth[i][j] = new Earth(i, j, this); //earth's world ptr is this student world


		}
	}
	for (int i = 30; i <= 33; i++) { //place in mine shaft by deleting earth
		for (int k = 4; k <= 59; k++) {
			delete m_earth[i][k];
			m_earth[i][k] = nullptr;
		}
	}



	m_tunnelman = new TunnelMan(this); //new tunnelman to have this studentworld as his world

	return GWSTATUS_CONTINUE_GAME;
}












 int StudentWorld::move()
{
	// findProsShortestPath(60, 60);											// queue based algorithm is always updated (but just once for any protestor) every tick to find optimal path
	//TODO: random sonar, water and rand gold spawner must go here
	// This code is here merely to allow the game to build, run, and terminate after you hit enter a few times.
	// Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
	 m_currentticks++;
	 showDisplay();//updates every tick
	m_tunnelman->doSomething();

	for (int i = 0; i < m_actors.size(); i++) { m_actors[i]->doSomething(); }

	for (vector<Actor*>::iterator it = m_actors.begin(); it != m_actors.end(); )
	{
		if (!(*it)->isAlive()) { delete* it; it = m_actors.erase(it); }
		else { it++; }
	}
	


	if (m_tunnelman->getHealth() <= 0) {
		decLives(); //decrease lives
		return GWSTATUS_PLAYER_DIED; //tell user he dead
	}

	if (m_oilbarrels <= 0) {
		playSound(SOUND_FINISHED_LEVEL);
		return GWSTATUS_FINISHED_LEVEL; //should move to next level
	}
	//SPAWNERs
	//protestors
	 int T = std::max((unsigned int)25, (unsigned int) 100 - getLevel()); 
	 int P = std::min((double)15,(double) 2 + getLevel() * 1.5);
	 int hardCoreProb = std::min((double)90, (double)getLevel() * 10 + 30);
	 int ran = rand() % (hardCoreProb - 1) + 1;
	 if (m_numProtestors < P && m_ticksSpawnProtestor >= T) {
		 if (ran == 1) {
			 m_actors.push_back(new HardCoreProtestor(this));

		 }else{

		 m_actors.push_back(new Protestor(this, TID_PROTESTER));
		 m_numProtestors++;
		 m_ticksSpawnProtestor = -1;
	 }
	 }
	 m_ticksSpawnProtestor++;

	int G = getLevel() * 25 + 300; //goodie chance
	int spawn = rand() % (G - 1) + 1;
	if (spawn == 1) {
		int sonarChance = rand() % (5 - 1) + 1;
		if (sonarChance == 1) {
			
			m_actors.push_back(new Sonar(0, 60, this));
		}
		else { //waterpool
			int x = 0;
			int y = 0;
			while (!canSpawnPool(x, y)&& noOverlap(x,y)) {
				x = randIntGeneratorX();
				y = randIntGeneratorY();
			}
			m_actors.push_back(new WaterPool(x, y, this));

		}
	}
	return GWSTATUS_CONTINUE_GAME;

}

 void StudentWorld::cleanUp()
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
	for (vector<Actor*>::iterator it = m_actors.begin(); it != m_actors.end(); )
	{
		delete* it;
		it = m_actors.erase(it);
	}
	return;

}

GameWorld* createStudentWorld(string assetDir)
{
	return new StudentWorld(assetDir);
}

// Students:  Add code to this file (if you wish), StudentWorld.h, Actor.h and Actor.cpp
StudentWorld::~StudentWorld() {
	//cleanUp();
	vector<Actor*>::iterator i;

	//Erase actors.
	for (i = m_actors.begin(); i != m_actors.end();) {
		delete* i;
		i = m_actors.erase(i);
	}
	//Erase earth elements.
	for (int k = 0; k < 60; k++) {
		for (int l = 0; l < 56; l++) {
			m_earth[k][l] = nullptr;
			delete m_earth[k][l];  //just in case
			//m_earth[k][l] = nullptr;
			//grid[k][l] = distance(60, 60, k, l);
		}
	}
	delete m_tunnelman;
	////cleanUp();  //function should destory dynamically aloocated memory
}



bool StudentWorld::personCanMove(int x, int y, bool canMoveEarth) const { //in implementation canMoveEarth is true for the tunnelman person only, false for protestors
	//boundary
	if (x < 0 || x>56 || y > 60 || y < 0) {
		return false;
	}
	
	
	if (!canMoveEarth) {//protestors and water
		for (int i = x; i < x + 4 && i < 60; i++) {
			for (int k = y; k < y + 4 && k < 60; k++) {
				if (atEarth(i, k))
					return false;
			}
		}
	}
	for (size_t i = 0; i < m_actors.size(); i++) {
		//Ensure that actor is within radius of 3 
		

		
		if (withinRad(m_actors[i]->getX(), m_actors[i]->getY(), x, y, 2)) {
			if (m_actors[i]->blocksMove())
				return false;
			
		} 
	}
	return true;

}
bool StudentWorld::atEarth(int x, int y) const {

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
	return false; //indicates that the  spot is not earth


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
void StudentWorld::giveWaterTunnelman(int num)
{
	int curWater = m_tunnelman->getWater();
	m_tunnelman->setWater(curWater + num);
}

int StudentWorld::randIntGeneratorX() {
	
	return (rand() % 56 );
}
int StudentWorld::randIntGeneratorY() {
	return (rand() % 60 -2 );
}
void StudentWorld::addActor(Actor* a) {
	m_actors.push_back(a);
}
//bool StudentWorld::isDead(Actor* ptr) { //will delete this actor,
//	if (ptr->isAlive() == false) {
//		
//		delete ptr;
//		return true;
//	}
//	return false;
//
//}
//Actor* StudentWorld::getActor(int x, int y) {
////	//TODO STL iteration through m_actors vector, find the indicated one at that pos and return it
////	return;
//	for (size_t i = 0; i < m_actors.size(); i++) {
//		if (m_actors[i]->getX() == x && m_actors[i]->getY() == y) {
//			return m_actors[i]; //ptr to actor will be returned
//		}
//	}
//	return nullptr; //if none is found
//
//} //returns a pointer to the acctor at those points

void StudentWorld::tunnelManUseSonar(TunnelMan* man) {
	int tun_x = man->getX();
	int tun_y = man->getY();
	//for every actor find if they are in the 12 unit distance of tunnel man if yes, make visuleb
	for (size_t i = 0; i < m_actors.size(); i++) {
		int act_x = m_actors[i]->getX();
		int act_y = m_actors[i]->getY();
		//double phyphag_square = (act_x - man_x) * (act_x - man_x) + (act_y - man_y) * (act_y - man_y);
		//double dist = (double)sqrt((double)phyphag_square);
		if (withinRad(act_x,act_y, tun_x, tun_y, 12)) {
			m_actors[i]->setVisible(true); //make it visible 
			//TODO: CODE IN THE KEY FOR USING SONAR in TUNNELMANCLASS
		}
	}
}
bool StudentWorld::withinRad(int x1, int y1, int x2, int y2, int rad)const {
	double phyphag_square =(double) ((double)(x1 - (double)x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
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

	/*double distSqa = (double)((act_x - tun_x) * (act_x - tun_x)) + ((act_y - tun_y) * (act_y - tun_y));
	double dist = sqrt(distSqa);*/

	if (withinRad(act_x, act_y, tun_x, tun_y, rad)) { //if tunnel man is in proximity to item
		return m_tunnelman;
	}

	return nullptr; //if we don't find tunnelman 
}
Protestor* StudentWorld::findProtestor(Actor* act, int rad) const {	//copy of findTunnelman but returns ptr of protestor for picking things up
	

	for (int i = 0; i < m_actors.size(); i++) {
		if (m_actors[i]->isPerson()) {
			if (withinRad(act->getX(), act->getY(), m_actors[i]->getX(), m_actors[i]->getY(), rad)) {
				return (Protestor*)m_actors[i]; //found
			}
		}
	}
	

	return nullptr; //if we don't find tunnelman 

}



void StudentWorld::annoyAllNearbyPeople(Actor* thing, int rad, int points, bool annoyPlayertoo) {
	//for (int i = 0; i < m_actors.size(); i++) {
		if ( withinRad(thing->getY(), thing->getX(), m_tunnelman->getX(), m_tunnelman->getY(), rad)&& annoyPlayertoo) {
			m_tunnelman->annoyPerson(points);
			
		}
		Protestor* p = findProtestor(thing, 4);
		if (p != nullptr) {
			
			
				p->annoyPerson(points);
				increaseScore(500);
			
		}
	//}

}

bool StudentWorld::noOverlap(int actX, int actY) {
	//int actX = a->getX();
	//int actY = a->getY();
	for (int i = 0; i < m_actors.size(); i++) {
		if (withinRad(m_actors[i]->getX(), m_actors[i]->getY(), actX, actY, 6)) {
			return  false;
		}
	}
	return true;
	
}







bool StudentWorld::canLeaveOilField(int x1, int y1, int startX, int startY) const {
	int beenHere[60][60];
	for (int i = 0; i <60; i++) { //x
		for (int k = 0; k < 60; k++) {//y
			beenHere[i][k] = 0;
		}


	}
	beenHere[x1][y1] = 1;
	
	stack<Coords>Cord;
	dirCheck(beenHere, Cord, startX, startY);
	//find(beenHere, Cord, startX, startY);

	while (!Cord.empty()) {
		Coords current = Cord.top();
		int cx = current.x();
		int cy = current.y();
		Cord.pop();
		if (cx == 56 && cy == 60) {
			return true; //sloved
		}
		dirCheck(beenHere, Cord, cx - 1, cy);
		dirCheck(beenHere, Cord, cx + 1, cy);
		dirCheck(beenHere, Cord, cx, cy - 1);
		dirCheck(beenHere, Cord, cx, cy + 1);
	}
	return false;
	//Previous implementation that did not function correctly
	//	startX = current.x();
	  // 	startY = current.y();

		
		/*void StudentWorld::find(int maze[56][60], stack<Coords>& qCords, int row, int col) const{

	if (personCanMove(row, col, false) && !maze[row][col]==1)
	{
		qCords.push(Coords(row, col));
		maze[row][col] = 1;
	}

}*/
		/*
			if (personCanMove(startX , startY, false)&&key==0) {
				if (beenHere[startX  ][startY] == 0) {
					Cord.push(Coords(startX, startY));
					beenHere[startX ][startY] = 1;
					dir = Actor::left;

					return true;
				}
			}
			 if (personCanMove(startX , startY, false)&&key==1) {
				if (beenHere[startX ][startY] == 0) {
					Cord.push(Coords(startX , startY));
					beenHere[startX ][startY] = 1;
					dir = Actor::right;
					return true;
				}

			}
			 if (personCanMove(startX, startY + 1, false)&&key==2) {
				if (beenHere[startX][startY + 1] == 0) {
					Cord.push(Coords(startX, startY ));
					beenHere[startX][startY ] = 1;
					dir = Actor::up;

					return true;
				}
			}
			
			if (personCanMove(startX, startY - 1, false)&&key==3) {
					if (beenHere[startX][startY + 1] == 0) {
						Cord.push(Coords(startX, startY));
						beenHere[startX][startY ] = 1;
						dir = Actor::down;

						return true;
					}

			}*/
		
			/*find(beenHere, Cord, xa - 1, ya);
			find(beenHere, Cord, xa + 1, ya);
			find(beenHere, Cord, xa, ya + 1);
			find(beenHere, Cord, xa, ya - 1);*/

			//beenHere[startX][startY] = 0;
	}




	 //can't



Actor::Direction StudentWorld::getProtestorDirection(Actor* a) const {
	int xinti = a->getX();
	int yinti = a->getY();
	//Actor::Direction  dr;
	int newX = xinti;
	int newY = yinti;
	//right
	a->newPos(newX, newY, 1, Actor::right);
	if (canLeaveOilField(xinti, yinti, newX, newY)) {
		return Actor::right; //return dir
	}
	//left
	newX = xinti;
	newY = yinti;
	a->newPos(newX, newY, 1, Actor::left);
	 if (canLeaveOilField(xinti, yinti, newX, newY) ){
		return Actor::left; //return dir
	}
	//up
	newX = xinti;
	newY = yinti;
	a->newPos(newX, newY, 1, Actor::up);
	 if (canLeaveOilField(xinti, yinti, newX, newY)) {
		return Actor::up; //return dir
	}
	//down
	//newX = xinti;
	//newY = yinti;
	////a->newPos(newX, newY, 1, Actor::down);
	// if (canLeaveOilField(xinti, yinti, newX, newY)) {
		return Actor::down; //return dir
	//}


}

void StudentWorld::dirCheck(int maze[56][60], stack<Coords>& qCords, int row, int col) const{

	if (personCanMove(row, col, false) && !maze[row][col]==1)
	{
		qCords.push(Coords(row, col));
		maze[row][col] = 1;
	}

}
bool StudentWorld::canSpawnPool(int x, int y) const { //can only spawn pool in 4 by 4 square without earth or another object
	for (int i = x; i < x + 4; i++) {
		for (int j = y; i < y + 4; j++) {
			if (atEarth(i, j)) {
				return false;
			}
		}
	}
	return true;

}
bool StudentWorld::tunnelManInSight(int x, int y, Actor::Direction direction)const { //recursively check if in sight
	if (x == m_tunnelman->getX() && y == m_tunnelman->getY()) {
		return true;
	}
	if (!personCanMove(x, y, false)) {
		return false;
	}

	switch (direction) {
	case Actor::right:
		return tunnelManInSight(x + 1, y, Actor::right);

	case Actor::left:
		return tunnelManInSight(x - 1, y, Actor::left);
	case Actor::up:
		return tunnelManInSight(x , y + 1, Actor::up);

	case Actor::down:
		return tunnelManInSight(x, y - 1, Actor::down);

	}
}





void StudentWorld::showDisplay(){
	int level = getLevel();
	int health = m_tunnelman->getHealth();
	int sonars = m_tunnelman->getSonars();
	int lives = getLives();
	int gold = m_tunnelman->getGold();
	int barrelamt = m_oilbarrels;
	int score = getScore();
	int squirt = m_tunnelman->getWater();
	string text = setDisplay(level, score, sonars, barrelamt, lives, health, gold, squirt);
	setGameStatText(text);
}
string StudentWorld::setDisplay(int level, int score, int sonar, int barrelsleft, int lives, int health, int gold, int squrits) const{
	string s = "Scr: ";
	s += format(score, 6, true);

	s += " Lvl: ";
	s += format(level, 2, false);

	s += " Lives: ";
	s += format(lives, 1, true);

	//convert to percentage instead of hitpoints
	int percent = health * 10;
	s += " Hlth: ";
	s += format(percent, 3, false); 
	s += "%";

	s += " Water:";
	s += format(squrits, 2, false);

	s += " Gld:";
	s += format(gold, 2, false);

	s += " Sonar:";
	s += format(sonar, 2, false);

	s += " Oil Left:";
	s += format(barrelsleft, 2, false);

	return s;

}
std::string StudentWorld::format(int in, int digits, bool zeros) const{

	char empty; 

	if (zeros)
		empty = '0';
	else
		empty = ' ';

	//if in is zero we need to format the zeros into string
	if (in == 0) {
		string s = "0";
		for (int i = 0; i < digits - 1; i++)
			s = empty + s;
		return s;
	}

	string s = to_string(in); //concationate the string
	for (int i = s.length(); i < digits; i++) {
		s = empty + s;
	}

	return s; 


}