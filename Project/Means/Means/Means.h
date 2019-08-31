#pragma once
#include<iostream>
#include<string>
#include<math.h>
#include<time.h>

using namespace std;

#define error 1e-3

typedef unsigned int uint;

class Means
{
public:
	uint pointsnum;
	uint dimension;
	uint clusternum;

	double** Weight = NULL;
	double** Points = NULL;
	double** Cluster = NULL;

};