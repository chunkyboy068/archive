package servlets;

import java.io.FileInputStream;
import java.io.IOException;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import logger.LogWriter;
import logic.PageServer;
import logic.ResponseWriter;

public class Education extends HttpServlet{
	@Override
	protected void doGet(HttpServletRequest req, HttpServletResponse resp)
			throws ServletException, IOException {

		FileInputStream fis = PageServer.getInstance().getPage("education");
		ResponseWriter rw = new ResponseWriter(resp);

		if (rw.respond(fis)) {
			LogWriter.getInstance().log(
					"Successfully Served Education to " + req.getRemoteAddr());
			rw = null;
		}

	}
}
