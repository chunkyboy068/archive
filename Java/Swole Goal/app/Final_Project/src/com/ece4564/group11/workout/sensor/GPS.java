package com.ece4564.group11.workout.sensor;

/**
 * GPS Fragment which allows the user to send their coordinates to the webserver, as well
 * as retrieve ant surrounding users.
 */

import java.util.Timer;
import java.util.TimerTask;
import java.util.UUID;

import com.ece4564.group11.workout.network.LocationNetworkTask;
import com.example.final_project.R;

import android.location.Criteria;
import android.location.Location;
import android.location.LocationListener;
import android.location.LocationManager;
import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

public class GPS extends Fragment implements LocationListener {

	LocationManager lManager_;
	LocationPackage locData_;
	TextView coordinates_;
	TextView friends_;
	TextView status_;
	Button add_;
	Button remove_;
	LocationNetworkTask nt_;
	UUID uuid_;
	EditText name_;
	Timer timer_;

	public View onCreateView(LayoutInflater inflater, ViewGroup container,
			Bundle savedInstanceState) {
		View rootView = inflater.inflate(R.layout.fragment_gps, container,
				false);
		coordinates_ = (TextView) rootView.findViewById(R.id.coordlist);
		friends_ = (TextView) rootView.findViewById(R.id.friendlist);
		add_ = (Button) rootView.findViewById(R.id.addserv);
		remove_ = (Button) rootView.findViewById(R.id.removeserv);
		uuid_ = new DeviceUuidFactory(rootView.getContext()).getDeviceUuid();
		name_ = (EditText) rootView.findViewById(R.id.editName);
		status_ = (TextView) rootView.findViewById(R.id.statusView);

		lManager_ = (LocationManager) this.getActivity().getSystemService(
				this.getActivity().LOCATION_SERVICE);

		init();
		setUpListeners();

		timer_ = new Timer();
		timer_.schedule(new TimerTask() {
			  @Override
			  public void run() 
			  {
				  if (locData_ == null)
				  {
					  getNetworkLocation();
				  }
			  }
			}, 10000);
		
		return rootView;
	}

	private void getNetworkLocation()
	{
		lManager_.requestLocationUpdates(LocationManager.NETWORK_PROVIDER, 10,
				Criteria.ACCURACY_FINE, this);
	}
	
	private void init() {
		add_.setEnabled(false);
		displayLocation(null);

		if (lManager_.getProvider(LocationManager.GPS_PROVIDER) == null) {
			status_.setText("NO GPS device found. GPS Functionality is required.");
		} else {
			lManager_.requestLocationUpdates(LocationManager.GPS_PROVIDER, 10,
					Criteria.ACCURACY_FINE, this);
		}
	}

	@Override
	public void onPause() 
	{
		super.onPause();
		lManager_.removeUpdates(this);
		timer_.cancel();
	}

	
	
	@Override
	public void onStop() 
	{
		super.onStop();
		lManager_.removeUpdates(this);
		timer_.cancel();
	}

	@Override
	public void onResume() {
		super.onResume();
		init();
	}

	private void setUpListeners() {
		add_.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View arg0) {
				sendServer("stay");
			}
		});

		remove_.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View arg0) {
				sendServer("leave");
			}
		});
	}

	private void displayLocation(LocationPackage loc) {
		if (loc == null) {
			coordinates_.setText("Latitude: Pending...\n");
			coordinates_.append("Longitude: Pending...\n");
			coordinates_.append("Altitude: Pending...\n");
		} else {
			coordinates_.setText("Latitude: " + Double.toString(loc.getLat())
					+ "\n");
			coordinates_.append("Longitude: " + Double.toString(loc.getLon())
					+ "\n");
			coordinates_.append("Altitude: "
					+ Double.toString(loc.getAltitude()) + "\n");
		}
	}

	@Override
	public void onLocationChanged(Location location) 
	{
		
		locData_ = new LocationPackage();
		locData_.setLocation(location.getAltitude(), location.getLongitude(),
				location.getLatitude());
		locData_.setTime(location.getTime());
		locData_.setMovement(location.getSpeed(), location.getBearing(),
				location.getAccuracy());
		displayLocation(locData_);
		add_.setEnabled(true);
	}

	@Override
	public void onProviderDisabled(String arg0) {
		lManager_.removeUpdates(this);
	}

	@Override
	public void onProviderEnabled(String arg0) {

	}

	@Override
	public void onStatusChanged(String arg0, int arg1, Bundle arg2) {
		lManager_.removeUpdates(this);
	}

	private void sendServer(String state) {
		if (name_.getText().length() == 0) {
			status_.setText("Enter a display name!");
			return;
		}

		add_.setEnabled(false);
		nt_ = new LocationNetworkTask(locData_, uuid_,
				"http://ec2-54-212-21-86.us-west-2.compute.amazonaws.com",
				name_.getText().toString());
		nt_.setTexts(status_, friends_);
		nt_.execute(state);
		status_.setText("Connecting to Server...");
	}
}
