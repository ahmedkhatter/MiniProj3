#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

struct A {
	int x;
	int y;
	int f;
	int g;
	int h;
	int layer;
};

int ManDist(int x1,int x2, int y1, int y2) {
	return abs(x1 - x2) + abs(y1 - y2);
}

int FindMin(vector <A> vect) {
	int min = vect[0].f; 
	for (int i = 1; i < vect.size(); i++)
		if (min < vect[i].f)
			min = vect[i].f;

	return min;
	
}

int main() {

	vector<A> V1;
	int width, height,startx,starty,targetx,targety;
	cout << "Enter grid width" <<endl;
	cin >> width;
	cout << "Enter grid height" << endl;
	cin >> height;
	cout << "Enter Start cell" << endl;
	cin >> startx;
	cin >> starty;
	cout << "Enter Target cell" << endl;
	cin >> targetx;
	cin >> targety;

	for (int i = 0; i < width; i++) {
		for (int g = 0; g < height; g++) {
			A temp;
			temp.x = i;
			temp.y = g;
			temp.g = ManDist(i,startx,g,starty);
			temp.h = ManDist(i, targetx, g, targety);
			temp.f = temp.g + temp.h;
			V1.push_back(temp);
		}
	}

	cout<<FindMin(V1)<<endl;
	

	system("pause");
	return 0;
}