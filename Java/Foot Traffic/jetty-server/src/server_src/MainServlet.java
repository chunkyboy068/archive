package server_src;

import java.io.IOException;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.eclipse.jetty.server.Server;
import org.eclipse.jetty.webapp.WebAppContext;

import HourData.DataConstruct;
import HourData.HourData;

public class MainServlet extends HttpServlet {
	
	public static DataConstruct storedData_;
	
	public static void main(String[] args) throws Exception{
		
		storedData_ = new DataConstruct();
		
		Server s = new Server(7634);
		
		WebAppContext context = new WebAppContext();
		context.setWar("war");
		context.setContextPath("/");
		s.setHandler(context);
		s.start();
		s.join();
	}

	@Override
	protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws IOException
	{
		resp.setContentType("text/html");
		resp.getWriter().write("Please access/getdata or /postdata");
	}

	@Override
	protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException 
	{
		resp.setContentType("text/html");
		System.out.println("Please access /getdata or /postdata");
		
	}

}
