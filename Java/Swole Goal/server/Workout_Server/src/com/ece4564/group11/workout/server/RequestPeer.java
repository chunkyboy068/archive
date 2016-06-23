package com.ece4564.group11.workout.server;

/**
 * Servlet which is used to respond when a person sends GPS coordinates
 * to the server. Responds to /request
 * 
 * Identification is UUID based
 */

import java.io.IOException;
import java.util.ArrayList;
import java.util.UUID;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.json.simple.JSONObject;

public class RequestPeer extends HttpServlet {

	@Override
	protected void doGet(HttpServletRequest req, HttpServletResponse resp)
			throws ServletException, IOException {
		resp.sendError(HttpServletResponse.SC_METHOD_NOT_ALLOWED);
	}

	@Override
	protected void doPost(HttpServletRequest req, HttpServletResponse resp)
			throws ServletException, IOException {
		String[] name = req.getParameterValues("name");
		String[] longitude = req.getParameterValues("lon");
		String[] latitude = req.getParameterValues("lat");
		String[] top = req.getParameterValues("top");
		String[] bot = req.getParameterValues("bot");
		String[] state = req.getParameterValues("state");

		float lon;
		float lat;
		Long msb;
		Long lsb;
		String person;
		String action = state[0];

		try {
			msb = Long.parseLong(top[0]);
			lsb = Long.parseLong(bot[0]);
			UUID uuid = new UUID(msb, lsb);

			if (action.equals("stay")) {
				lon = Float.parseFloat(longitude[0]);
				lat = Float.parseFloat(latitude[0]);
				person = name[0];

				System.out.println("Adding Person: " + person + " UUID: "
						+ uuid.toString());
				System.out.println("Latitude = " + lat + " Longitude = " + lon);

				Person pData = new Person(person, lat, lon);

				resp.setContentType("application/json");
				resp.setStatus(HttpServletResponse.SC_OK);
				resp.getWriter().write(pullCurrent(pData).toJSONString());
				System.out.println("Response sent.");
				processAdd(uuid, pData);
			} else if (action.equals("leave")) {
				System.out.println("Removing UUID: " + uuid.toString());
				removePerson(uuid);
				resp.setStatus(HttpServletResponse.SC_NO_CONTENT);
			} else {
				resp.sendError(HttpServletResponse.SC_BAD_REQUEST);
			}
		} catch (Exception e) {
			resp.sendError(HttpServletResponse.SC_BAD_REQUEST);
		}
	}

	private void processAdd(UUID id, Person newPerson) {
		ProximityData.getInstance().addNew(id, newPerson);
		System.out.println("Person Successfully Added To Collection.");
	}

	private JSONObject pullCurrent(Person newPerson) {
		ArrayList<String> people = ProximityData.getInstance().getLocal(
				newPerson);

		if (people.size() == 0) {
			return new JSONObject();
		} else {
			JSONObject jOb = new JSONObject();
			int counter = 0;
			for (String name : people) {
				jOb.put(name, counter);
				counter++;
			}
			return jOb;
		}
	}

	private void removePerson(UUID uuid) {
		ProximityData.getInstance().removeUUID(uuid);
		System.out.println("Remove Success.");
	}

}
