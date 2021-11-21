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
	virtual void show_main() {
		printf("Here is nothing :(\n");
	}
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
		printf("Heap()\n");
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
		printf("~Heap()\n");
		delete S1;
		delete S2;
	}
};

class Someone : public Something {
private: bool alive;
public:
	void show_main() override {
		printf("The main prorerty is liveliness\n");
	}
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

class SomethingMeasured : public Something {     //a class without constructors & destructor
private: int size=0;
public:
	void show_main() override {
		printf("The main prorerty is size\n");
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

	printf("\n\nStatic creation of Someones:\n");
	Someone _s1;
	Someone _s2("hij", 3,true);
	Someone _s3(_s2);
	//

	printf("\n\nDynamic creation of Someones & putting Someone into the variable of the class Something:\n");
	Someone* _s4 = new Someone("klm", 4,true);  //each time both of Somathing's and Someone's constructors are called
	_s4->changeliveliness(false);               //_s5 will not have such method since it'll still be Something
	Something* _s5 = new Someone(*_s4);

	//

	printf("\n\nDeleting dynamically created Someones:\n");
	printf("   Deleting _s4:\n");
	delete _s4;
	printf("   Deleting _s5:\n");               
	delete _s5;                                 //only Something's destructor is called
	//                                            if Something's destructor is virtual, both destructors will be called
	//

	printf("\n\nStatic creation of Heaps:\n");
	Heap H1;
	Heap H2(H1);

	//

	printf("\n\nDynamic creation of Heaps:\n");
	Heap *H3 = new Heap();
	Heap *H4 = new Heap(*H3);

	//

	printf("\n\nDeleting dynamically created Heaps\n");
	printf("   Deleting H3:\n"); 
	delete H3;
	printf("   Deleting H4:\n"); 
	delete H4;

	//

	printf("\n\nStatic & dynamic creation of SomethingMeasured, deleting dynamically created SomethingMeasured:\n");
	SomethingMeasured M1;  
	Something* M2 = new SomethingMeasured;
	SomethingMeasured* M3 = new SomethingMeasured;     //in all cases Something's default constructor is called
	delete M2;                                        
	delete M3;                                         //in both cases Something's destructor is called

	//

	printf("\n\nCreating different versions of Something\n");
	Something A1;
	Something *A2 = new Someone();
	Something *A3 = new SomethingMeasured();

	//

	printf("\n\nUsing overrided virtual method of each Something\n");
	A1.show_main();
	A2->show_main();
	A3->show_main();

	//

	printf("\n\nDeleting dynamically versions if Something:\n");
	delete A2;                                         //again only Something's constructor is called
	delete A3;

	//

	printf("\n\nDeleting statically created Someones, Something, Heaps:\n");
}