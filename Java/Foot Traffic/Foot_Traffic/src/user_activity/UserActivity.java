package user_activity;

import user_request.UserRequest;
import networktask.SendTask;

import battery_info.mBatInfoReceiver;

import com.example.foot_traffic.Helper;
import com.example.foot_traffic.MainActivity;
import com.example.foot_traffic.R;

import Location_Data.LocationPackage;
import android.location.Criteria;
import android.location.Location;
import android.location.LocationListener;
import android.location.LocationManager;
import android.os.Bundle;
import android.app.Activity;
import android.content.Intent;
import android.content.IntentFilter;
import android.graphics.Color;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.view.Menu;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemSelectedListener;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.CompoundButton;
import android.widget.CompoundButton.OnCheckedChangeListener;
import android.widget.ImageView;
import android.widget.ProgressBar;
import android.widget.RadioButton;
import android.widget.Spinner;
import android.widget.TextView;
import android.widget.ToggleButton;

public class UserActivity extends Activity{

	public final static String EXTRA_MESSAGE2 = "2";
	
	Helper helper_;
	String destination_;
	
	SensorManager sManager_;
	LocationManager lManager_;
	
	SensorEventListener sListener_;
	LocationListener lListener_;
	
	Sensor tempSens_;
	
	Button sendButton_;
	Button statButton_;
	ProgressBar progress_;
	Spinner spinner_;
	TextView sensorInfo_;
	ToggleButton gpsToggle_;
	ToggleButton sensToggle_;
	ImageView image_;
	
	boolean tempExists_;
	mBatInfoReceiver myBatInfoReceiver;
	
