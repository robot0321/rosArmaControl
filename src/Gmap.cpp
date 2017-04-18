#include <test1/Gmap.h>
#include <iostream>

Gmap::Gmap(){
	Gmap::load_map(1, true);
	Gmap::set_global_map();
}

Gmap::Gmap(int map_number, bool object=true){
	Gmap::load_map(map_number, object);
	Gmap::set_global_map();
}

Gmap::~Gmap(){
	int num_list = list_object.size();
	if(num_list>0){
		for(int i=0; i<num_list; i++){
			list_object[num_list -1 - i].clear();
		}
		list_object.clear();
	}

	//delete global_map;
}



void Gmap::load_map(int num_map, bool object){
	switch(num_map){
	case 1:
		grid = 0.1;
		glen = 1;
		int a[2] = { 1,2 };
		x_rng = {-10, 10};
		y_rng = {-10, 10};
		x_len = x_rng[1] - x_rng[0];
		y_len = y_rng[1] - y_rng[0];
		if (object) {
			Gmap::setObjects(2, 2, 2, 3, 0); //box1
			Gmap::setObjects(-4.5, -4.5, 4, 4, 0); //box2
			Gmap::setObjects(-3.5, 4, 3, 3, 0); //box3
			Gmap::setObjects(3, -7, 3, 3, 0); //box4
			Gmap::setObjects(7, 5.5, 2, 2, 0); //box5
		}
		break;
	
	}
}

int Gmap::obj_collision(float y, float x){
	int obj=0;
	for(int k=0;k<list_object.size();k++){
		obj = (int)(list_object[k][0]-list_object[k][2]/2.0 <= x && list_object[k][0]+list_object[k][2]/2.0>x && list_object[k][1]-list_object[k][3]/2.0<=y && list_object[k][1]+list_object[k][3]/2.0>y);
		if(obj==1) break;
	}

	return obj;
}

float Gmap::getGrid() const {return grid;}
std::vector<float> Gmap::getXrng() const {return x_rng;}
std::vector<float> Gmap::getYrng() const {return y_rng;}


void Gmap::set_global_map() {
	num_yaxis = int((y_rng[1] - y_rng[0]) / grid);
	num_xaxis = int((x_rng[1] - x_rng[0]) / grid);

	global_map = arma::mat(num_yaxis,num_xaxis); //global_map[y][x]
	for (int i = 0; i<num_yaxis; i++) {
		for (int j = 0; j<num_xaxis; j++) {
			global_map(num_yaxis-1-i,j) = obj_collision(i*grid - y_len / 2.0, j*grid - x_len / 2.0);
		}
	}
	xaxis = arma::rowvec(num_xaxis);
	yaxis = arma::rowvec(num_yaxis);
	for (int i = 0; i < num_xaxis; i++) { xaxis(i) = x_rng[0] + grid * i; }
	for (int i = 0; i < num_yaxis; i++) { yaxis(i) = y_rng[0] + grid * i; }

}

arma::mat Gmap::getGlobalmap() const{return global_map;}
arma::rowvec Gmap::get_xaxis() {return xaxis;}
arma::rowvec Gmap::get_yaxis() { return yaxis; }

void Gmap::printGlobalmap() const {
	std::cout << "********** Gmap **********" << std::endl;
	for (int i = 0; i<num_yaxis; i++) {
		for (int j = 0; j<num_xaxis; j++) {
			if (i == int(y_rng[1] / grid)-1) {
				std::cout << "^";
			}
			else if (j == -int(x_rng[0] / grid)+1) {
				std::cout << "<";
			}
			else {
				std::cout << global_map(i, j);// << " ";
			}
		}
		std::cout << std::endl;
	}
	std::cout << "************************" << std::endl;
}


void Gmap::getObjects() const {
	int num_list = list_object.size();
	int loop_count = 0;
	if (num_list>0) {
		for (int i = 0; i<num_list; i++) {
			list_object[i];
		}
	}
	else {
		std::cout << "# of object list is " << num_list << std::endl;
	}
}

void Gmap::setObjects(float x, float y, float xlen, float ylen, float degree) {
	int num_list = list_object.size();

	list_object.push_back(std::vector<float>());

	list_object[num_list].push_back(x);
	list_object[num_list].push_back(y);
	list_object[num_list].push_back(xlen);
	list_object[num_list].push_back(ylen);
	list_object[num_list].push_back(degree);

}
