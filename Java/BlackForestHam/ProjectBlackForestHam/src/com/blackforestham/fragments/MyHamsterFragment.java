package com.blackforestham.fragments;

import com.blackforestham.interfaces.GetNameInterface;

import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

public class MyHamsterFragment extends Fragment implements GetNameInterface{

	final String abName = "My Hamster";
	
	@Override
	public View onCreateView(LayoutInflater inflater, ViewGroup container,Bundle savedInstanceState) 
	{
		return super.onCreateView(inflater, container, savedInstanceState);
	}
	
	@Override
	public String getName()
	{
		return abName;
	}

}
