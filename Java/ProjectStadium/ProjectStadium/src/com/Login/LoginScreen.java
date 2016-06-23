package com.Login;

import twitter4j.Twitter;
import twitter4j.TwitterException;
import twitter4j.TwitterFactory;
import twitter4j.User;
import twitter4j.auth.AccessToken;
import twitter4j.auth.RequestToken;
import twitter4j.conf.Configuration;
import twitter4j.conf.ConfigurationBuilder;

import com.StadiumActivity.StadiumListActivity;
import com.example.projectstadium.R;

import android.app.Activity;
import android.app.ProgressDialog;
import android.content.Intent;
import android.content.SharedPreferences;
import android.content.SharedPreferences.Editor;
import android.content.pm.ActivityInfo;
import android.net.Uri;
import android.os.Bundle;
import android.os.StrictMode;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.ImageButton;
import android.widget.Toast;

public class LoginScreen extends Activity {
	// ..........
	// Constants
	/**
	 * Register your here app https://dev.twitter.com/apps/new and get your
	 * consumer key and secret
	 * */
	public static String TWITTER_CONSUMER_KEY = "DmZGjxPzh7JKxLCya5IiA";
	public static String TWITTER_CONSUMER_SECRET = "orxtvFo4rl6wIPsfKxtdpEgOZYzYIb15mdDpdR9rtMY";

	// Preference Constants
	static String PREFERENCE_NAME = "twitter_oauth";
	public static final String PREF_KEY_OAUTH_TOKEN = "oauth_token";
	public static final String PREF_KEY_OAUTH_SECRET = "oauth_token_secret";
	static final String PREF_KEY_TWITTER_LOGIN = "isTwitterLogedIn";

	static final String TWITTER_CALLBACK_URL = "oauth://t4jsample";

	// Twitter oauth urls
	static final String URL_TWITTER_AUTH = "auth_url";
	static final String URL_TWITTER_OAUTH_VERIFIER = "oauth_verifier";
	static final String URL_TWITTER_OAUTH_TOKEN = "oauth_token";

	// Login button
	private ImageButton login_;
	private Button logout_;

	// Progress dialog
	private ProgressDialog pDialog;

	// Twitter
	private static Twitter twitter;
	private static RequestToken requestToken;

	// Shared Preferences
	private SharedPreferences mSharedPreferences;

	// Internet Connection detector
	private ConnectionDetector cd;

	// Alert Dialog Manager
	AlertDialogManager alert = new AlertDialogManager();

	// ................................................................................

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		this.setContentView(R.layout.activity_login);

