package com.HamServer.Servlets;

import java.io.IOException;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.HamServer.Storage.PlayerData;
import com.HamServer.Storage.StorageStructure;

public class GetStats extends HttpServlet
{

	@Override
	protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException 
	{	
		String[] uid = req.getParameterValues("friendid");
		
		if (uid == null) 
		{
			resp.sendError(HttpServletResponse.SC_BAD_REQUEST);
			System.out.println("Bad Request Recieved. Terminating Connection.");
		}
		else
		{
			System.out.println("GET on GETSTATS, parameters as follows:");
			System.out.println("USERID="+uid[0]);
			
			String userID = uid[0];
			PlayerData pd = StorageStructure.getInstance().getUser(userID);
			if ( pd != null)
			{
				resp.setStatus(HttpServletResponse.SC_OK);
				resp.getWriter().write("FitLevel:" + pd.getFitLevel() + "HungerLevel:" + pd.getHungerLevel());
			}
			else
			{
				resp.setStatus(HttpServletResponse.SC_CONFLICT);
			}
		}
	}
	
}
