//Christina De Cesaris
#include "BballRoster.h"
#include<iostream>
#include<string>
using namespace std;
BballRoster::Player::Player(string fname, string lname, SomeType val){ //constructor for each new player
	m_fname = fname;
	m_lname = lname;
	m_val = val;
	next = nullptr;
	prev = nullptr;
}
BballRoster:: BballRoster() : head(nullptr), m_size(0){} //defualt constructor

BballRoster::BballRoster(const BballRoster& bbr) : head(nullptr), m_size(0) {//copy constructor 
	Player* m = bbr.head;
	if (m != nullptr) { //if bbr.head is not empty
		m_size = bbr.m_size; // set this.size to bbr.size

		head = new Player(m->m_fname, m->m_lname, m->m_val); //set it's address to a new node, copy over values of bbr.head to that node
		
		m = m->next; //point m to the next node on bbr
	} 
	//
	Player* n = head; //pointer pointing to the new.head
	while (m != nullptr) {
		if (n == head) { //if n points to the first node
			Player* p = new Player(m->m_fname, m->m_lname, m->m_val); //make a new player with address in p, copy information from the current location of m
			
			n->next = p; //link the new head node to p
			p->prev = head; //link new node's prev to head			n->next; // move along
			n=n->next; // move n to point at p's node
			m = m->next; //continue m down the bbr
		}
		else { // n is not pointing to the first node of the new list
			Player* x = new Player(m->m_fname, m->m_lname, m->m_val);
			n->next = x;
			x->prev = n;
			n = n->next;
			m = m->next;



		}
	}

} 

const BballRoster& BballRoster::operator=(const BballRoster& bbr) {
	if (this == &bbr) //ensure we are not assigning something to itself!
		return *this;
	if (!this->rosterEmpty()) { //delete any previous memory contained in this
		for (int i = 0; i < this->howManyPlayers(); i++) {
			string ftemp, ltemp;
			SomeType x;
			this->choosePlayer(i, ftemp, ltemp, x);
			this->renouncePlayer(ftemp,ltemp);
		}
		
	}
	BballRoster temp = bbr; //copy constructor
	swapRoster(temp); //swap pointers
	return *this;
} //assignment operator 

BballRoster::~BballRoster() {
	Player* m = head; //of what we are destroying
	
	while (m != nullptr) {
		Player* toDelete = m;
		m = m->next;
		delete toDelete;
	}


} //destructor

bool BballRoster::rosterEmpty() const {
	if (m_size > 0) {
		return false;
	}
	else {
		return true;
	}
}

int BballRoster::howManyPlayers() const {
	return m_size;
}

bool BballRoster::signPlayer(const std::string& firstName, const std::string&

	lastName, const SomeType& value) {
	//Player* m = head;
	if (head == nullptr) { //empty list //!= changed from == --
		 //placed in side of code --
		Player* added = new Player(firstName, lastName, value);	//--changed/ /here we don't worry about sorting becase it is the first player
		head = added;
		m_size++;

		return true; //work here is done
	}
	//otherwise we must add alpabetically
	Player* m = head;
	while (m != nullptr) {
		Player* p = new Player(firstName, lastName, value);

		
		if (m->m_lname == p->m_lname && m->m_fname == p->m_fname) { //ensure we don't have same last and first names here
			return false;
		}

		if (m->m_lname == p->m_lname) {
			//compare first names and sort accordingly
			//do the first name shibang
			if (head->m_fname > p->m_fname == true) { //means if m->firstname at head is lower aphabetically than the new node, the == true isn't needed just for me visually
				//new node becomes new head, old head is linked after 
				m->prev = p; 
				p->next = m;
				head = p;
				m_size++;
				return true; //we added our player
			}
			if (m->m_fname > p->m_fname == true) {//so is the next guy apha lower than our new guy
				//if yah, then our new guy goes on top of the old guy
				m->prev->next = p; //point the guy before old guy's next to p, has to happen before we change m-> prev its gonna be hell
				p->prev = m->prev;
				m->prev = p; // old guys prev, point to new guy
				p->next = m; //new guy next,  point to old guy
				m_size++;


				return true; //done here
			}
			else { //new guy is alpha lower than the current 
				//before moving along we have to make sure we aren't at the last node because if we are at last node and move along, m will pt at null 
				if (m->next == nullptr) {//new guy is offically at the bottom, link em to the rear!
					m->next = p;
					p->prev = m;
					m_size++;

					return true;

				}
				m = m->next;

			}

		}
		else {
			//compare last names and sort accordinly
			if (head->m_lname > p->m_lname == true) { //means if m->lastname at head is lower aphabetically than the new node, the == true isn't needed
				//new node becomes new head, old head is linked after 
				m->prev = p; 
				p->next = head;
				head = p;
				m_size++;

				return true; //we added our player
			}
			//if we get here, then our head is more apha than our new player 
			//so we must go down the list and compare our new player to all the other guys
			//m = m->next; //on to the next one
			if (m->m_lname > p->m_lname == true ) {//so is the next guy apha lower than our new guy
				//if yah, then our new guy goes on top of the old guy
				m->prev->next = p; //point the guy before old guy's next to p, has to happen before we change m-> prev its gonna be hell
				p->prev = m->prev;
				m->prev = p; // old guys prev, point to new guy
				p->next = m; //new guy next,  point to old guy
				m_size++;

				return true; //done here
			}
			else { //new guy is alpha lower than the current 
				//before moving along we have to make sure we aren't at the last node because if we are at last node and move along, m will pt at null 
				if (m->next == nullptr) {//new guy is offically at the bottom, link em to the rear!
					m->next = p;
					p->prev = m;
					m_size++;

					return true;

				}
				m = m->next;  

			}


		}
		
	}
	 
	
	
	m_size++;

	return true;
}

