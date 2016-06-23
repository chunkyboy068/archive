package com.HamServer.Servlets;

import java.io.IOException;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.HamServer.Storage.StorageStructure;

public class StoreStats extends HttpServlet{
	
	@Override
	protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException 
	{
		String[] uid = req.getParameterValues("userid");
		String[] fv = req.getParameterValues("fitlv");
		String[] hv = req.getParameterValues("hungerlv");
		if (uid == null || fv == null || hv == null) 
		{
			resp.sendError(HttpServletResponse.SC_BAD_REQUEST);
			System.out.println("Bad Request Recieved. Terminating Connection.");
		}
		else
		{
			System.out.println("GET on STORESTATS, parameters as follows:");
			System.out.println("USERID=" + uid[0]);
			System.out.println("FITLV=" + fv[0]);
			System.out.println("HUNGERLV=" + hv[0]);
			
			String userID = uid[0];
			int fit = Integer.parseInt(fv[0]);
			int health = Integer.parseInt(hv[0]);
			
			if (StorageStructure.getInstance().updateUser(userID, fit, health))
			{
				resp.setStatus(HttpServletResponse.SC_OK);
			}
			else
			{
				resp.setStatus(HttpServletResponse.SC_CONFLICT);
			}
		}
		
	}

	@Override
	//run once once, at account creation
	protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException 
	{
		String[] uid = req.getParameterValues("userid");
		//String[] fv = req.getParameterValues("fitlv");
		//String[] hv = req.getParameterValues("hungerlv");
		
		if (uid == null) {
			resp.sendError(HttpServletResponse.SC_BAD_REQUEST);
			System.out.println("Bad Request Recieved. Terminating Connection.");
		}
		else
		{
			String userID = uid[0];
			
			if (StorageStructure.getInstance().addUser(userID, 50, 50))
			{
				resp.setStatus(HttpServletResponse.SC_OK);
			}
			else
			{
				resp.setStatus(HttpServletResponse.SC_CONFLICT);
			}
		}
	}

}
