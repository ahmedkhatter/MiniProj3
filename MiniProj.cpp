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

int width, height, startx, starty, targetx, targety, start_layer, target_layer;


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

void UpdateVect(vector<A>& V1, A elem) {

	for (int lay = 1; lay <= 3; lay++)
		for (int i = 0; i < width; i++) {
			for (int g = 0; g < height; g++) {
				A temp;
				temp.x = i;
				temp.y = g;
				temp.g = ManDist(i, elem.x, g, elem.y);
				temp.h = ManDist(i, targetx, g, targety);
				temp.f = temp.g + temp.h + 10 * abs(lay - target_layer) + 10 * abs(lay - elem.layer);
				V1[lay*(width*i + g)];
			}
		}

}

int main() {

	vector<A> V1;
	cout << "Enter grid width" <<endl;
	cin >> width;
	cout << "Enter grid height" << endl;
	cin >> height;
	cout << "Enter Start cell" << endl;
	cin >> startx;
	cin >> starty;
	cin >> start_layer;
	cout << "Enter Target cell" << endl;
	cin >> targetx;
	cin >> targety;
	cin >> target_layer;


	for(int lay=1;lay<=3;lay++)
	for (int i = 0; i < width; i++) {
		for (int g = 0; g < height; g++) {
			A temp;
			temp.x = i;
			temp.y = g;
			temp.g = ManDist(i,startx,g,starty);
			temp.h = ManDist(i, targetx, g, targety);
			temp.f = temp.g + temp.h + 10*abs(lay-target_layer)+ 10*abs(lay-start_layer);
			V1.push_back(temp);
		}
	}


	vector<A> route;
	
	do{
		int elem = FindMin(V1);
		route.push_back(V1[elem]);
		UpdateVect(V1, V1[elem]);
	} while (route.back().x != targetx && route.back().y != targety);



	system("pause");
	return 0;
}