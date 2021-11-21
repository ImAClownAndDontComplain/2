#include <iostream>
#include <stdio.h>
#include <string>

using namespace std;

class Something {
protected:
	string name;
	int age;                            
public:
	Something() {
		name = "default", age = 0;
		printf("Something()\n");
	}
	Something(string name, int age) {
		printf("Something(string name, int age)\n");
		this->name = name, this->age=age;
	}
	Something(const Something&S) {
		name = S.name, age = S.age;
		printf("Something(const Something &S)\n");
	}
	~Something() {
		cout << "\n~Someone()\nit was a " << age << "-year-old " << name << endl;
	}
	void rename(string s) {
		name = s;
	}
	void resetC();
};
void Something::resetC() {
	age = 0;
}

string liveliness(bool alive) {
	if (alive == true)return "alive ";
	else return "lifeless ";
}

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
		cout << "\n~Someone()\nit was a " << age << "-year-old and " << liveliness(alive) << name << endl;
	}
	void changeliveliness(bool alive) {
		this->alive = alive;
	}
};

class CoupleOfShapes {
private:
	Something* A;
	Something* B;
public:
};


int main()
{
	Someone* A = new Someone("a", 1,true);
	A->rename("aa");
	A->resetC();
	A->changeliveliness(false);
	delete A;
}