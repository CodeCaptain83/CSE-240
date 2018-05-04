#include <iostream>
#include <fstream>

using namespace std;

int foo(int x, int y){ // size-n problem
	if (y <= 0) // stopping condition
		return x; // return value of stopping condition
	else if (x <= 0) // stopping condition
		return y; // return value of stopping condition
	else if (x >= y) // from size-(n-1) to size-n problem
		return x + foo(x - 2, y); // size-m problem
	else if (x < y) // from size-(n-1) to size-n problem
		return y + foo(x, y - 3); // size-m problem
}

int main()
{
	cout << foo(5, 6);
}
