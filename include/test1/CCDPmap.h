#pragma once
#include <vector>
#include <test1/Gmap.h>

#ifndef P
	#define PI 3.141593
#endif // !


class CCDPmap { //get Local CCDP map
private:
	arma::rowvec local_x_rng;
	arma::rowvec local_y_rng;
	float local_x_len;
	float local_y_len;
	int local_num_x;
	int local_num_y;
	float grid;
	int ndir;
	int nvis;
	int H_step;
	float threshold_track;
	
	arma::mat local_map;


	//arma::cube Cost_visual;
	//arma::cube Cost_avoid;
	//std::vector<arma::cube> Cost_track;
	//std::vector<arma::cube> Cost_const; // avoid + const

public:
	CCDPmap(Gmap* ptr_gmap, arma::rowvec x_rng, arma::rowvec y_rng, float epsilon);
	~CCDPmap();


	void grid_resize(int factor);

	void setLocalmap(Gmap* ptr_gmap, arma::rowvec x_rng, arma::rowvec y_rng);
	arma::mat getLocalmap() const;
	void printLocalmap() const;

	float getGrid();
	int getLocal_num_x();
	int getLocal_num_y();

	/*
	void setCost_visual(int y, int x);
	void setCost_avoid(int y, int x);
	void setCost_track(int y, int x, int num);
	void setCost_const(int y, int x, int num);


	arma::cube getCost_visual() const;
	arma::cube getCost_avoid() const;
	std::vector<arma::cube> getCost_track() const;
	std::vector<arma::cube> getCost_const() const;
	*/

	//void CCDPmap::initCostfunc(int y, int x, int num);

	//ccdp.xs/ys -> (num-Áß¾Ó)/grid·Î ´ëÃ³
	//ccdp.glen -> grid
	//ccdp.gmap -> local_map


};
