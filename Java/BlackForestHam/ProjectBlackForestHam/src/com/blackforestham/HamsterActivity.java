package com.blackforestham;

import java.util.ArrayList;
import java.util.Locale;

import com.blackforestham.fragments.FriendFragment;
import com.blackforestham.fragments.InitialFragment;
import com.blackforestham.fragments.MyHamsterFragment;
import com.blackforestham.interfaces.GetNameInterface;

import android.content.Context;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentActivity;
import android.support.v4.app.FragmentManager;
import android.support.v4.app.FragmentPagerAdapter;
import android.support.v4.view.ViewPager;
import android.view.Menu;

public class HamsterActivity extends FragmentActivity {

	SectionsPagerAdapter mSectionsPagerAdapter;
	ViewPager mViewPager;
	SharedPreferences sp;
	final public static String isFirstKey = "ISFIRST";
	
	ArrayList<Fragment> friends;

	@Override
	protected void onCreate(Bundle savedInstanceState) 
	{
		super.onCreate(savedInstanceState);
		
		setContentView(R.layout.activity_hamster);
		sp = this.getPreferences(Context.MODE_PRIVATE);
		
		friends = new ArrayList<Fragment>();
		setupFriendsList();
		
		mSectionsPagerAdapter = new SectionsPagerAdapter(
				getSupportFragmentManager());

		mViewPager = (ViewPager) findViewById(R.id.pager);
		mViewPager.setAdapter(mSectionsPagerAdapter);
	}
	
	
	
	private void setupFriendsList() 
	{
		//executes if NOT first time
		if (!sp.getBoolean(isFirstKey, true))
		{
			//populate friendslist with server data
			//hardcode for now
			friends.add(new MyHamsterFragment());
			friends.add(new FriendFragment());
		}
		else
		{
			friends.add(new InitialFragment());
		}
	}
	
	@Override
	protected void onResume()
	{
		super.onResume();
	}
	
	@Override
	public boolean onCreateOptionsMenu(Menu menu) 
	{
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.hamster, menu);
		return true;
	}

	public class SectionsPagerAdapter extends FragmentPagerAdapter 
	{
		public SectionsPagerAdapter(FragmentManager fm) 
		{
			super(fm);
		}

		@Override
		public Fragment getItem(int position) 
		{
			return friends.get(position);
		}

		@Override
		public int getCount() 
		{
			return friends.size();
		}

		@Override
		public CharSequence getPageTitle(int position) 
		{
			Locale l = Locale.getDefault();
			return ((GetNameInterface) friends.get(position)).getName().toUpperCase(l);
		}
	}

}
