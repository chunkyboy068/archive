package com.example.lab4;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.Date;

import android.app.Activity;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.SurfaceTexture;
import android.hardware.Camera;
import android.media.MediaScannerConnection;
import android.media.MediaScannerConnection.MediaScannerConnectionClient;
import android.net.Uri;
import android.os.Bundle;
import android.os.Environment;
import android.view.Menu;
import android.view.MenuItem;
import android.view.MenuItem.OnMenuItemClickListener;
import android.view.MotionEvent;
import android.view.TextureView;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.View.OnTouchListener;
import android.widget.ImageView;
import android.widget.RelativeLayout;
import android.widget.RelativeLayout.LayoutParams;
import android.widget.ScrollView;
import android.widget.Toast;

public class LiveCameraActivity extends Activity implements TextureView.SurfaceTextureListener, TextureView.OnTouchListener, Camera.PictureCallback
{
	private Camera mCamera;
	private TextureView mTextureView;
	private RelativeLayout rl_;
	private ScrollView sv_;
	ArrayList<ImageView> viewList_;
	ArrayList<Bitmap> bitmaps;
	private int ids;
	private View active;
	String mCurrentPhotoPath;
	MediaScannerConnection connection;
	
	protected void onCreate(Bundle savedInstanceState) 
	{
		super.onCreate(savedInstanceState);
		
		active = null;
		viewList_ = new ArrayList<ImageView>();
		bitmaps = new ArrayList<Bitmap>();
		ids = 1000;
		
		sv_ = new ScrollView(this);
		sv_.setFillViewport(true);
		
		rl_ = new RelativeLayout(this);
		rl_.setOnTouchListener(this);
		
		mTextureView = new TextureView(this);
		mTextureView.setSurfaceTextureListener(this);
		mTextureView.setId(999);
		
		sv_.addView(rl_);
		rl_.addView(mTextureView);
		
		mTextureView.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View arg0) 
			{
				takePicture();
			}
        });
		
		reorganize();
		this.setContentView(sv_);
		
		
	}
	
	@Override
	public boolean onCreateOptionsMenu(Menu menu) 
	{
		menu.add(Menu.NONE, 1, Menu.NONE, "Clean");
		menu.add(Menu.NONE, 2, Menu.NONE, "Save");
		
		return super.onCreateOptionsMenu(menu);
	}
	
	@Override
	public boolean onOptionsItemSelected(MenuItem item) 
	{
		if (item.getItemId() == 1)
		{
			clearAll();
		}
		else if (item.getItemId() == 2)
		{
			saveCollage();
		}
		
		return super.onOptionsItemSelected(item);
	}

	private void clearAll()
	{
		System.out.println("Cleaning");
		removeImageViews(false);
		while(bitmaps.size() > 0)
		{
			bitmaps.remove(0);
		}
		
		ids = 1000;
		active = null;
		reorganize();
		Toast.makeText(this, "Cleaned", Toast.LENGTH_SHORT).show();
	}
	
	private void saveCollage()
	{
		if (bitmaps.size() == 0)
		{
			Toast.makeText(this, "No Images", Toast.LENGTH_SHORT).show();
		}
		else if (bitmaps.size() == 1)
		{
			Toast.makeText(this, "Use a regular camera", Toast.LENGTH_SHORT).show();
		}
		else
		{
			Bitmap result = this.combineImageIntoOne(bitmaps);
			
			File folder = new File(Environment.getExternalStorageDirectory(),"collages");
			folder.mkdir();
			FileOutputStream out = null;
			
			Calendar c = Calendar.getInstance();
			String date = String.valueOf(c.get(Calendar.MONTH))
			            + String.valueOf(c.get(Calendar.DAY_OF_MONTH))
			            + String.valueOf(c.get(Calendar.YEAR))
			            + String.valueOf(c.get(Calendar.HOUR_OF_DAY))
			            + String.valueOf(c.get(Calendar.MINUTE))
			            + String.valueOf(c.get(Calendar.SECOND));
			
			File name = new File(folder, date.toString() + ".jpg");

			try
			{
				 out = new FileOutputStream(name);
				 result.compress(Bitmap.CompressFormat.JPEG, 100, out);
				 out.flush();
				 out.close();
				 scanPhoto(name);
				 out = null;
				 Toast.makeText(this, "Saved", Toast.LENGTH_SHORT).show();
			} 
			catch (Exception e)
			{
				e.printStackTrace();
			}
		}
	}
	
	private void scanPhoto(File f)
	{
		Intent mediaScanIntent = new Intent(Intent.ACTION_MEDIA_SCANNER_SCAN_FILE);
	    Uri contentUri = Uri.fromFile(f);
	    mediaScanIntent.setData(contentUri);
	    getApplicationContext().sendBroadcast(mediaScanIntent);
	}

	private void takePicture()
	{
		mCamera.takePicture(null, null, null, this);
	}

	public void onSurfaceTextureAvailable(SurfaceTexture surface, int width, int height) {
		
		mCamera = Camera.open();

		try 
		{
			mCamera.setPreviewTexture(surface);
			mCamera.startPreview();
		} 
		catch (IOException ioe) 
		{
			// Something bad happened
		}
	}

	public void onSurfaceTextureSizeChanged(SurfaceTexture surface, int width,int height) 
	{
		// Ignored, Camera does all the work for us
	}

	public boolean onSurfaceTextureDestroyed(SurfaceTexture surface) 
	{
		mCamera.stopPreview();
		mCamera.release();
		return true;
	}
	
	public void onSurfaceTextureUpdated(SurfaceTexture surface) 
	{
		// Invoked every time there's a new Camera preview frame
	}

	@Override
	public boolean onTouch(View view, MotionEvent event) 
	{
		if (viewList_.size() < 5 && active != null)
		{
			if (event.getAction() == MotionEvent.ACTION_MOVE)
			{
				active.setX(event.getX() - active.getWidth()/2);
				active.setY(event.getY()- active.getHeight()/2);
			}
		}
		return true;
	}
	
	private void reorganize()
	{	
		removeImageViews(true);
		
		LayoutParams previewParams = new LayoutParams(LayoutParams.WRAP_CONTENT, LayoutParams.WRAP_CONTENT);
		previewParams.width = 320;
		previewParams.height = 240;
		if (viewList_.size() != 0)
		{	
			for (int i = 0; i <  viewList_.size(); i ++)
			{
				LayoutParams imgParams = new LayoutParams(
						RelativeLayout.LayoutParams.WRAP_CONTENT,
						RelativeLayout.LayoutParams.WRAP_CONTENT);
				imgParams.width = 320;
				imgParams.height = 240;
				
				if (i == 0)
				{
					imgParams.addRule(RelativeLayout.ALIGN_PARENT_LEFT);
					imgParams.addRule(RelativeLayout.ALIGN_PARENT_TOP);
				}
				else if ( (i>3) && ( ( (i-4)%4 ) == 0) )
				{
					imgParams.addRule(RelativeLayout.BELOW, viewList_.get(i - 4).getId());
					imgParams.addRule(RelativeLayout.ALIGN_RIGHT, viewList_.get(i - 4).getId());
				}
				else
				{
					imgParams.addRule(RelativeLayout.RIGHT_OF, viewList_.get(i - 1).getId());
					imgParams.addRule(RelativeLayout.ALIGN_BASELINE, viewList_.get(i - 1).getId());
					imgParams.addRule(RelativeLayout.ALIGN_BOTTOM, viewList_.get(i - 1).getId());
				}
				
				viewList_.get(i).setLayoutParams(imgParams);
				rl_.addView(viewList_.get(i));
			}
			
			if (viewList_.size() % 4 == 0)
			{
				previewParams.addRule(RelativeLayout.BELOW, viewList_.get(viewList_.size() - 4).getId());
				previewParams.addRule(RelativeLayout.ALIGN_RIGHT, viewList_.get(viewList_.size() - 4).getId());
			}
			else
			{
				previewParams.addRule(RelativeLayout.RIGHT_OF, viewList_.get(viewList_.size() - 1).getId());
				previewParams.addRule(RelativeLayout.ALIGN_BASELINE, viewList_.get(viewList_.size() - 1).getId());
				previewParams.addRule(RelativeLayout.ALIGN_BOTTOM, viewList_.get(viewList_.size() - 1).getId());
			}
		}	
		
		mTextureView.setLayoutParams(previewParams);
	}

	@Override
	public void onPictureTaken(byte[] data, Camera camera) 
	{
		Bitmap bmp = BitmapFactory.decodeByteArray(data, 0, data.length);
		Bitmap scaled = Bitmap.createScaledBitmap(bmp, 320, 240, false);
		ImageView img = new ImageView(this);
		img.setImageBitmap(scaled);
		img.setId(ids);
		
		img.setOnTouchListener(new OnTouchListener() {
			@Override
			public boolean onTouch(View view, MotionEvent event) 
			{
				active = view;
				return false;
			}
        });
		
		ids++;
		viewList_.add(img);
		bitmaps.add(scaled);
		rl_.addView(img);
		reorganize();
		mCamera.startPreview();
	}
	
	private void removeImageViews(boolean recreate)
	{
		while(viewList_.size() > 0)
		{
			rl_.removeView(viewList_.remove(0));
		}
		
		ids = 1000;
		
		if (recreate)
		{
			for (int i = 0; i < bitmaps.size(); i ++)
			{
				ImageView view = new ImageView(this);
				view.setImageBitmap(bitmaps.get(i));
				view.setId(ids);
				view.setOnTouchListener(new OnTouchListener() {
					@Override
					public boolean onTouch(View view, MotionEvent event) 
					{
						active = view;
						return false;
					}
		        });
				
				ids ++;
				viewList_.add(view);
			}
		}
	}
	
	private Bitmap combineImageIntoOne(ArrayList<Bitmap> bitmap) { 
		 int w = 0, h = 0; 
		 for (int i = 0; i < bitmap.size(); i++) { 
		 if (i < bitmap.size() - 1) { 
		 w = bitmap.get(i).getWidth() > bitmap.get(i + 1).getWidth() ? 
		 bitmap.get(i).getWidth() : bitmap.get(i + 1).getWidth(); 
		 } 
		 h += bitmap.get(i).getHeight(); 
		 } 
		 
		 Bitmap temp = Bitmap.createBitmap(w, h, Bitmap.Config.ARGB_8888); 
		 Canvas canvas = new Canvas(temp); 
		 int top = 0; 
		 for (int i = 0; i < bitmap.size(); i++) { 
		 top = (i == 0 ? 0 : top+bitmap.get(i).getHeight()); 
		 canvas.drawBitmap(bitmap.get(i), 0f, top, null); 
		 } 
		 return temp; 
	} 
	
}