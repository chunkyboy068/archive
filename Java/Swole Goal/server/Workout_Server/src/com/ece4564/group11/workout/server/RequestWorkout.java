package com.ece4564.group11.workout.server;

/**
 * Servlet which responds to the request for a single workout based on id.
 * Responds to /requestone.
 */

import java.io.IOException;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class RequestWorkout extends HttpServlet {

	@Override
	protected void doGet(HttpServletRequest req, HttpServletResponse resp)
			throws ServletException, IOException {
		String[] uuid = req.getParameterValues("id");

		if (uuid == null) {
			resp.sendError(HttpServletResponse.SC_BAD_REQUEST);
		} else {
			System.out.println("External Workout Request...");
			String id = uuid[0];

			try {
				int workout_id = Integer.parseInt(id);
			} catch (NumberFormatException nfe) {
				resp.sendError(HttpServletResponse.SC_BAD_REQUEST);
				return;
			}

			String workout = DatabaseManager.getInstance()
					.getIDFromDataBase(id);

			resp.setStatus(HttpServletResponse.SC_ACCEPTED);

			if (workout == null) {
				resp.getWriter().write("");
			} else {
				resp.getWriter().write(workout);
			}
		}

	}

	@Override
	protected void doPost(HttpServletRequest req, HttpServletResponse resp)
			throws ServletException, IOException {
		resp.sendError(HttpServletResponse.SC_METHOD_NOT_ALLOWED);
	}

}
