package parsingtask;

import java.util.ArrayList;

import org.jsoup.Jsoup;
import org.jsoup.nodes.Document;
import org.jsoup.nodes.Element;
import org.jsoup.select.Elements;
import com.example.http_experiment.Helper;
import android.os.AsyncTask;

public class ParsingTask extends AsyncTask<String, String, String>{

	String name_;
	Helper helper_;
	Document doc;
	
	ArrayList<String> itemNames_;
	ArrayList<String> priceList_;
	
	public ParsingTask()
	{
		name_ = null;
		helper_ = null;
	}
	
	public ParsingTask(String site, Helper h)
	{
		name_ = site;
		helper_ = h;
	}
	
	@Override
	protected String doInBackground(String... arg0) 
	{
		if (name_.equals("newegg"))
		{
			return parseNewegg(arg0[0]);
		}
		else if (name_.equals("frys"))
		{
			return parseFrys(arg0[0]);
		}
		return null;
	}
	
	private String parseNewegg(String html)
	{
		doc = Jsoup.parse(html);
		Elements elem = doc.body().select("div#container").select("div#bodyArea").select("div#bodyCenterArea");
		elem = elem.select("div#bodyGrid").select("div.productList").select("div.version600").select("div.itemcell");
		
		if(elem.size() == 0)
		{
			return null;
		}
		
		int i = 0;
		Elements curElemlist;
		String temp;
		itemNames_ = new ArrayList<String>();
		priceList_ = new ArrayList<String>();
		while (!elem.isEmpty() && i < 8)
		{
			curElemlist = elem.first().select("div.itemText").select("div.wrapper").select("a");
			curElemlist = curElemlist.select("span[style=display:inline].itemDescription");
			if (curElemlist.text().length() > 33)
			{
				itemNames_.add(curElemlist.text().substring(0, 30) + "...");
			}
			else
			{
				itemNames_.add(curElemlist.text());
			}
			
			curElemlist = elem.first().select("div.itemAction").select("ul").select("li.price-current");;
			System.out.println(curElemlist.select("li.price-current").toString());
			
			temp = curElemlist.select("strong").text() + curElemlist.select("sup").text();
			priceList_.add(temp);
			
			elem.remove(0);
			i++;
		}
		
		String allData = "";
		
		for (int j = 0; j < itemNames_.size(); j ++)
		{
			allData += " " + itemNames_.get(j) + "\t" + priceList_.get(j) + "\n";
		}
		
 		return allData;
	}
	
	private String parseFrys(String html)
	{
		doc = Jsoup.parse(html);
		Elements elem = doc.body().select("div#MainContainer").select("table[width=800]").select("tbody").select("tr");
		elem = elem.select("td[valign=top]").select("table[width=99%]");
		elem = elem.get(1).select("tbody").select("tr");
		
		int actualData = 0;
		Elements curElemList;
		Elements tempList;
		itemNames_ = new ArrayList<String>();
		priceList_ = new ArrayList<String>();
		Element curElem;
		
		while(actualData < 8)
		{
			curElemList = elem.first().select("td[align=left]");
			if (curElemList.size() != 0)
			{
				curElem = curElemList.get(0);
				if(curElem.select("a").text().length() > 33)
				{
					itemNames_.add(curElem.select("a").text().substring(0, 30) + "...");
				}
				else
				{
					itemNames_.add(curElem.select("a").text());
				}
				actualData ++;
			}
			
			curElemList = elem.first().select("td[width=24%]");
			if (curElemList.size() != 0)
			{
				
				curElemList = curElemList.select("div#did_priceblock");
				tempList = curElemList;		
				curElemList = curElemList.select("div#did_price1_combo");
				curElemList = curElemList.select("div#did_price1valuediv").select("label");
				
				if (curElemList.text().length() == 0)
				{
					curElemList = tempList;
					curElemList = curElemList.select("div#did_price2_combo");
					curElemList = curElemList.select("div#did_price2valuediv").select("label");
					priceList_.add(curElemList.text());
				}
				else
				{
					priceList_.add(curElemList.text());
				}
			}
			
			elem.remove(0);
		}
		
		String allData = "";
		for (int j = 0; j < itemNames_.size(); j ++)
		{
			allData += " " + itemNames_.get(j) + " \t" + priceList_.get(j) + "\n";
		}
		
		return allData;
	}

	@Override
	protected void onPostExecute(String result) 
	{
		if (result == null)
		{
			helper_.setParse(name_, null, null);
		}
		else
		{
			helper_.setParse(name_, itemNames_, priceList_ );
		}
		
		helper_.resetSearch();
		
	}
	
	

}
