package com.ece4564.group11.workout.network;

/**
 * This class is a AsyncTask inherited class that receive the workout plans stored in server.
 */

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;

import org.apache.http.HttpResponse;
import org.apache.http.ParseException;
import org.apache.http.client.HttpClient;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.impl.client.DefaultHttpClient;
import org.json.simple.JSONObject;
import org.json.simple.JSONArray;
import org.json.simple.parser.JSONParser;

import com.ece4564.group11.workout.fragments.PlannerFragment;

import android.os.AsyncTask;
import android.util.Log;

public class GetDataNetworkTask extends
		AsyncTask<Void, Void, HashMap<String, HashMap<String, List<String>>>> {

	private PlannerFragment pf_;
	String address_;
	String uuid_;
	private HashMap<String, HashMap<String, List<String>>> cache_ = new HashMap<String, HashMap<String, List<String>>>();
	private HashMap<String, List<String>> workoutPlanMap_;

	public GetDataNetworkTask() {
		address_ = null;
		uuid_ = null;
	}

	public GetDataNetworkTask(String address, String uuid, PlannerFragment pf) {
		uuid_ = uuid;
		address_ = address;
		pf_ = pf;
	}

	@Override
	protected HashMap<String, HashMap<String, List<String>>> doInBackground(
			Void... params) {
		HttpClient client = new DefaultHttpClient();
		HttpGet httpget = new HttpGet(address_ + "store?" + "uuid=" + uuid_);
		List<String> result = new ArrayList<String>();
		try {
			HttpResponse response = client.execute(httpget);

			BufferedReader reader = new BufferedReader(new InputStreamReader(
					response.getEntity().getContent()));
			Log.d("Get status:", response.getStatusLine().toString());
			JSONParser parser = new JSONParser();
			try {
				JSONObject jOb = (JSONObject) parser.parse(reader);
				Log.d("Parsed JSONObject", jOb.toString());

				Iterator itr = (Iterator) jOb.keySet().iterator();
				while (itr.hasNext()) {
					workoutPlanMap_ = new HashMap<String, List<String>>();
					String name = (String) itr.next();
					JSONObject plan = (JSONObject) parser.parse(jOb.get(name)
							.toString());

					Iterator planItr = (Iterator) plan.keySet().iterator();
					while (planItr.hasNext()) {
						List<String> workoutValues = new ArrayList<String>();
						String workName = (String) planItr.next();
						JSONArray workout = (JSONArray) parser.parse(plan.get(
								workName).toString());

						JSONObject workoutTimeObj = (JSONObject) workout.get(0);
						JSONObject restTimeObj = (JSONObject) workout.get(1);
						JSONObject setObj = (JSONObject) workout.get(2);

						String workoutTimeName = "Workout Time";
						String restTimeName = "Rest time";
						String setName = "Sets";
						String workoutTime = workoutTimeObj
								.get(workoutTimeName).toString();
						String restTime = restTimeObj.get(restTimeName)
								.toString();
						String set = setObj.get(setName).toString();

						workoutValues.add(workoutTime);
						workoutValues.add(restTime);
						workoutValues.add(set);
						Log.d("Workout Array", workoutValues.toString());
						workoutPlanMap_.put(workName, workoutValues);
					}
					cache_.put(name, workoutPlanMap_);
					result.add(name);
				}
				Log.d("WorkoutPlanMap", workoutPlanMap_.toString());
				Log.d("Cache", cache_.toString());
			} catch (ParseException e) {
				e.printStackTrace();
			}

		} catch (Exception e) {
			e.printStackTrace();
		}
		Log.d("RETURN KEY", result.toString());
		return cache_;
	}

	@Override
	protected void onPostExecute(
			HashMap<String, HashMap<String, List<String>>> result) {
		pf_.getDataNetworkTaskResult(result);
	}

}
