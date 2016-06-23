package user_request;

import networktask.GetTask;
import user_activity.UserActivity;

import com.example.foot_traffic.MainActivity;
import com.example.foot_traffic.R;
import com.example.foot_traffic.R.layout;
import com.example.foot_traffic.R.menu;

import android.os.Bundle;
import android.app.Activity;
import android.content.Intent;
import android.view.Menu;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.TimePicker;

public class UserRequest extends Activity {

	Button getButton_;
	EditText queryBox_;
	TextView display_;
	TextView results_;
	TimePicker tpicker_;
	String destination_;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) 
	{
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_user_request);
		
		getButton_ = (Button) findViewById(R.id.button3);
		queryBox_ = (EditText) findViewById(R.id.qText02);
		tpicker_ = (TimePicker) findViewById(R.id.timePicker1);
		display_ = (TextView) findViewById(R.id.dispView2);
		results_ = (TextView) findViewById(R.id.resultsView2);
		
		Intent intent = getIntent();
		destination_ = intent.getStringExtra(UserActivity.EXTRA_MESSAGE2);
		
		getButton_.setOnClickListener(
				new OnClickListener()
				{
					@Override
					public void onClick(View arg0) 
					{
						startRequest();
					}
				}
		);
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu)
	{
		getMenuInflater().inflate(R.menu.user_request, menu);
		return true;
	}
	
	private void startRequest()
	{
		String query = queryBox_.getText().toString();
		if (query.trim().equals(""))
		{
			display_.setText("What are you looking for?  [LAT, LON] or Letters Only");
			return;
		}
		
		String[] stringList = query.split(",");
		
		int hour = tpicker_.getCurrentHour();	
		if (stringList.length == 1)
		{
			sendRequest(stringList[0], hour);
		}
		else if (stringList.length == 2)
		{
			float lat;
			float lon;
			try
			{
				lat = Float.parseFloat(stringList[0]);
				lon = Float.parseFloat(stringList[1]);
			}
			catch (NumberFormatException nfe)
			{
				display_.setText("Wrong Format.  [LAT, LON] or Letters Only");
				return;
			}
			sendRequest(lat, lon, hour);
		}
		else
		{
			display_.setText("Wrong Format.  [LAT, LON] or Letters Only");
		}
	}

	private void sendRequest(String descrip, int hour)
	{
		GetTask get = new GetTask(destination_, hour, results_);
		get.execute(descrip);
	}
	
	private void sendRequest(Float lat, Float lon, int hour)
	{
		GetTask get = new GetTask(destination_, hour, results_);
		get.execute(String.valueOf(lat), String.valueOf(lon));
	}
}
