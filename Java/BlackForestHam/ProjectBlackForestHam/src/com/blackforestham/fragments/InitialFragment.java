package com.blackforestham.fragments;

import com.blackforestham.HamsterActivity;
import com.blackforestham.R;
import com.blackforestham.interfaces.GetNameInterface;

import android.content.Context;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.view.View.OnClickListener;
import android.widget.Button;

public class InitialFragment extends Fragment implements GetNameInterface{

	String abName = "Set Your Goals";
	Button start;
	SharedPreferences sp;
	
	public InitialFragment()
	{
		
	}
	
	@Override
	public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) 
	{
		View rootView = inflater.inflate(com.blackforestham.R.layout.activity_goal, container, false);
		
		start = (Button) rootView.findViewById(R.id.startButton);
		
		start.setOnClickListener(new OnClickListener() {
		    @Override
		    public void onClick(View v) 
		    {
		    	startApp();
		    }
		});
		
		sp = this.getActivity().getPreferences(Context.MODE_PRIVATE);
		
		return rootView;
	}

	private void startApp()
	{
		/**
		 * TODO: a check for user input
		 * store these onto shared preferences for persistence
		 */
		sp.edit().putBoolean(HamsterActivity.isFirstKey, false).commit();
	}
	
	@Override
	public String getName() 
	{
		return abName;
	}

}
