package com.ece4564.group11.workout.sensor;

/*
 * Custom location package class which contains the users GPS data.
 * Should have just used location class instead.
 */

public class LocationPackage {

	double altitude_;
	double longitude_;
	double latitude_;
	float speed_;
	float bearing_;
	float accuracy_;
	long time_;

	public LocationPackage() {
		altitude_ = 0;
		longitude_ = 0;
		latitude_ = 0;
		speed_ = 0;
		bearing_ = 0;
		accuracy_ = 0;
		time_ = 0;
	}

	public void setLocation(double alt, double lon, double lat) {
		altitude_ = alt;
		longitude_ = lon;
		latitude_ = lat;
	}

	public void setTime(long t) {
		time_ = t;
	}

	public void setMovement(float s, float bear, float acc) {
		speed_ = s;
		bearing_ = bear;
		accuracy_ = acc;
	}

	public double getLat() {
		return latitude_;
	}

	public double getLon() {
		return longitude_;
	}

	public long getTime() {
		return time_;
	}

	public double getAltitude() {
		return altitude_;
	}

	public float getAcc() {
		return accuracy_;
	}
}
