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
	int used;
};

int width, height, startx, starty, targetx, targety, start_layer, target_layer;

int get_elem(int x, int y, int lay) {
	return (lay-1)*width*height + (height*x + y);
}


int ManDist(int x1,int x2, int y1, int y2) {
	return abs(x1 - x2) + abs(y1 - y2);
}

int FindMin(vector <A> vect) {
	int min = vect[0].f;
	int min_elem = 0;
	for (int i = 1; i < vect.size(); i++)
		if (min > vect[i].f) {
			min = vect[i].f;
			min_elem = i;
		}

	return min_elem;

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
			temp.used = 0;
			temp.x = i;
			temp.y = g;
			temp.layer = lay;
			temp.g = ManDist(startx, i, starty, g);
			
			if ((lay==1 && start_layer==3 || lay ==3 && start_layer==1) && (abs(starty-temp.y)!=0))
				temp.g += 20;
			else if (lay != start_layer)
				temp.g += 10;

			temp.h = ManDist(targetx, i, targety, g);

			if ((lay == 1 && target_layer == 3 || lay == 3 && target_layer == 1) && (abs(targety - temp.y) != 0))
				temp.h += 20;
			else if (lay != target_layer)
				temp.g += 10;
			temp.f = temp.g + temp.h;
			V1.push_back(temp);
		}
	}


	vector<A> route;
	int source_elem = get_elem(startx,starty,start_layer);
	int source_g = V1[source_elem].g;
	int source_x = startx;
	int source_y = starty;
	int source_layer = start_layer;
	route.push_back(V1[source_elem]);
	do {
		
		int up = -1, down = -1, left = -1, right = -1;
		vector<A> myvect;

			int laye;
			if (source_layer == 3)
				laye = 1;
			else
				laye = source_layer + 1;

			if ((source_x == targetx && source_y == targety && laye == target_layer)|| (source_y != targety && (laye == 2) || (source_x != targetx && (laye==1||laye==3))))
			{
				up = get_elem(source_x, source_y, laye);
				V1[up].g = source_g + 10;
				V1[up].f = V1[up].g + V1[up].h;
				if(V1[up].used == 0)
					myvect.push_back(V1[up]);
			}
			int laye2;
			if (source_layer == 1)
				laye2 = 3;
			else
				laye2 = source_layer - 1;
			if ((source_x == targetx && source_y == targety && laye2 == target_layer) ||( source_y != targety && (laye2 == 2) || (source_x != targetx && (laye2 == 1 || laye2 == 3))))
			{
				down = get_elem(source_x, source_y, laye2);
				V1[down].g = source_g + 10;
				V1[down].f = V1[down].g + V1[down].h;
				if (V1[down].used == 0)
					myvect.push_back(V1[down]);
			}

			if (source_layer == 1 || source_layer == 3) {
				if (source_x != targetx) {
					if (source_x - 1 > 0)
					{
						left = get_elem(source_x - 1, source_y, source_layer);
						V1[left].g = source_g + 1;
						V1[left].f = V1[left].g + V1[left].h;
						if (V1[left].used == 0)
							myvect.push_back(V1[left]);
					}

					if (source_x + 1 <= width)
					{
						right = get_elem(source_x + 1, source_y, source_layer);
						V1[right].g = source_g + 1;
						V1[right].f = V1[right].g + V1[right].h;
						if (V1[right].used == 0)
							myvect.push_back(V1[right]);
					}
				}
			}

			else {

				if (source_y - 1 > 0 && source_y != targety)
				{
					left = get_elem(source_x - 1, source_y-1, source_layer);
					V1[left].g = source_g + 1;
					V1[left].f = V1[left].g + V1[left].h;
					if (V1[left].used == 0)
						myvect.push_back(V1[left]);
				}

				if (source_y + 1 <= height && source_y != targety)
				{
					right = get_elem(source_x , source_y+1, source_layer);
					V1[right].g = source_g + 1;
					V1[right].f = V1[right].g + V1[right].h;
					if (V1[right].used == 0)
						myvect.push_back(V1[right]);
				}
			}
		
		int element = FindMin(myvect);
		route.push_back(myvect[element]);
		source_g = myvect[element].g;
		source_x = myvect[element].x;
		source_y = myvect[element].y;
		V1[get_elem(source_x,source_y,source_layer)].used=1;
		source_layer = myvect[element].layer;
	} while (source_x != targetx || source_y != targety || source_layer != target_layer);
	V1[get_elem(targetx, targety, target_layer)].used = 1;
	cout << V1[get_elem(targetx, targety, target_layer)].g<<endl;

	/*for (int lay = 1; lay <= 3; lay++){
		cout << endl<<endl;
		for (int i = 0; i < width; i++) {
			cout << endl;
			for (int g = 0; g < height; g++) {
				cout << V1.back().used<<"   ";
				V1.pop_back();
			
			}
		}
		}*/


	system("pause");
	return 0;
}