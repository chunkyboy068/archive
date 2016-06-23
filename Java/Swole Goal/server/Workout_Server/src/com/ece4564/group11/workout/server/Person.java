package com.ece4564.group11.workout.server;

/**
 * Person Class which represents a single person and their GPS coordinates
 */

public class Person {

	String name_;
	float latitude_;
	float longitude_;

	public Person(String n, float lat, float lon) {
		name_ = n;
		latitude_ = lat;
		longitude_ = lon;
	}

	public String getName() {
		return name_;
	}

	public float getLat() {
		return latitude_;
	}

	public float getLon() {
		return longitude_;
	}

	public boolean isCloseTo(Person other) {
		float latMin = (float) (latitude_ - (float) .01);
		float latMax = (float) (latitude_ + (float) .01);
		float lonMin = (float) (longitude_ - (float) .01);
		float lonMax = (float) (longitude_ + (float) .01);

		if (other.getLat() > latMin && other.getLat() < latMax) {
			if (other.getLon() > lonMin && other.getLon() < lonMax) {
				return true;
			}
		}

		return false;
	}
}
