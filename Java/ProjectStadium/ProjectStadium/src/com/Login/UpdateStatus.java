package com.Login;

import twitter4j.Twitter;
import twitter4j.TwitterException;
import twitter4j.TwitterFactory;
import twitter4j.auth.AccessToken;
import twitter4j.conf.ConfigurationBuilder;
import android.app.Activity;
import android.app.ProgressDialog;
import android.content.SharedPreferences;
import android.os.AsyncTask;
import android.util.Log;
import android.widget.Toast;
import com.StadiumActivity.StadiumDetailFragment;


	/**
	 * Function to update status
	 * */
	public class UpdateStatus extends AsyncTask<String, String, String> {
		Activity parent;
		private SharedPreferences mSharedPreferences;
		ProgressDialog pDialog;
		StadiumDetailFragment frag;
		
		
		public UpdateStatus(Activity p, SharedPreferences prefs, StadiumDetailFragment f){
			parent = p;
			mSharedPreferences = prefs;
			frag = f;
		}
		/**
		 * Before starting background thread Show Progress Dialog
		 * */
		@Override
		protected void onPreExecute() {
			super.onPreExecute();
			pDialog = new ProgressDialog(parent);
			pDialog.setMessage("Updating to twitter...");
			pDialog.setIndeterminate(false);
			pDialog.setCancelable(false);
			pDialog.show();
		}

		/**
		 * getting Places JSON
		 * */
		protected String doInBackground(String... args) {
			Log.d("Tweet Text", "> " + args[0]);
			String status = args[0];
			try {
				ConfigurationBuilder builder = new ConfigurationBuilder();
				builder.setOAuthConsumerKey(LoginScreen.TWITTER_CONSUMER_KEY);
				builder.setOAuthConsumerSecret(LoginScreen.TWITTER_CONSUMER_SECRET);
				
				// Access Token 
				String access_token = mSharedPreferences.getString(LoginScreen.PREF_KEY_OAUTH_TOKEN, "");
				// Access Token Secret
				String access_token_secret = mSharedPreferences.getString(LoginScreen.PREF_KEY_OAUTH_SECRET, "");
				
				AccessToken accessToken = new AccessToken(access_token, access_token_secret);
				Twitter twitter = new TwitterFactory(builder.build()).getInstance(accessToken);
				
				// Update status
				twitter4j.Status response = twitter.updateStatus(status);
				
				Log.d("Status", "> " + response.getText());
			} catch (TwitterException e) {
				// Error in updating status
				Log.d("Twitter Update Error", e.getMessage());
			}
			return null;
		}

		/**
		 * After completing background task Dismiss the progress dialog and show
		 * the data in UI Always use runOnUiThread(new Runnable()) to update UI
		 * from background thread, otherwise you will get error
		 * **/
		protected void onPostExecute(String file_url) {
			// dismiss the dialog after getting all products
			pDialog.dismiss();
			// updating UI from Background Thread
			parent.runOnUiThread(new Runnable() {
				@Override
				public void run() {
					Toast.makeText(parent,
							"Status tweeted successfully", Toast.LENGTH_SHORT)
							.show();
					// Clearing EditText field
					frag.getSection().setText("");
				}
			});
		}
	}