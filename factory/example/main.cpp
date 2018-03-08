#include "factory.h"
#include <iostream>

using namespace std;

int main(){
	BFactory::init();
	B* b1 = BFactory::generate("D1");
	if(b1==nullptr){
		cerr<<"cannot get D1"<<endl;
	}
	cout<<b1->fun()<<endl;
	delete b1;
	
	B* b2 = BFactory::generate("D2");
	if(b2==nullptr){
		cerr<<"cannot get D2"<<endl;
	}
	cout<<b2->fun()<<endl;
	delete b1;
	return 0;
}

