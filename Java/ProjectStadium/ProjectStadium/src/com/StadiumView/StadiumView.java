package com.StadiumView;

import java.util.ArrayList;
import java.util.List;

import com.Login.Friend;
import com.StadiumActivity.StadiumDetailFragment;
import com.example.projectstadium.R;

import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemSelectedListener;
import android.widget.ArrayAdapter;
import android.widget.ImageView;
import android.widget.RelativeLayout;
import android.widget.RelativeLayout.LayoutParams;
import android.widget.Spinner;

public class StadiumView extends Activity implements OnItemSelectedListener {

	private Spinner friends_;
	private List<String> friendArray;
	private RelativeLayout rl;
	private ArrayList<ImageView> imageList;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_stadiumview);

		friendArray = new ArrayList<String>();
		friendArray.add("All friends");

		rl = (RelativeLayout) this.findViewById(R.id.relative_Layout);

		imageList = new ArrayList<ImageView>();
		if (StadiumDetailFragment.myArea != -1) {
			addImageFromAreaID(StadiumDetailFragment.myArea, true);
		}
		for (Friend f : StadiumDetailFragment.friends) {
			friendArray.add(f.getName());

			addImageFromAreaID(f.getArea(), false);
		}

		friends_ = (Spinner) this.findViewById(R.id.friendSpinner);
		ArrayAdapter<String> dataAdapter = new ArrayAdapter<String>(this,
				android.R.layout.simple_spinner_item, friendArray);
		dataAdapter
				.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
		friends_.setAdapter(dataAdapter);
		friends_.setOnItemSelectedListener(this);

	}

	private void addImageFromAreaID(int areaID, boolean isGreen) {
		ImageView iv = new ImageView(this);
		String color = "sectionred_";

		if (isGreen) {
			color = "sectiongreen_";
		}
		int id = getResources().getIdentifier(color + areaID, "drawable",
				this.getPackageName());
		iv.setImageResource(id);

		LayoutParams params = new LayoutParams(LayoutParams.MATCH_PARENT,
				LayoutParams.WRAP_CONTENT);
		iv.setLayoutParams(params);
		iv.setVisibility(View.VISIBLE);

		rl.addView(iv);

		imageList.add(iv);

	}

	private void showAllFriends() {
		for (ImageView iv : imageList) {
			iv.setVisibility(View.VISIBLE);
		}
	}

	private void hideAllFriends() {
		for (ImageView iv : imageList) {
			iv.setVisibility(View.INVISIBLE);
		}
	}

	@Override
	public void onItemSelected(AdapterView<?> adapter, View view, int pos,
			long id) {
		if (pos == 0) {
			showAllFriends();
		} else {
			hideAllFriends();
			imageList.get(pos).setVisibility(View.VISIBLE);
			// pos - 1 since "Show all friends" option takes up the first
			// element
		}

	}

	@Override
	public void onNothingSelected(AdapterView<?> arg0) {
		// TODO Auto-generated method stub

	}

}
