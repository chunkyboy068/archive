package logger;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Date;

public class LogWriter 
{
	private static LogWriter log_ = new LogWriter();

	private File logFile_;
	private FileWriter fw_;
	private BufferedWriter bw_;
	
	
	public static LogWriter getInstance()
	{
		return log_;
	}
	
	private LogWriter()
	{
		logFile_ = new File("log.txt");
		try 
		{
			if (logFile_.exists())
			{
				logFile_.delete();
				System.out.println("Deleting old log");
			}
			
			logFile_.createNewFile();
			System.out.println("SUCCESS: LOG FILE CREATED. WRITING INTO LOG FROM NOW ON.");
			
			fw_ = new FileWriter(logFile_.getAbsoluteFile());
			bw_ = new BufferedWriter(fw_);
			this.log("Starting Logging...");
		} 
		catch (IOException e) 
		{
			System.out.println("ERROR: CANNOT CREATE LOG FILE. CANCELING SETUP AND EXITING.");
			e.printStackTrace();
			System.exit(0);
		}
	}
	
	public boolean log(String msg)
	{
		try 
		{
			DateFormat dateFormat = new SimpleDateFormat("MM/dd/yyyy HH:mm:ss");
			Date date = new Date();
			bw_.append(dateFormat.format(date) + ": ");
			bw_.append(msg + "\r\n");
			bw_.flush();
			return true;
			
		} 
		catch (IOException e)
		{
			System.out.println("ERROR: COULD NOT WRITE TO LOG");
			System.out.println("FAILED WRITE:" + msg);
			return false;
		}
	}

}
