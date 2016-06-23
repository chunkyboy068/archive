package com.example.foot_traffic;

import java.util.ArrayList;

import user_activity.UserActivity;

import android.os.Bundle;
import android.app.Activity;
import android.content.Intent;
import android.view.Menu;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

public class MainActivity extends Activity {

	Button startButton_;
	Button optionsButton_;
	EditText ipField_;
	EditText portField_;
	TextView display_;
	String fullpath_;
	
	public final static String EXTRA_MESSAGE = "1";

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		
		startButton_ = (Button) findViewById(R.id.button1);
		portField_ = (EditText) findViewById(R.id.EditText01);
		ipField_ = (EditText) findViewById(R.id.editText1);
		display_ = (TextView) findViewById(R.id.textView3);
		
		setupClickListeners();
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}
	
	private void setupClickListeners()
	{
		startButton_.setOnClickListener(
				new OnClickListener()
				{
					@Override
					public void onClick(View arg0) 
					{
						startApp();
					}
				}
		);
	}
	
	private void startApp()
	{
		if (checkPort())
		{
			fullpath_ = "http://" + ipField_.getText().toString().trim() + ":" + portField_.getText().toString().trim();
			startNextActivity();
		}
		else
		{
			display_.setText("Invalid Port");
		}
	}
	
	private boolean checkPort()
	{
		try
		{
			int a = Integer.parseInt(portField_.getText().toString());
		}
		catch (NumberFormatException n)
		{
			return false;
		}
		return true;
	}
	
	private void startNextActivity()
	{
		Intent intent = new Intent(this, UserActivity.class);
		intent.putExtra(EXTRA_MESSAGE, fullpath_);
		startActivity(intent);
	}
}
