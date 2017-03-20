#pragma once
#include <vector>

#define ARMA_USE_CXX11
#include </usr/include/armadillo>

class Gmap {
private:
	float grid;
	float glen;
	std::vector<float> x_rng;
	std::vector<float> y_rng;
	float x_len;
	float y_len;
	int num_yaxis;
	int num_xaxis;
	std::vector<std::vector<float>> list_object; //object: [x, y, xlen, ylen, degree]
	arma::rowvec xaxis;
	arma::rowvec yaxis;

	
	arma::mat global_map;

public:
	Gmap();
	Gmap(int map_number, bool object);
	~Gmap();

	void load_map(int num_map, bool object);
	int obj_collision(float y, float x);

	float getGrid() const;
	std::vector<float> getXrng() const;
	std::vector<float> getYrng() const;
	arma::rowvec get_xaxis();
	arma::rowvec get_yaxis();
	
	void set_global_map();
	arma::mat getGlobalmap() const;
	void printGlobalmap() const;

	void getObjects() const;
	void setObjects(float x, float y, float xlen, float ylen, float degree);


	
};
