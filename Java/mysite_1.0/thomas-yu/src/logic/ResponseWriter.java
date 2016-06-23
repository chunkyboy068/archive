package logic;

import java.io.FileInputStream;
import java.io.PrintWriter;

import javax.servlet.http.HttpServletResponse;

import logger.LogWriter;

public class ResponseWriter 
{
	private HttpServletResponse resp_;
	
	public ResponseWriter()
	{
		resp_ = null;
	}
	
	public ResponseWriter(HttpServletResponse response)
	{
		resp_ = response;
	}
	
	public boolean respond(FileInputStream file)
	{
		try
		{
			if (file == null)
			{
				resp_.sendError(HttpServletResponse.SC_NOT_FOUND);
				return false;
			}
			
			PrintWriter pw = resp_.getWriter();
			resp_.setStatus(HttpServletResponse.SC_ACCEPTED);
			resp_.setContentType("text/html");
			
			while(file.available() > 0)
			{
				pw.write(file.read());
			}
			
			return true;
		}
		catch (Exception e)
		{
			LogWriter.getInstance().log("ERROR. COULD NOT RESPOND TO CLIENT." + e.getMessage());
			return false;
		}
	}
}
