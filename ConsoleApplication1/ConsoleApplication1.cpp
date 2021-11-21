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
	Something(string name, int corners) {
		printf("Something(string name, int age)\n");
		this->name = name, this->age=age;
	}
	Something(const Something&S) {
		name = S.name, age = S.age;
		printf("Shape(const Shape &S)\n");
	}
	~Something() {
		cout << "~Shape()\nit was a " << age << "-year-old " << name << endl;
	}
	void rename(string s) {
		name = s;
	}
	void resetC();
};
void Something::resetC() {
	age = 0;
}

class CoupleOfShapes {
private:
	Something* A;
	Something* B;
public:
};


int main()
{
	Something* A = new Something("a", 1);
	A->rename("aa");
	A->resetC();
	delete A;
}