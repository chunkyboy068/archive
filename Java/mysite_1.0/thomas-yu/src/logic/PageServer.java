package logic;

import java.io.File;
import java.io.FileInputStream;
import java.util.HashMap;
import java.util.List;

import org.jdom2.Document;
import org.jdom2.Element;
import org.jdom2.input.SAXBuilder;

import logger.LogWriter;


public class PageServer
{
	private static PageServer pServer_ = new PageServer();
	
	private HashMap<String, File> pageList_;
	
	public static PageServer getInstance()
	{
		return pServer_;
	}
	
	private PageServer()
	{
		pageList_ = parse("war/site_src/xml/listing.xml");
	}
	
	private HashMap<String, File> parse(String path)
	{
		File listXML_ = new File(path);

		if (listXML_.exists()) 
		{
			LogWriter.getInstance().log("SUCCESS: listing.xml found");
		} 
		else 
		{
			LogWriter.getInstance().log("ERROR: listing.xml does not exist");
			System.exit(0);
		}

		try 
		{
			SAXBuilder builder_ = new SAXBuilder();
			Document doc = (Document) builder_.build(listXML_);
			Element root = doc.getRootElement();
			List<Element> list = root.getChildren("page");
			HashMap<String, File> tempList = new HashMap<String, File>();
			
			for (Element node : list) 
			{
				String pageName = node.getAttributeValue("id");
				String pagePath = node.getChildText("path");
				File f = new File(pagePath);
				tempList.put(pageName, f);
			}

			LogWriter.getInstance().log("SUCCESS: Successfully parsed listing.xml");
			return tempList;
		} 
		catch (Exception e) 
		{
			LogWriter.getInstance().log("ERROR: failed to parse listing.xml\r\n" + e.getMessage());
			return null;
		}
	}
	
	public FileInputStream getPage(String page)
	{
		try 
		{
			return new FileInputStream(getRawFile(page));
		} 
		catch (Exception e) 
		{
			LogWriter.getInstance().log("ERROR: failed to find requested html file\r\n" + e.getMessage());
			return null;
		}
	}
	
	public File getRawFile(String page)
	{
		if (page.equals("init"))
		{
			return null;
		}
		return pageList_.get(page);
	}
}
