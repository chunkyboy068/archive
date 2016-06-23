package com.ece4564.group11.workout.network;

/**
 * This class gets the muscle group data for the planner fragment.
 */

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.URI;
import java.net.URISyntaxException;

import org.apache.http.HttpResponse;
import org.apache.http.client.HttpClient;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.impl.client.DefaultHttpClient;

public class GetHtml {
	public String getHtmlStrings(String muscleGroup) throws IOException,
			URISyntaxException {
		BufferedReader in = null;
		String data = null;
		try {
			HttpClient client = new DefaultHttpClient();
			// http://www.bodybuilding.com/exercises/list/muscle/selected/<MUSCLE_GROUP>
			// URI website = new
			// URI("http://www.bodybuilding.com/exercises/list/muscle/selected/"+
			// muscleGroup);
			URI website = new URI(
					"http://www.bodybuilding.com/exercises/list/muscle/selected/"
							+ muscleGroup);
			HttpGet request = new HttpGet();
			request.setURI(website);
			HttpResponse response = null;

			try {
				response = client.execute(request);
				// System.out.println("after execute");
			} catch (IOException e) {
				System.err.println("DEBUG: IOexception called");
			} finally {
				// System.out.println("DEBUG: Http Response Returned");
			}

			in = new BufferedReader(new InputStreamReader(response.getEntity()
					.getContent()));

			StringBuffer sb = new StringBuffer("");
			String l = "";
			String nl = System.getProperty("line.separator");
			while ((l = in.readLine()) != null) {
				sb.append(l + nl);
			}
			in.close();
			data = sb.toString();
			return data;
		} finally {
			if (in != null) {
				try {
					in.close();
					return data;
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		}
	}
}
