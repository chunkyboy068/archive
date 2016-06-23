package com.Login;

import java.util.ArrayList;
import java.util.List;

import twitter4j.IDs;
import twitter4j.Status;
import twitter4j.Twitter;
import twitter4j.TwitterException;
import twitter4j.TwitterFactory;
import twitter4j.User;
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
public class RetrieveFollowedTask extends AsyncTask<String, String, String> {
	Activity parent;
	Twitter twitter;
	private SharedPreferences mSharedPreferences;
	ProgressDialog pDialog;
	StadiumDetailFragment frag;
	IDs ids;

	public RetrieveFollowedTask(Activity p, SharedPreferences prefs,
			StadiumDetailFragment f) {
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
		pDialog.setMessage("Retrieving followed users...");
		pDialog.setIndeterminate(false);
		pDialog.setCancelable(false);
		pDialog.show();
	}

	/**
	 * getting Places JSON
	 * */
	protected String doInBackground(String... args) {
		try {
			ConfigurationBuilder builder = new ConfigurationBuilder();
			builder.setOAuthConsumerKey(LoginScreen.TWITTER_CONSUMER_KEY);
			builder.setOAuthConsumerSecret(LoginScreen.TWITTER_CONSUMER_SECRET);

			// Access Token
			String access_token = mSharedPreferences.getString(
					LoginScreen.PREF_KEY_OAUTH_TOKEN, "");
			// Access Token Secret
			String access_token_secret = mSharedPreferences.getString(
					LoginScreen.PREF_KEY_OAUTH_SECRET, "");

			AccessToken accessToken = new AccessToken(access_token,
					access_token_secret);
			twitter = new TwitterFactory(builder.build())
					.getInstance(accessToken);

			ids = twitter.getFriendsIDs(-1);
			
			
		} catch (TwitterException e) {
			// Error in updating status
			Log.d("Twitter Retrieve Error", e.getMessage());
		}
		return null;
	}

	/**
	 * After completing background task Dismiss the progress dialog and show the
	 * data in UI Always use runOnUiThread(new Runnable()) to update UI from
	 * background thread, otherwise you will get error
	 * **/
	protected void onPostExecute(String file_url) {
		// dismiss the dialog after getting all products
		pDialog.dismiss();
		// updating UI from Background Thread
		parent.runOnUiThread(new Runnable() {
			@Override
			public void run() {
				Toast.makeText(parent,
						"Retrieved followed users successfully.",
						Toast.LENGTH_SHORT).show();
				frag.processIds(ids);
			}
		});
	}
}