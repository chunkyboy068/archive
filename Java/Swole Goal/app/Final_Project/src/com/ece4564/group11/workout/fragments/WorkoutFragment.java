package com.ece4564.group11.workout.fragments;

/**
 * WorkoutFragment is a fragment that counts down the workout time. It also lets the user to start the lift song and break song.
 */

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Set;

import android.content.Intent;
import android.graphics.Color;
import android.media.MediaPlayer;
import android.media.MediaPlayer.OnPreparedListener;
import android.os.Bundle;
import android.os.Handler;
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

import com.ece4564.group11.workout.media.FileExplore;
import com.ece4564.group11.workout.media.MusicPlayer;
import com.example.final_project.R;

public class WorkoutFragment extends Fragment {

	Handler handler_;
	Runnable incrementer_;

	TextView path1_;
	TextView path2_;
	TextView counter_;
	TextView currentEx_;
	TextView setCounter_;
	Button play_;
	Button stop_;
	Button switch_;
	ImageButton browse_;
	ImageButton browse2_;
	MusicPlayer player_;
	boolean ready1;
	boolean ready2;

	List<Integer> routine_;
	List<String> routineName_;

	int currentRest_;
	int currentLift_;
	int currentSet_;
	String currentName_;

	static List<String> allExercises_;
	static HashMap<String, List<String>> workout_;

	public WorkoutFragment() {
		player_ = new MusicPlayer();
		ready1 = false;
		ready2 = false;
		workout_ = null;
		currentRest_ = 0;
		currentLift_ = 0;
		currentSet_ = 0;
		routine_ = null;
		currentName_ = null;
	}

	public static void setWorkout(HashMap<String, List<String>> plan) {
		workout_ = plan;
		Set<String> set = workout_.keySet();
		allExercises_ = new ArrayList<String>(set);
	}

	@Override
	public View onCreateView(LayoutInflater inflater, ViewGroup container,
			Bundle savedInstanceState) {

		View rootView = inflater.inflate(R.layout.fragment_workout, container,
				false);

		path1_ = (TextView) rootView.findViewById(R.id.path1);
		// path2_ = (TextView) rootView.findViewById(R.id.path2);
		play_ = (Button) rootView.findViewById(R.id.playbutton);
		play_.setEnabled(false);
		stop_ = (Button) rootView.findViewById(R.id.stopbutton);
		stop_.setEnabled(false);
		switch_ = (Button) rootView.findViewById(R.id.Switch);
		browse_ = (ImageButton) rootView.findViewById(R.id.browse1);
		browse2_ = (ImageButton) rootView.findViewById(R.id.browse2);
		switch_.setEnabled(false);
		counter_ = (TextView) rootView.findViewById(R.id.textCountdown);
		currentEx_ = (TextView) rootView.findViewById(R.id.currentEx);
		setCounter_ = (TextView) rootView.findViewById(R.id.setCounter);

		setNext();
		setUpListen();

		return rootView;
	}

	@Override
	public void setMenuVisibility(final boolean menuVisible) {
		// super.setMenuVisibility(menuVisible);
		if (menuVisible && (currentEx_ != null)) {
			setNext();
		}
	}

	@Override
	public void onPause() {
		player_.pause();
		super.onPause();
	}

	@Override
	public void onDestroy() {

		player_.release();
		super.onDestroy();
	}

