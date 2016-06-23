package main;

import logger.LogWriter;
import logic.QuoteGrabber;

import org.eclipse.jetty.server.Server;
import org.eclipse.jetty.webapp.WebAppContext;

public class Main {

	public static void main(String[] args) throws Exception 
	{
		LogWriter.getInstance().log("Initializing Server...");
		QuoteGrabber.getInstance().getQuote();
		Server s = new Server(80);
		WebAppContext context = new WebAppContext();
		context.setWar("war");
		context.setContextPath("/");
		s.setHandler(context);
		s.start();
		s.join();	
	}

}
