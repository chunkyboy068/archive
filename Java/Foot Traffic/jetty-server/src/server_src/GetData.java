package server_src;

import java.io.IOException;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.json.simple.JSONObject;

public class GetData extends HttpServlet{
	
	@Override
	protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
		
		resp.getWriter().write("Please use a POST request to access this URI");
	}
	
	@Override
	protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException 
	{
		String[] lat = req.getParameterValues("lat");
		String[] lon = req.getParameterValues("lon");
		String[] description = req.getParameterValues("description");
		
		String hour = req.getParameterValues("hour")[0];
		
		JSONObject jOb;
		if (description == null && lat == null && lon == null)
		{
			jOb = null;
		}
		else if (description == null)
		{
			jOb = MainServlet.storedData_.get(lat[0], lon[0], hour);
		}
 		else if (lat == null && lon == null)
		{
			jOb = MainServlet.storedData_.get(description[0], hour);
		}
 		else
 		{
 			jOb = null;
 		}
		
		System.out.println(jOb.toJSONString());
		
		resp.setContentType("application/json");
		resp.getWriter().write(jOb.toJSONString());
	}



}