bool BballRoster::resignPlayer(const std::string& firstName, const std::string&
	lastName, const SomeType& value) {
	if (head == nullptr) {
		return false;
	}
	if (playerOnRoster(firstName, lastName)) {
		Player* m = head;
		while (m != nullptr) {
			if ( m != nullptr && m->m_fname == firstName && m->m_lname == lastName ) {
				m->m_val = value;
			}
			
				m = m->next;

			
		}

		return true;
	}
	else {
		return false;
	}
	
}

bool BballRoster::signOrResign(const std::string& firstName, const std::string&
	lastName, const SomeType& value) {
	
	if (playerOnRoster(firstName, lastName)) { //call resign
		resignPlayer(firstName, lastName, value);
		return true;
	}
	else {
		signPlayer(firstName, lastName, value);
		return true;

	}
}
// If full name is equal to a name currently in the list, then
	// make that full name no longer map to the value it currently
	// maps to, but instead map to the value of the third parameter;
	// return true in this case. If the full name is not equal to
	// any full name currently in the list then add it and return
	// true. In fact, this function always returns true.

bool BballRoster::renouncePlayer(const std::string& firstName, const
	std::string& lastName) {
	if (playerOnRoster(firstName, lastName)) {
		Player* m = head;
		while (m != nullptr) {

			if (m->m_lname == lastName && m->m_fname == firstName) {
				if (m == head ) {
					if (m->next == nullptr) {
						delete m; //one node
						head = nullptr;
					}
					else {
						head = head->next;
						delete m;
						m = nullptr;
					}
					m_size--;
					return true;
				}

				else if (m->next == nullptr) { //this is proabably not needed 
					m->prev->next = nullptr;
					delete m;
					head = nullptr;
					m_size--;
					return true;
				}
				else if (m->next != nullptr) {
					m->next->prev = m->prev;
					m->prev->next = m->next;
					delete m;
					m_size--;
					return true;

				}
			

				

			}
			m = m->next;
		}
		//return false;
		return true;

	}
	else {
		return false;
	}
}

bool BballRoster::playerOnRoster(const std::string& firstName, const
	std::string& lastName) const {
	Player* m = head;
	if (m == nullptr) {
		return false;
	}
	while (m != nullptr) {
		if (m->m_fname == firstName && m->m_lname == lastName) {
			return true;
		}
		m = m->next;
	}
	return false;
}

bool BballRoster::lookupPlayer(const std::string& firstName, const std::string&
	lastName, SomeType& value) const {
	if (playerOnRoster(firstName, lastName)) {
		Player* m = head;
		while (m != nullptr) {
			if (m->m_lname == lastName && m->m_fname == firstName) {
				value = m->m_val;
				return true;
			}
			m = m->next;
		}
		//return false;
	}
	return false;
}


bool BballRoster::choosePlayer(int i, std::string& firstName, std::string&
	lastName, SomeType& value) const {
	if (i < 0 || i > m_size) {
		return false;
	}
	else {
		Player* m = head;
		int count = 0;
		while (count<i && m!= nullptr) {
			m = m->next;
			count++;
		}// bring m to index of i
		if (m != nullptr)
		{
			firstName = m->m_fname;
			lastName = m->m_lname;
			value = m->m_val;
			return true;
		}

		return false;
	}
}

void BballRoster::swapRoster(BballRoster& other) {
	Player* temp = other.head;
	other.head = head;
	head = temp;

	int temp_siz = other.m_size;
	other.m_size = m_size;
	m_size = temp_siz;

}


