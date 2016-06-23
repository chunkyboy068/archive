package com.example.http_experiment;

import java.util.ArrayList;

import android.content.Context;
import android.content.Intent;
import android.widget.Button;
import android.widget.TextView;

public class Helper {

	TextView messages_;
	TextView feedback_;
	TextView counter_;
	Button searchBtn_;
	String neweggData_;
	String fryData_;
	Button parseBtn_;
	
	ArrayList<String> nNames_;
	ArrayList<String> fNames_;
	ArrayList<String> nPrices_;
	ArrayList<String> fPrices_;
	
	boolean neweggDone;
	boolean fryDone;
	boolean neweggParse;
	boolean fryParse;
	
	Context mainContext_;
	
	public Helper(TextView msg, TextView fb, TextView cnt, Button sb, Button pb)
	{
		messages_ = msg;
		feedback_ = fb;
		counter_ = cnt;
		searchBtn_ = sb;
		neweggDone = false;
		fryDone = false;
		neweggParse = false;
		fryParse = false;
		parseBtn_ = pb;
		
	}
	
	public void setContext(Context con)
	{
		mainContext_ = con;
	}
	
	public void changeMsg(String text )
	{
		messages_.setText(text);
	}
	
	public void setCount(int cnt)
	{
		counter_.setText(Integer.toString(cnt));
	}
	
	public void giveFeedback(String text)
	{
		feedback_.append(text);
		feedback_.append("...");
		feedback_.append("\n");
	}
	
	public void resetSearch()
	{
		searchBtn_.setEnabled(true);
		neweggDone = false;
		fryDone = false;
	}
	
	public void setData(String data, String source)
	{
		if (source.equals("newegg"))
		{
			neweggData_ = data;
			neweggDone = true;
		}
		else if (source.equals("frys"))
		{
			fryData_ = data;
			fryDone = true;
		}
		
		if (fryDone && neweggDone)
		{
			resetSearch();
			parseBtn_.setEnabled(true);
		}
	}
	
	public String getData(String site)
	{
		if (site.equals("newegg"))
		{
			return neweggData_;
		}
		else if (site.equals("frys"))
		{
			return fryData_;
		}
		
		return null;
	}
	
	public void setParse(String site, ArrayList<String> names, ArrayList<String> prices)
	{
		if (site.equals("newegg"))
		{
			nNames_ = names;
			nPrices_ = prices;
			neweggParse = true;
			
		}
		else if (site.equals("frys"))
		{
			fNames_ = names;
			fPrices_ = prices;
			fryParse = true;
		}
		
		if (fryParse && neweggParse)
		{
			fryParse = false;
			neweggParse = false;
			giveFeedback("Done Processing...");
			giveFeedback("Displaying...");
			
			Intent intent = new Intent(mainContext_, DisplayActivity.class);
			intent.putStringArrayListExtra(MainActivity.NNAME_, nNames_);
			intent.putStringArrayListExtra(MainActivity.FNAME_, fNames_);
			intent.putStringArrayListExtra(MainActivity.NPRICE_, nPrices_);
			intent.putStringArrayListExtra(MainActivity.FPRICE_, fPrices_);
			
			mainContext_.startActivity(intent);
		}
	}
}
