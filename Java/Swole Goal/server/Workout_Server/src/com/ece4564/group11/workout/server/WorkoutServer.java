package com.ece4564.group11.workout.server;

/**
 * This file contains the main. Executes new server on port 80
 */

import org.eclipse.jetty.server.Server;
import org.eclipse.jetty.webapp.WebAppContext;


public class WorkoutServer {
	
	public static void main(String[] args) throws Exception
	{	
		Server s = new Server(80);
		WebAppContext context = new WebAppContext();
		context.setWar("war");
		context.setContextPath("/");
		s.setHandler(context);
		s.start();
		s.join();	
	}
}
