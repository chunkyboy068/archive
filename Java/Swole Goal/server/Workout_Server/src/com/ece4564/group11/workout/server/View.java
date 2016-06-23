package com.ece4564.group11.workout.server;

/**
 * This servlet is used to view all the available workouts on the database.
 * Responds to any URI besides the ones already allocated to the other servlets.
 */

import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class View extends HttpServlet {

	@Override
	protected void doGet(HttpServletRequest req, HttpServletResponse resp)
			throws ServletException, IOException {
		System.out.println("Printing All Database");
		ArrayList<WorkoutEntry> workouts = DatabaseManager.getInstance()
				.getAll();
		PrintWriter pw = resp.getWriter();

		if (workouts == null) {
			resp.sendError(HttpServletResponse.SC_NO_CONTENT);
		} else {
			resp.setContentType("text/html");
			resp.setStatus(HttpServletResponse.SC_OK);

			pw.write("<h1> Available Workouts </h1> <br /> ");
			while (workouts.size() != 0) {
				WorkoutEntry workout = workouts.remove(0);

				pw.write("<b>ID: " + workout.getID() + "<br> Name: "
						+ workout.getName() + "<br></b>");

				pw.write("<table border=\"1\" width=\"30%\"> ");
				pw.write("<tr> <td> Exercise </td> <td> Workout Time </td> <td> Rest Time </td> <td> Sets </td> </tr>");
				pw.write(workout.toHTMLTableString());
				pw.write("</table>");

				pw.write("<br>");
			}

			pw.write("</table>");
		}
	}

	@Override
	protected void doPost(HttpServletRequest req, HttpServletResponse resp)
			throws ServletException, IOException {
		resp.sendError(HttpServletResponse.SC_METHOD_NOT_ALLOWED);
	}

}
