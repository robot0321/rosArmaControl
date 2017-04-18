#include <test1/CCDPmap.h>
#include <iostream>

CCDPmap::CCDPmap(Gmap* ptr_gmap, arma::rowvec x_rng, arma::rowvec y_rng, float epsilon=0.3) {
	grid = ptr_gmap->getGrid();
	ndir = 10;
	nvis = 20;
	H_step = 10;
	threshold_track = epsilon;
	
	
	CCDPmap::setLocalmap(ptr_gmap, x_rng, y_rng);
}

CCDPmap::~CCDPmap() {
	//delete local_map;
	//delete Cost_visual;
	//delete Cost_avoid;
	//delete Cost_track;
	//delete Cost_const;
}

void CCDPmap::grid_resize(int factor) {
	int new_x_num = local_num_x/factor;
	int new_y_num = local_num_y/factor;
	arma::mat new_map_tmp = arma::mat(new_y_num, new_x_num);

	for (int i = 0; i < new_y_num; i++) {
		for (int j = 0; j < new_x_num; j++) {
			new_map_tmp(i, j) = local_map(2 * i, 2 * j); //Need to edit the resizing way
		}
	}
	//delete memory of local_map pointer
	//delete local_map;

	local_map = new_map_tmp;
	grid = grid*factor;
	local_num_x = new_x_num;
	local_num_y = new_y_num;

}

void CCDPmap::setLocalmap(Gmap* ptr_gmap, arma::rowvec x_rng, arma::rowvec y_rng) {
	local_x_rng = x_rng;
	local_y_rng = y_rng;
	local_x_len = local_x_rng(1) - local_x_rng(0);
	local_y_len = local_y_rng(1) - local_y_rng(0);
	local_num_x = local_x_len / grid;
	local_num_y = local_y_len / grid;
	
	arma::mat global_map = ptr_gmap->getGlobalmap();
	std::vector<float> global_Xrng = ptr_gmap->getXrng();
	std::vector<float> global_Yrng = ptr_gmap->getYrng();

	local_map = arma::mat(local_num_y, local_num_x);
	for (int i = 0; i < local_num_y; i++) {
		for (int j = 0; j < local_num_x; j++) {
			local_map(i,j) = global_map(i + abs(int((local_y_rng(1) - global_Yrng[1]) / grid)) + 1, j + int((local_x_rng(0) - global_Xrng[0]) / grid));
		}
	}
}

arma::mat CCDPmap::getLocalmap() const {return local_map;}

void CCDPmap::printLocalmap() const {
	std::cout << "********** Local map **********" << std::endl;
	for (int i = 0; i < local_num_y; i++) {
		for (int j = 0; j < local_num_x; j++) {
			if (i == int(local_y_rng(1) / grid)-1) {
				std::cout << "^";
			}
			else if (j == -int(local_x_rng(0) / grid)+1) {
				std::cout << "<";
			}
			else {
				std::cout << local_map(i, j);
			}
		}
		std::cout << std::endl;
	}
	std::cout << "******************************" << std::endl;
}

float CCDPmap::getGrid() {
	return grid;
}

int CCDPmap::getLocal_num_x() {
	return local_num_x;
}

int CCDPmap::getLocal_num_y() {
	return local_num_y;
}

/*
arma::cube CCDPmap::getCost_visual() const {return Cost_visual;}
arma::cube CCDPmap::getCost_avoid() const {return Cost_avoid;}
std::vector<arma::cube> CCDPmap::getCost_track() const {return Cost_track; }
std::vector<arma::cube> CCDPmap::getCost_const() const {return Cost_const;}

void CCDPmap::setCost_visual(int y, int x) {
	Cost_visual = arma::cube(y, x,H_step+1);
	for (int tt = 0; tt < H_step; tt++) {

	}
}
void CCDPmap::setCost_avoid(int y, int x) {
	Cost_avoid = arma::cube(y, x, H_step+1);
}
void CCDPmap::setCost_track(int y, int x, int num) {
	Cost_track.push_back(arma::cube(y, x, num));
}
void CCDPmap::setCost_const(int y, int x, int num) {
	Cost_const.push_back(arma::cube(y, x, num));
}

*/



/*

int main() {
	std::vector<float> x = { -10,10 };
	std::vector<float> y = { -10,10 };
	system("PAUSE");
	Gmap* a = new Gmap();
	a->printGlobalmap();
	system("PAUSE");
	CCDPmap* b = new CCDPmap(a, x, y, 0.3);
	b->printLocalmap();
	system("PAUSE");
	b->grid_resize(3);
	b->printLocalmap();
	system("PAUSE");
	

	delete b;
	delete a;


	return 0;
}

*/
