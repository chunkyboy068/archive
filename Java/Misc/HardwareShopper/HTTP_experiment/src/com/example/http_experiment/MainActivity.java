package com.example.http_experiment;

import java.util.ArrayList;

import parsingtask.ParsingTask;
import networktask.NetworkTask;
import android.os.Bundle;
import android.app.Activity;
import android.util.Log;
import android.view.Menu;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

public class MainActivity extends Activity {

	Button searchButton_;
	Button conButton_;
	Button parseButton_;
	TextView msgDisplay_;
	TextView feedback_;
	TextView counterDisplay_;
	EditText userInput_;
	private static String tag = "HTTP_Experiment";
	ParsingTask nParser_;
	ParsingTask fParser_;
	NetworkTask newegg;
	NetworkTask frys;
	int clickCounter_;
	Helper helper_;
	
	public final static String NNAME_ = "NEWEGG ITEMS";
	public final static String FNAME_ = "FRYS ITEMS";
	public final static String NPRICE_ = "NEWEGG PRICES";
	public final static String FPRICE_ = "FRYS PRICES";
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		
		clickCounter_ = 0;
		searchButton_ = (Button) findViewById(R.id.button1);
		msgDisplay_ = (TextView) findViewById(R.id.textView1);
		feedback_ = (TextView) findViewById(R.id.textView2);
		userInput_ = (EditText) findViewById(R.id.editText1);
		conButton_ = (Button) findViewById(R.id.Button01);
		counterDisplay_ = (TextView) findViewById(R.id.textView3);
		parseButton_ = (Button) findViewById(R.id.button2);
		
		parseButton_.setEnabled(false);
		
		helper_ = new Helper(msgDisplay_, feedback_, counterDisplay_, searchButton_, parseButton_);
		helper_.setContext(this);
		
		searchButton_.setOnClickListener(
				new OnClickListener()
				{
					@Override
					public void onClick(View arg0) 
					{
						Log.d(tag, "Search Button Pressed");
						if (checkTextExist())
						{
							searchButton_.setEnabled(false);
							executeQuery();
						}
					}
				}
		);
		
		conButton_.setOnClickListener(
				new OnClickListener()
				{
					@Override
					public void onClick(View arg0) 
					{
						clickCounter_++;
						helper_.setCount(clickCounter_);
					}
				}
		);
		
		parseButton_.setOnClickListener(
				new OnClickListener()
				{
					@Override
					public void onClick(View arg0) 
					{
						parseButton_.setEnabled(false);
						helper_.giveFeedback("Processing");
						searchButton_.setEnabled(false);
						parseData();
					}
				}
		);
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}
	
	private boolean checkTextExist()
	{
		if (userInput_.getText().length() == 0)
		{
			helper_.giveFeedback("Please enter valid text and press search again.");
			return false;
		}
		feedback_.setText("Connecting to server...\n");
		return true;
	}
	
	private void executeQuery()
	{
		String params = userInput_.getText().toString();
		newegg = new NetworkTask(helper_);
		frys = new NetworkTask(helper_);
		newegg.execute(params, "http://www.newegg.com/Product/ProductList.aspx?Submit=ENE", "newegg");
		frys.execute(params, "http://www.frys.com/search?search_type=regular", "frys");
	}
	
	private void parseData()
	{
		nParser_ = new ParsingTask("newegg", helper_);
		fParser_ = new ParsingTask("frys", helper_);
		
		nParser_.execute(helper_.getData("newegg"));
		fParser_.execute(helper_.getData("frys"));
	}

}
