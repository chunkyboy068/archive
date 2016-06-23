package com.example.http_experiment;

import java.util.ArrayList;

import android.os.Bundle;
import android.app.Activity;
import android.content.Intent;
import android.graphics.Color;
import android.util.Log;
import android.view.Menu;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.TableLayout;
import android.widget.TableRow;
import android.widget.TextView;

public class DisplayActivity extends Activity {

	Intent intent_;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_display);
		
		intent_ = getIntent();
		ArrayList<String> neweggItems = intent_.getStringArrayListExtra(MainActivity.NNAME_);
		ArrayList<String> frysItems = intent_.getStringArrayListExtra(MainActivity.FNAME_);
		ArrayList<String> neweggPrices = intent_.getStringArrayListExtra(MainActivity.NPRICE_);
		ArrayList<String> frysPrices = intent_.getStringArrayListExtra(MainActivity.FPRICE_);
		
		TableLayout layout = (TableLayout) findViewById(R.id.tableLayout1);
		layout.setColumnShrinkable(0, true);
		layout.setColumnShrinkable(1, true);
		layout.setColumnStretchable(0, true);
		layout.setColumnShrinkable(1, true);
		
		TableLayout layout2 = (TableLayout) findViewById(R.id.tableLayout2);
		layout2.setColumnShrinkable(0, true);
		layout2.setColumnShrinkable(1, true);
		layout2.setColumnStretchable(0, true);
		layout2.setColumnShrinkable(1, true);
		
		TableRow newRow;
		TextView nameText;
		TextView priceText;
		
		while(!neweggItems.isEmpty())
		{
			nameText = new TextView(this);
			nameText.setText(neweggItems.remove(0));
			priceText = new TextView(this);
			priceText.setText(neweggPrices.remove(0));
			
			nameText.setTextColor(Color.parseColor("#FFFFFF"));
			priceText.setTextColor(Color.parseColor("#FFFFFF"));
			
			newRow = new TableRow(this);
			newRow.addView(nameText);
			newRow.addView(priceText);
			
			layout.addView(newRow);
		}
		
		while(!frysItems.isEmpty())
		{
			nameText = new TextView(this);
			nameText.setText(frysItems.remove(0));
			priceText = new TextView(this);
			priceText.setText(frysPrices.remove(0));
			
			nameText.setTextColor(Color.parseColor("#FFFFFF"));
			priceText.setTextColor(Color.parseColor("#FFFFFF"));
			
			newRow = new TableRow(this);
			newRow.addView(nameText);
			newRow.addView(priceText);
			
			layout2.addView(newRow);
		}
	}

	@Override
	public void onBackPressed() {
		super.onBackPressed();
		this.finish();
	}

	
}
