package com.ece4564.group11.workout.fragments;

/**
 * ExtrasFragment is the heart rate monitor fragment that displays the start button to start the monitor
 */

import com.ece4564.group11.workout.sensor.HeartRateMonitor;
import com.example.final_project.R;

import android.content.Intent;
import android.graphics.Color;
import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.MotionEvent;
import android.view.View;
import android.view.ViewGroup;
import android.view.View.OnClickListener;
import android.view.View.OnTouchListener;
import android.widget.Button;
import android.widget.ImageButton;
import android.widget.TextView;

public class ExtrasFragment extends Fragment {

	ImageButton heart_;
	TextView display_;

	public ExtrasFragment() {
	}

	@Override
	public View onCreateView(LayoutInflater inflater, ViewGroup container,
			Bundle savedInstanceState) {

		View rootView = inflater.inflate(R.layout.fragment_extras, container,
				false);
		heart_ = (ImageButton) rootView.findViewById(R.id.heartOn);
		display_ = (TextView) rootView.findViewById(R.id.extraText);

		setUpListeners();

		return rootView;
	}

	private void setUpListeners() {
		heart_.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View arg0) {
				startHRM();
			}
		});
		heart_.setOnTouchListener(new OnTouchListener() {
		    @Override
		    public boolean onTouch(View arg0, MotionEvent me) {
		        if (me.getAction() == MotionEvent.ACTION_DOWN) {
		        	heart_.setColorFilter(Color.argb(50, 0, 0, 0));
		        } else if (me.getAction() == MotionEvent.ACTION_UP) {
		        	heart_.setColorFilter(Color.argb(0, 155, 155, 155));
		        }
		        return false;
		    }
		});
	}

	public void startHRM() {
		Intent intent = new Intent(getActivity(), HeartRateMonitor.class);
		this.startActivity(intent);
	}
}
