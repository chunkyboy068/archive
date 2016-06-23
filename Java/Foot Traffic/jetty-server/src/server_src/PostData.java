package server_src;

import java.io.IOException;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.json.simple.JSONObject;

public class PostData extends HttpServlet{
	@Override
	protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException 
	{
		resp.getWriter().write("Please use a POST request to access this URI");
	}
	@Override
	protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException 
	{
		System.out.println("Post on PostData");
		
		String[] t = req.getParameterValues("time");
		String[] t2 = req.getParameterValues("temp");
		String[] l1 = req.getParameterValues("lon");
		String[] l2 = req.getParameterValues("lat");
		String[] l3 = req.getParameterValues("light");
		String[] s = req.getParameterValues("status");
		
		if (t == null)
		{
			resp.setContentType("text/html");
			resp.getWriter().write("Need Time Value");
		}
		else if (t2 == null)
		{
			resp.setContentType("text/html");
			resp.getWriter().write("Need Temperature Value");
		}
		else if (l1 == null)
		{
			resp.setContentType("text/html");
			resp.getWriter().write("Need Longitude Value");
		}
		else if (l2 == null)
		{
			resp.setContentType("text/html");
			resp.getWriter().write("Need latitude Value");
		}
		else if (l3 == null)
		{
			resp.setContentType("text/html");
			resp.getWriter().write("Need Light Value");
		}
		else if (s == null)
		{
			resp.setContentType("text/html");
			resp.getWriter().write("Need Status");
		}
		else
		{
		
			String time;
			String lon;
			String temp;
			String light;
			String lat;
			String status;
		
			time =t[0];
			lon = l1[0];
			temp = t2[0];
			light = l3[0];
			lat = l2[0];
			status = s[0];

			System.out.println(time + lon + temp + light + lat + status);
			
			MainServlet.storedData_.addNew(time, lat, lon, light, temp, status);
		}
	}
}