	private void setUpListen() {
		/*
		 * OnClickListeners
		 */
		play_.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View arg0) {
				play_.setEnabled(false);
				stop_.setEnabled(true);
				switch_.setEnabled(true);
				player_.start(0);
				if (workout_ != null && routine_.size() > 0
						&& routineName_.size() > 0) {
					startWorkout();
				} else {
					setWorkout(workout_);
					setNext();
					startWorkout();
				}
			}
		});

		stop_.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View arg0) {
				stopButtonClicked();
				handler_.removeCallbacks(incrementer_);
			}
		});

		switch_.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View arg0) {
				switchMP();
			}
		});

		browse_.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View arg0) {
				startbrowse();
			}
		});

		browse2_.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View arg0) {
				startbrowse2();
			}
		});

		OnPreparedListener opl = new OnPreparedListener() {
			public void onPrepared(MediaPlayer mp) {
				ready1 = true;
				if (ready1 && ready2) {
					ready1 = false;
					ready2 = false;
					play_.setEnabled(true);
				}
			}
		};

		OnPreparedListener opl2 = new OnPreparedListener() {
			public void onPrepared(MediaPlayer mp) {
				ready2 = true;
				if (ready1 && ready2) {
					ready1 = false;
					ready2 = false;
					play_.setEnabled(true);
				}
			}
		};

		player_.setOnPreparedListener(opl, opl2);
		
		
		/*
		 * ontouchListeners
		 */
		
		browse_.setOnTouchListener(new OnTouchListener() {
		    @Override
		    public boolean onTouch(View arg0, MotionEvent me) {
		        if (me.getAction() == MotionEvent.ACTION_DOWN) {
		        	browse_.setColorFilter(Color.argb(50, 0, 0, 0));
		        } else if (me.getAction() == MotionEvent.ACTION_UP) {
		        	browse_.setColorFilter(Color.argb(0, 155, 155, 155)); 
		        }
		        return false;
		    }
		});
		
		browse2_.setOnTouchListener(new OnTouchListener() {
		    @Override
		    public boolean onTouch(View arg0, MotionEvent me) {
		        if (me.getAction() == MotionEvent.ACTION_DOWN) {
		        	browse2_.setColorFilter(Color.argb(50, 0, 0, 0));
		        } else if (me.getAction() == MotionEvent.ACTION_UP) {
		        	browse2_.setColorFilter(Color.argb(0, 155, 155, 155));
		        }
		        return false;
		    }
		});
	}

	private void switchMP() {
		player_.switchSongs();
	}

	@Override
	public void onActivityResult(int requestCode, int resultCode, Intent data) {
		super.onActivityResult(requestCode, resultCode, data);
		this.getActivity().finishActivity(1);
		this.getActivity().finishActivity(2);
		String result = data.getStringExtra("path");

		path1_.setText(result);
		// path2_.setText(result);

		if (requestCode == 1 && result.length() > 0) {
			player_.setFirstPath(result);
		} else if (requestCode == 2 && result.length() > 0) {
			player_.setSecondPath(result);
		}
	}

	private void startbrowse() {
		Intent intent = new Intent(getActivity(), FileExplore.class);
		this.startActivityForResult(intent, 1);
	}

	private void startbrowse2() {
		Intent intent = new Intent(getActivity(), FileExplore.class);
		this.startActivityForResult(intent, 2);
	}

	private void setNext() {
		if (workout_ != null && !workout_.isEmpty()
				&& allExercises_.size() != 0) {

			currentName_ = allExercises_.remove(0);
			currentEx_.setText(currentName_);

			List<String> params = workout_.get(currentName_);
			currentLift_ = Integer.parseInt(params.get(0));
			currentRest_ = Integer.parseInt(params.get(1));
			currentSet_ = Integer.parseInt(params.get(2));

			setCounter_.setText(currentSet_ + " Sets Left");
			counter_.setText(params.get(0));
			setRoutine();

		} else {
			currentEx_.setText("No Exercises Selected");
			setCounter_.setText(currentSet_ + " Sets Left");
		}
	}

	private void startWorkout() {
		handler_ = new Handler();

		incrementer_ = new Runnable() {
			@Override
			public void run() {

				{
					int num = routine_.get(0);
					num--;
					routine_.set(0, num);
					if (num == 0) {
						routine_.remove(0);
						routineName_.remove(0);

						if (allExercises_.isEmpty() && routineName_.isEmpty()
								&& routine_.isEmpty()) {
							currentSet_ = 0;
							currentLift_ = 0;
							currentRest_ = 0;
							stopButtonClicked();
							handler_.removeCallbacks(this);
							setNext();
							return;
						}

						if (routineName_.size() == 0) {
							setNext();
						}
						currentEx_.setText(routineName_.get(0));
						if (routineName_.get(0).equals("Rest")) {
							currentSet_--;
							setCounter_.setText(Integer.toString(currentSet_)
									+ " Sets Left");
						}
						player_.switchSongs();
					}
					counter_.setText(Integer.toString(routine_.get(0)));
					handler_.postDelayed(this, 1000);
				}
			}
		};

		incrementer_.run();
	}

	private void setRoutine() {
		routine_ = new ArrayList<Integer>();
		routineName_ = new ArrayList<String>();
		for (int i = 0; i < currentSet_; i++) {
			routineName_.add(currentName_);
			routine_.add(currentLift_);
			routineName_.add("Rest");
			routine_.add(currentRest_);
		}
	}

	private void stopButtonClicked() {
		play_.setEnabled(true);
		stop_.setEnabled(false);
		switch_.setEnabled(false);
		player_.pause();
	}
}