		StrictMode.ThreadPolicy policy = new StrictMode.ThreadPolicy.Builder()
				.permitAll().build();
		StrictMode.setThreadPolicy(policy);
		setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_PORTRAIT);

		cd = new ConnectionDetector(getApplicationContext());

		// Check if Internet present
		if (!cd.isConnectingToInternet()) {
			// Internet Connection is not present
			alert.showAlertDialog(LoginScreen.this,
					"Internet Connection Error",
					"Please connect to working Internet connection", false);
			// stop executing code by return
			return;
		}

		// Check if twitter keys are set
		if (TWITTER_CONSUMER_KEY.trim().length() == 0
				|| TWITTER_CONSUMER_SECRET.trim().length() == 0) {
			// Internet Connection is not present
			alert.showAlertDialog(LoginScreen.this, "Twitter oAuth tokens",
					"Please set your twitter oauth tokens first!", false);
			// stop executing code by return
			return;
		}

		//
		login_ = (ImageButton) this.findViewById(R.id.btn_login);
		logout_ = (Button) this.findViewById(R.id.btn_stadiumView);

		// Shared Preferences
		mSharedPreferences = getApplicationContext().getSharedPreferences(
				"MyPref", 0);

		login_.setOnClickListener(new OnClickListener() {

			@Override
			public void onClick(View arg0) {
				loginToTwitter();
			}
		});

		logout_.setOnClickListener(new View.OnClickListener() {

			@Override
			public void onClick(View arg0) {
				// Call logout twitter function
				logoutFromTwitter();
			}
		});

		/**
		 * This if conditions is tested once is redirected from twitter page.
		 * Parse the uri to get oAuth Verifier
		 * */
		if (!isTwitterLoggedInAlready()) {
			Uri uri = getIntent().getData();
			if (uri != null && uri.toString().startsWith(TWITTER_CALLBACK_URL)) {
				// oAuth verifier
				String verifier = uri
						.getQueryParameter(URL_TWITTER_OAUTH_VERIFIER);

				try {
					// Get the access token
					AccessToken accessToken = twitter.getOAuthAccessToken(
							requestToken, verifier);

					// Shared Preferences
					Editor e = mSharedPreferences.edit();

					// After getting access token, access token secret
					// store them in application preferences
					e.putString(PREF_KEY_OAUTH_TOKEN, accessToken.getToken());
					e.putString(PREF_KEY_OAUTH_SECRET,
							accessToken.getTokenSecret());
					// Store login status - true
					e.putBoolean(PREF_KEY_TWITTER_LOGIN, true);
					e.commit(); // save changes

					Log.e("Twitter OAuth Token", "> " + accessToken.getToken());


					Intent intent = new Intent(this, StadiumListActivity.class);
					startActivity(intent);

					// Getting user details from twitter
					// For now i am getting his name only
					long userID = accessToken.getUserId();
					User user = twitter.showUser(userID);
					String username = user.getName();

					// // Displaying in xml ui
					// lblUserName.setText(Html.fromHtml("<b>Welcome " +
					// username + "</b>"));
				} catch (Exception e) {
					// Check log for login errors
					Log.e("Twitter Login Error", "> " + e.getMessage());
				}
			}
		}

	}

	/**
	 * Function to login twitter
	 * */
	private void loginToTwitter() {
		// Check if already logged in
		if (!isTwitterLoggedInAlready()) {
			ConfigurationBuilder builder = new ConfigurationBuilder();
			builder.setOAuthConsumerKey(TWITTER_CONSUMER_KEY);
			builder.setOAuthConsumerSecret(TWITTER_CONSUMER_SECRET);
			Configuration configuration = builder.build();

			TwitterFactory factory = new TwitterFactory(configuration);
			twitter = factory.getInstance();



			// ___________________
			try {
				requestToken = twitter
						.getOAuthRequestToken(TWITTER_CALLBACK_URL);
				this.startActivity(new Intent(Intent.ACTION_VIEW, Uri
						.parse(requestToken.getAuthenticationURL())));
//				Intent intent = new Intent(this, StadiumListActivity.class);
//				startActivity(intent);
				
			} catch (TwitterException e) {
				e.printStackTrace();
			}
			// ___________________

		} else {
			// user already logged into twitter
			Toast.makeText(getApplicationContext(),
					"Already Logged into twitter", Toast.LENGTH_LONG).show();
			Intent intent = new Intent(this, StadiumListActivity.class);
			startActivity(intent);
		}
	}

	/**
	 * Function to logout from twitter It will just clear the application shared
	 * preferences
	 * */
	private void logoutFromTwitter() {
		// Clear the shared preferences
		Editor e = mSharedPreferences.edit();
		e.remove(PREF_KEY_OAUTH_TOKEN);
		e.remove(PREF_KEY_OAUTH_SECRET);
		e.remove(PREF_KEY_TWITTER_LOGIN);
		e.commit();

		// After this take the appropriate action
		// I am showing the hiding/showing buttons again
		// You might not needed this code

	}

	/**
	 * Check user already logged in your application using twitter Login flag is
	 * fetched from Shared Preferences
	 * */
	private boolean isTwitterLoggedInAlready() {
		// return twitter login status from Shared Preferences
		return mSharedPreferences.getBoolean(PREF_KEY_TWITTER_LOGIN, false);
	}

	protected void onResume() {
		super.onResume();
	}

}