	String status_;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) 
	{
		status_ = "stay";
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_user);
		
		sensorInfo_ = (TextView) findViewById(R.id.textView3);
		progress_ = (ProgressBar) findViewById(R.id.progressBar1);
		spinner_ = (Spinner) findViewById(R.id.spinner1);
		sendButton_ = (Button) findViewById(R.id.button1);
		gpsToggle_ = (ToggleButton) findViewById(R.id.toggleButton1);
		sensToggle_ = (ToggleButton) findViewById(R.id.ToggleButton01);
		statButton_ = (Button) findViewById(R.id.button2);
		image_ = (ImageView) findViewById(R.id.imageView1);
		
		helper_ = new Helper();
		helper_.setProgress(progress_);
		helper_.setSend(sendButton_);
		helper_.enableSend(false);
		
		getDest();
		setUpLocListener();
		setUpSenListener();
		toggleGPS(true);
		toggleSensor(true);

		ArrayAdapter<CharSequence> adapter = ArrayAdapter.createFromResource(this, R.array.drop_down, 
				android.R.layout.simple_spinner_item );
		adapter.setDropDownViewResource( android.R.layout.simple_spinner_dropdown_item );
		spinner_.setAdapter(adapter);		
		
		setUpClickListeners();
		
		sManager_ = (SensorManager) getSystemService(SENSOR_SERVICE);
		lManager_ = (LocationManager) getSystemService(LOCATION_SERVICE);
		
		tempExists_ = checkTempExist();
		initSensors();
		
	}
	
	@Override
	protected void onPause() 
	{
		super.onPause();
		toggleGPS(false);
		changeGPSState(false);
		toggleSensor(false);
//		changeSensorState(false);
	}

	@Override
	protected void onResume() 
	{
		super.onResume();
		toggleGPS(true);
		changeGPSState(true);
		toggleSensor(true);
	//	changeSensorState(true);
	}
	
	private void initSensors()
	{
		if (tempExists_)
		{
			sManager_.registerListener(sListener_, sManager_.getDefaultSensor(Sensor.TYPE_AMBIENT_TEMPERATURE), 
									SensorManager.SENSOR_DELAY_UI);
		}
		else
		{
			myBatInfoReceiver = new mBatInfoReceiver(); 
			this.registerReceiver(this.myBatInfoReceiver, new IntentFilter(Intent.ACTION_BATTERY_CHANGED));
		}
		
		sManager_.registerListener(sListener_, sManager_.getDefaultSensor(Sensor.TYPE_LIGHT), 
									SensorManager.SENSOR_DELAY_UI);
		lManager_.requestLocationUpdates(LocationManager.GPS_PROVIDER, 10, Criteria.ACCURACY_FINE, lListener_);
	}

	private void setUpClickListeners() 
	{
		statButton_.setOnClickListener(
				new OnClickListener()
				{
					@Override
					public void onClick(View arg0) 
					{
						startRequestActivity();
					}
				}
		);
		
		sendButton_.setOnClickListener(
				new OnClickListener()
				{
					@Override
					public void onClick(View arg0) 
					{
						sendToServer();
						helper_.resetData();
					}
				}
		);
		
		spinner_.setOnItemSelectedListener(
				new OnItemSelectedListener()
				{

					@Override
					public void onItemSelected(AdapterView<?> adapter, View view, int pos, long id) 
					{
						changeDisplayed(pos);
					}

					@Override
					public void onNothingSelected(AdapterView<?> arg0) {
					}
				}
		);
		
		gpsToggle_.setOnCheckedChangeListener(
				new OnCheckedChangeListener()
				{
					@Override
					public void onCheckedChanged(CompoundButton button, boolean state) 
					{
						toggleGPS(state);
						changeGPSState(state);
					}	
				}
				
		);
		
		sensToggle_.setOnCheckedChangeListener(
				new OnCheckedChangeListener()
				{
					@Override
					public void onCheckedChanged(CompoundButton button, boolean state) 
					{
						toggleSensor(state);
						changeSensorState(state);
					}
				}
				
		);
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		getMenuInflater().inflate(R.menu.user, menu);
		return true;
	}
	
	public boolean checkTempExist()
	{
		Sensor temp = sManager_.getDefaultSensor(Sensor.TYPE_AMBIENT_TEMPERATURE);
		
		if (temp == null)
		{
			return false;
		}
		return true;
	}
	
	public void getDest()
	{
		Intent intent = getIntent();
		destination_ = intent.getStringExtra(MainActivity.EXTRA_MESSAGE);
		helper_.setDest(destination_);
	}
	
	private void sendToServer()
	{
		SendTask nTask = new SendTask(helper_, destination_, status_);
		nTask.execute();
	}
	
	private void setUpLocListener()
	{
		lListener_ = new LocationListener()
		{
			public void onLocationChanged(Location location) 
			{
				LocationPackage locData_ = new LocationPackage();

				locData_.setLocation(location.getAltitude(), location.getLongitude(), location.getLatitude());
				locData_.setTime(location.getTime());
				locData_.setMovement(location.getSpeed(), location.getBearing(), location.getAccuracy());

				helper_.setLocation(locData_);
				changeDisplayed(spinner_.getSelectedItemPosition());
			}

			@Override
			public void onProviderDisabled(String provider) 
			{
			}

			@Override
			public void onProviderEnabled(String provider) 
			{
			}

			@Override
			public void onStatusChanged(String provider, int status, Bundle extras) {
			}
		};
	}
	
	private void setUpSenListener()
	{
		sListener_ = new SensorEventListener()
		{

			@Override
			public void onAccuracyChanged(Sensor event, int arg1) {
			}

			@Override
			public void onSensorChanged(SensorEvent event) 
			{
				Sensor sensor = event.sensor;
				
				if (sensor.getType() == Sensor.TYPE_LIGHT)
				{
					helper_.setLightData(event.values[0]);
					
					if (!tempExists_)
					{
						helper_.setTempData(myBatInfoReceiver.get_temp());
					}
				}
				else if (sensor.getType() == Sensor.TYPE_AMBIENT_TEMPERATURE)
				{
					helper_.setTempData(event.values[0]);
				}
				
				changeDisplayed(spinner_.getSelectedItemPosition());
			}
			
		};
	}
	
	private void changeDisplayed(int pos)
	{
		String display = "\n";
		
		LocationPackage locate = helper_.getCurLocation();
		if ( pos == 0 && locate == null)
		{
			sensorInfo_.setText("\nNo Location Data");
			return;
		}
		else if (pos == 1 && locate == null)
		{
			sensorInfo_.setText("\nNo Time Data");
			return;
		}
		
		if (pos == 0)
		{
				display += "Latitude:\n" + locate.getLat() + "\n\n";
				display += "Longitude:\n" + locate.getLon() + "\n\n";
		}
		else if (pos == 1)
		{
			display += "Time Given by GPS:\n";
			display += locate.getTime();
		}
		else if (pos == 2)
		{
			display += "Brightness in Lumens:\n" + helper_.getLight();
		}
		else if (pos == 3)
		{
			display += "Celsius:\n" + helper_.getTemp() + "\n\n";
			display += "Fahrenheit:\n" + ((helper_.getTemp() * 1.8) + 32) + "\n\n";
			display += "Kelvin: \n" + (helper_.getTemp() + 273.15);
		}
		
		sensorInfo_.setText(display);
	}
	
	private void toggleGPS(boolean b)
	{
		gpsToggle_.setChecked(b);
		
		if (b)
		{
			gpsToggle_.setBackgroundColor(Color.parseColor("#48DE37"));
		}
		else
		{
			gpsToggle_.setBackgroundColor(Color.parseColor("#8D8F94"));
		}
	}
	
	private void toggleSensor(boolean b)
	{
		sensToggle_.setChecked(b);
		
		if (b)
		{
			sensToggle_.setBackgroundColor(Color.parseColor("#48DE37"));
		}
		else
		{
			sensToggle_.setBackgroundColor(Color.parseColor("#8D8F94"));
		}
	}
	
	private void changeGPSState(boolean b)
	{
		if (b)
		{
			lManager_.requestLocationUpdates(LocationManager.GPS_PROVIDER, 10, Criteria.ACCURACY_FINE, lListener_);
		}
		else
		{
			lManager_.removeUpdates(lListener_);
		}
	}
	
	private void changeSensorState(boolean b)
	{
		if (b)
		{
			sManager_.registerListener(sListener_, sManager_.getDefaultSensor(Sensor.TYPE_LIGHT), 
					SensorManager.SENSOR_DELAY_UI);
			
			if (tempExists_)
			{
				sManager_.registerListener(sListener_, sManager_.getDefaultSensor(Sensor.TYPE_AMBIENT_TEMPERATURE), 
						SensorManager.SENSOR_DELAY_UI);
			}
			else
			{
				this.registerReceiver(this.myBatInfoReceiver, new IntentFilter(Intent.ACTION_BATTERY_CHANGED));
			}
		}
		else
		{
			sManager_.unregisterListener(sListener_);
			this.unregisterReceiver(myBatInfoReceiver);
		}
	}
	
	private void startRequestActivity()
	{
		Intent intent = new Intent(this, UserRequest.class);
		intent.putExtra(EXTRA_MESSAGE2, destination_);
		startActivity(intent);
	}
	
	public void onRadioButtonClicked(View view)
	{
		boolean checked = ((RadioButton) view).isChecked(); 
		
	    switch(view.getId()) {
	        case R.id.radio0:
	            	if (checked)
	            	{
	            		image_.setImageResource(R.drawable.heretostay);
	            		status_ = "stay";
	            	}
	            	break;
	        case R.id.radio1:
	            	if (checked)
	            	{
	            		image_.setImageResource(R.drawable.hitroad);
	            		status_ = "leave";
	            	}
	            	break;
	        case R.id.radio2:
	        		if (checked)
	        		{
	        			image_.setImageResource(R.drawable.passingthrough);
	        			status_ = "pass";
	        		}
	        		break;
	    }
	}
}
