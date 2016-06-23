package com.ece4564.group11.workout.server;

/**
 * Servlet which both returns and stores data using the database. The GET request
 * actually gets the requester's stored workouts based on UUID and the post is
 * used for storing a workout. Responds to /store
 */

import java.io.IOException;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class StoreData extends HttpServlet {

	@Override
	protected void doGet(HttpServletRequest req, HttpServletResponse resp)
			throws ServletException, IOException {
		String[] uuid = req.getParameterValues("uuid");

		if (uuid == null) {
			resp.sendError(HttpServletResponse.SC_BAD_REQUEST);
		} else {
			String ident = uuid[0];
			resp.setStatus(HttpServletResponse.SC_ACCEPTED);
			System.out.println("GET workout Request:\nUUID: " + ident);
			String jStr = DatabaseManager.getInstance().getFromDatabase(ident);
			System.out.println("Sending Search Result to Client...");
			resp.getWriter().write(jStr);
		}
	}

	@Override
	protected void doPost(HttpServletRequest req, HttpServletResponse resp)
			throws ServletException, IOException {
		String[] name = req.getParameterValues("id");
		String[] jsonString = req.getParameterValues("data");
		String[] uuid = req.getParameterValues("uuid");

		if (name == null || jsonString == null || uuid == null) {
			resp.sendError(HttpServletResponse.SC_BAD_REQUEST);
			System.out.println("Bad Request Recieved. Terminating Connection.");
		} else {
			String workout_name = name[0];
			String jData = jsonString[0];
			String identifier = uuid[0];

			System.out.println("StoreData Post Received:");
			System.out.println("NAME: " + workout_name);
			System.out.println("JSONSTRING: " + jData);
			System.out.println("UUID: " + identifier);
			System.out.println("Storing...");

			if (DatabaseManager.getInstance().addToDatabase(jData,
					workout_name, identifier)) {
				System.out.println("Addition Success");
				resp.setStatus(HttpServletResponse.SC_NO_CONTENT);
			} else {
				System.out.println("Addition Failed");
				resp.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR);
			}
		}

	}

}
