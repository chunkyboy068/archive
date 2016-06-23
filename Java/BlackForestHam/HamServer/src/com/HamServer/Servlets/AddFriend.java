package com.HamServer.Servlets;

import java.io.IOException;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.HamServer.Storage.StorageStructure;

public class AddFriend extends HttpServlet
{
	@Override
	protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException 
	{
		String[] uid = req.getParameterValues("userid");
		String[] fid = req.getParameterValues("friendid");
		
		if (uid == null || fid == null) 
		{
			resp.sendError(HttpServletResponse.SC_BAD_REQUEST);
			System.out.println("Bad Request Recieved. Terminating Connection.");
		}
		else
		{
			System.out.println("GET on ADDFRIEND, parameters as follows:");
			System.out.println("USERID=" + uid[0]);
			System.out.println("FRIENDID=" + fid[0]);
			
			String userID = uid[0];
			String friendID = fid[0];
			
			if (StorageStructure.getInstance().addNewFriend(userID, friendID))
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
