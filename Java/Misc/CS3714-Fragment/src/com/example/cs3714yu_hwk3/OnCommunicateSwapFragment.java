package com.example.cs3714yu_hwk3;

import android.app.Fragment;
import android.graphics.Bitmap;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;

public class OnCommunicateSwapFragment extends Fragment{

	ImageView img_;
	
	@Override
	public void onCreate(Bundle savedInstanceState) 
	{
		super.onCreate(savedInstanceState);
	}

	@Override
	public View onCreateView(LayoutInflater inflater, ViewGroup container,Bundle savedInstanceState) 
	{
		View view = inflater.inflate(R.layout.img_frag,container, false);
		img_ = (ImageView) view.findViewById(R.id.imageView1);
		img_.setImageResource(R.drawable.ic_launcher);
		return view;
	}

	public void show(Bitmap result) 
	{
		img_.setImageBitmap(result);
	}

}
