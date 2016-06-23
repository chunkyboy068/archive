package com.ece4564.group11.workout.server;

/**
 * Servlet which returns a quote to the requester. Responds to /quote
 *
 */

import java.io.IOException;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class RequestQuote extends HttpServlet {

	@Override
	protected void doGet(HttpServletRequest req, HttpServletResponse resp)
			throws IOException {
		resp.setContentType("text/html");
		resp.getWriter().write(QuoteGrabber.getInstance().getQuote());
	}

	@Override
	protected void doPost(HttpServletRequest req, HttpServletResponse resp)
			throws ServletException, IOException {
		resp.sendError(HttpServletResponse.SC_METHOD_NOT_ALLOWED);
	}

}