package com.ece4564.group11.workout.server;

/**
 * Class used to encapsulate an entry in the database.
 */

import java.util.Iterator;
import java.util.Set;

import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;
import org.json.simple.parser.ParseException;

public class WorkoutEntry {

	String name_;
	int id_;
	String data_;

	public WorkoutEntry(String name, int dbID, String dat) {
		name_ = name;
		id_ = dbID;
		data_ = dat;
	}

	public String toHTMLTableString() {
		String HTMLString = "";

		JSONParser parser = new JSONParser();
		try {
			JSONObject jOb = (JSONObject) parser.parse(data_);
			String exList = jOb.get(name_).toString();
			JSONObject workoutSep = (JSONObject) parser.parse(exList);

			Set<String> exerciseNames = workoutSep.keySet();
			Iterator<String> exNameIter = exerciseNames.iterator();
			while (exNameIter.hasNext()) {
				String name = exNameIter.next();
				JSONArray params = (JSONArray) workoutSep.get(name);
				JSONObject workoutTime = (JSONObject) params.get(0);
				JSONObject restTime = (JSONObject) params.get(1);
				JSONObject setNum = (JSONObject) params.get(2);

				HTMLString += "<tr><td>" + name + "</td>";
				HTMLString += "<td>" + workoutTime.get("Workout Time")
						+ "</td>";
				HTMLString += "<td>" + restTime.get("Rest time") + "</td>";
				HTMLString += "<td>" + setNum.get("Sets") + "</td></tr>";
			}

			return HTMLString;

		} catch (ParseException e) {
			e.printStackTrace();
			return "";
		}
	}

	public String getName() {
		return name_;
	}

	public int getID() {
		return id_;
	}
}
