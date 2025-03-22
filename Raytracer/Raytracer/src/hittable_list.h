#pragma once
#include "hittable.h"
#include <vector>
/**
 * @class hittable_list
 * @brief A collection of hittable objects that is itself hittable.
 *
 * This class represents a scene or group of objects in a raytracer.
 * It inherits from hittable so it can be intersected with rays.
 * Essentially implements the "Composite" design pattern for scene objects.
 */
class hittable_list : public hittable {
public:
	/* Vector of shared pointers to hittable objects in the scene */
	std::vector<shared_ptr<hittable>> objects;

	/** Default constructor creates an empty list */
	hittable_list() {}

	/** Constructor that initializes with a single object */
	hittable_list(shared_ptr<hittable> object) { add(object); }

	/** Clear all objects from the list */
	void clear() { objects.clear(); }

	/** Add an object to the list */
	void add(shared_ptr<hittable> object) {
		objects.push_back(object);
	}

	/**
	 * @brief Determine if a ray hits any object in the list
	 *
	 * Checks each object in the list for intersection with the ray.
	 * If multiple objects are hit, records only the closest hit.
	 * This is critical for correct visibility determination in raytracing.
	 *
	 * @param r The ray to test for intersection
	 * @param ray_tmin Minimum parametric distance along ray to consider (prevents self-intersection)
	 * @param ray_tmax Maximum parametric distance along ray to consider
	 * @param rec Record to store information about the hit
	 * @return True if any object was hit, false otherwise
	 */
	bool hit(const ray& r, double ray_tmin, double ray_tmax, hit_record& rec) const override {
		hit_record temp_rec;
		bool hit_anything = false;
		auto closest_so_far = ray_tmax;

		// Iterate through all objects in the scene
		for (const auto& object : objects) {
			// Check if the ray hits this object between valid bounds
			if (object->hit(r, ray_tmin, closest_so_far, temp_rec)) {
				hit_anything = true;
				// Update the closest hit distance to ensure we only record the closest hit
				closest_so_far = temp_rec.t;
				// Store this hit as our current best hit
				rec = temp_rec;
			}
		}

		return hit_anything;
	}
};