package com.HamServer;
import org.eclipse.jetty.server.Server;
import org.eclipse.jetty.webapp.WebAppContext;

public class HamServer {

	/**
	 * @param args
	 */
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
