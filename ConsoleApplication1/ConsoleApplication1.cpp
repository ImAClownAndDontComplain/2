#include <iostream>
#include <stdio.h>
#include <string>

using namespace std;
string liveliness(bool alive) {
	if (alive == true)return "alive";
	else return "lifeless";
}

class Something {
protected:
	string name;
	int age;                            
public:
	Something() {
		printf("Something()\n");
		name = "default", age = 0;
	}
	Something(string name, int age) {
		printf("Something(string name, int age)\n");
		this->name = name, this->age=age;
	}
	Something(const Something&S) {
		printf("Something(const Something &S)\n");
		name = S.name, age = S.age;
	}
	~Something() {
		cout << "~Something()\nit was a " << age << "-year-old " << name << endl;
	}
	void rename(string s) {
		cout << "New name of \"" << name << "\" is \"" << s  <<"\""<< endl;
		name = s;
	}
	void resetC();
};
void Something::resetC() {
	cout << "New age of \"" << name << "\" is \"" << 0 << "\"" << endl;
	age = 0;
}

class Heap {
protected:
	Something* S1;
	Something* S2;
public:
	Heap(){
		printf("Heap()");
		S1 = new Something();
		S2 = new Something();
	}
	Heap(Something S1, Something S2) {
		printf("Heap(Something* S1, Something * S2)\n");
		this->S1 = new Something(S1), this->S2 = new Something(S2);
	}
	Heap(const Heap& H) {
		printf("Heap(const Heap& H)\n");
		S1 = new Something(*(H.S1)), S2 = new Something(*(H.S2));
	}
	~Heap() {
		printf("\n~Heap()\n");
		delete S1;
		delete S2;
	}
};

class Someone : public Something {
private: bool alive;
public:
	Someone() : Something() {
		printf("Someone()\n");
		alive = true;
	}
	Someone(string name, int age, bool alive) :Something(name, age) {
		printf("Someone(string name, int age, bool alive)\n");
		this->alive = alive;
	}
	Someone(const Someone& S) {
		name = S.name, age = S.age, alive = S.alive;
		printf("Someone(const Someone &S)\n");
	}
	~Someone() {
		cout << "~Someone()\nit was a " << age << "-year-old and " << liveliness(alive) << " "<< name << endl;
	}
	void changeliveliness(bool alive) {
		cout << "New liveliness of \"" << name << "\" is \"" << liveliness(alive) << "\"" << endl;
		this->alive = alive;
	}
};

int main()
{
	//
	printf("Static creation of Something:\n");
	Something s1;
	Something s2("abc", 1);
	Something s3(s2);
	//
	printf("\n\nDynamic creation of Something:\n");
	Something* s4 = new Something();
	Something* s5 = new Something("def",2);
	Something* s6 = new Something(*s5);
	s6->rename("defg");
	s6->resetC();
	//
	printf("\n\nDeleting dynamically created Something:\n");
	delete s4;
	delete s5;
	delete s6;
	//
	printf("\n\nStatic creation of Someone:\n");
	Someone _s1;
	Someone _s2("hij", 3,true);
	Someone _s3(_s2);
	printf("\n\nDynamic creation of Someone & putting Someone into the variable of the class Something:\n");
	Someone* _s4 = new Someone("klm", 4,true);  //each time both of Somathing's and Someone's constructors are called
	Something* _s5 = new Someone(*_s4);
	_s4->changeliveliness(false);               //_s5 doesn't have such method since it's still Something
	printf("\n\nDeleting dynamically created Someone:\n");
	printf("   Deleting _s4:\n");
	delete _s4;
	printf("   Deleting _s5:\n");               //only Something's destructor is called
	delete _s5;
	printf("\n\nDeleting statically created Someone and Something:\n");
}