void BballRoster::dump() const {
	Player* m = head;
	while (m != nullptr ) {
		cerr << m->m_lname << " " << m->m_fname << " " << m->m_val << endl;

		m = m->next;

	}
}
///Non member functions
bool joinRosters(const BballRoster& bbOne,
	const BballRoster& bbTwo,
	BballRoster& bbJoined) {
	bool dupes = false;
	string first, last;
	SomeType val;
	if (&bbOne == &bbJoined ) {
		BballRoster temp;//create an empty new list
		temp = bbJoined;
		joinRosters(bbOne, bbTwo, temp);
		return true;
		//ensure if we pass the same list in both bbjoined and bbone we don't accidentally loose contents
	}
	if (&bbTwo == &bbJoined) {
		BballRoster temp;//create an empty new list
		temp=bbJoined;
		joinRosters(bbOne, bbTwo, temp);
		return true;
		//bbJoined.swapRoster(temp);

		
	}
	if (!bbJoined.rosterEmpty()) { //is bbJoined empty if not make it so
		//delete all contents of bbJoined
		BballRoster temp;//create an empty new list
		bbJoined.swapRoster(temp);  //swap with bbJoined so now we have an empty list
	
		

	}
	if (!bbOne.rosterEmpty() && bbTwo.rosterEmpty()) {//if only bbOne has content then just set result to bbOne via ssianment operator 
		bbJoined = bbOne;
	}
	if (bbOne.rosterEmpty() && !bbTwo.rosterEmpty()) {//if only bbTwo has content then just set result to bbTwo via ssianment operator 
		bbJoined = bbTwo;
	}

	string dupefname, dupelname;

	//ensure both one and two are not empty
	if (!bbOne.rosterEmpty() && !bbTwo.rosterEmpty()) {
		string tempfname, templname;
		SomeType tempval;
		

		for (int i = 0; i < bbTwo.howManyPlayers(); i++) {
			bbTwo.choosePlayer(i, first, last, val); //get player from two
			bbJoined.signPlayer(first, last, val);//add to joined
		}
		for (int i = 0; i < bbOne.howManyPlayers(); i++) {
			bbOne.choosePlayer(i, first, last, val); //get player from two
			bbJoined.signPlayer(first, last, val);//add to joined
		}

		if (bbOne.howManyPlayers() < bbTwo.howManyPlayers()) {
			for (int i = 0; i < bbOne.howManyPlayers(); i++) {
				bbOne.choosePlayer(i, first, last, val);
				for (int j = 0; j < bbTwo.howManyPlayers(); j++) {
					bbTwo.choosePlayer(j, tempfname, templname, tempval);
					if (tempfname == first && templname == last && tempval != val) {
						bbJoined.renouncePlayer(tempfname, templname);
						dupes = true;
					}
				}
			}

		}
		else {
			for (int i = 0; i < bbTwo.howManyPlayers(); i++) {
				bbTwo.choosePlayer(i, first, last, val);
				for (int j = 0; j < bbOne.howManyPlayers(); j++) {
					bbOne.choosePlayer(j, tempfname, templname, tempval);
					if (tempfname == first && templname == last && tempval != val) {
						bbJoined.renouncePlayer(tempfname, templname);
						dupes = true;
					}
				}
			}

		}

	}


	if (dupes) {
		return false;
	}
	return true;
		//go down roster one, get each player's name and val one at a time
		//store those values in a temp and see if those players with those values
		//exist at all on the second list if NOT then player add vals from one to joined and add vals from two to joined
		//if we have a same name different value case, then we have to not add that name at all to joined, maybe have a continue?
		//maybe if that is the case, then we store that name in another temp, and we cehc if it is on the list when we are adding
		//if we find that name in this case, we don't added it at all, we do this for both lists so it isn't added at all
		//the last case is if we have the same name and same val twice, we only want to add the name once in this case
		//another way would be to add everything, the sign player won't allow double adds.. so that is taken care of actually
		//in this case, our issue becames same name and different value, hmm in this case actually
		//we can look into the list and if we have two players same name and different values, remove both of them.
	



}

void checkRoster(const std::string& fsearch,
	const std::string& lsearch,
	const BballRoster& bbOne,
	BballRoster& bbResult) {
	if (&bbOne == &bbResult) {//dont be passing in the same list 
		BballRoster temp;//create an empty new list
		//temp = bbResult;
		checkRoster(fsearch,lsearch, bbOne, temp);
		return; //so we don't go throught the whole shebang again and cause a mess tbh
		//ensure if we pass the same list in both bbResult and bbone we don't accidentally loose contents
	}
	if (!(bbResult.rosterEmpty())) {
		BballRoster temp;
		bbResult.swapRoster(temp); //ensure we don't ahve anything in Result
	}
	if (!bbOne.rosterEmpty()) { //if bbOne isn't empty lets go
		string first, last;
		SomeType val;
		for (int i = 0; i < bbOne.howManyPlayers(); i++) {
			bbOne.choosePlayer(i, first, last, val);
			if (fsearch == first && lsearch == last) {
				bbResult.signPlayer(first, last, val);
			}
			if (fsearch == "*" && lsearch != "*") {
				if (lsearch == last) {
					bbResult.signPlayer(first, last, val);

				}
			}
			if (fsearch != "*" && lsearch == "*") {
				if (fsearch == first) {
					bbResult.signPlayer(first, last, val);

				}
			}
			if (fsearch == "*" && lsearch == "*") {
				bbResult = bbOne;

			}
		}
	}
	
}
//returns bb result as a copy of elements which match the search elements
//look up wild card implementations if needed
//ensure bbResult is EMPTY because it cannt contain other eelements
//how about if * is first name then add all with matching last name
//if * in last name add all with matching first name
//if no star, match based on first and last add elements who match only
//if both stars are passed, then copy input list to empty
