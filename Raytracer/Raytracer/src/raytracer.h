#pragma once

#include <cmath>
// #include <cstdlib>
#include <iostream>
#include <limits>
#include <memory>
#include <random>

// C++ Std Usings

using std::make_shared;
using std::shared_ptr;

// Constants

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility Functions

inline double degrees_to_radians(double degrees) {
	return degrees * pi / 180.0;
}

inline double random_double() {
	// Thread-local generator and distribution for thread safety
	// Using mt19937 over std::rand() for higher quality random generation, thread_local is optional since not currently multi threading
	// static thread_local std::mt19937 generator(std::random_device{}());
	// static thread_local std::uniform_real_distribution<double> distribution(0.0, 1.0);
	// return distribution(generator);
	static std::uniform_real_distribution<double> distribution(0.0, 1.0);
	static std::mt19937 generator;
	return distribution(generator);
}

inline double random_double(double min, double max) {
	// Returns a random real in [min,max).
	return min + (max - min)*random_double();
}

// Common Headers

#include "color.h"
#include "interval.h"
#include "ray.h"
#include "vec3.h"
