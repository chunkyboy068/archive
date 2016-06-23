package com.StadiumActivity;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

import twitter4j.IDs;
import twitter4j.Twitter;
import twitter4j.TwitterException;
import twitter4j.TwitterFactory;
import twitter4j.User;
import twitter4j.auth.AccessToken;
import twitter4j.conf.ConfigurationBuilder;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.location.Location;
import android.location.LocationListener;
import android.location.LocationManager;
import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageButton;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;

import com.Login.Friend;
import com.Login.LoginScreen;
import com.Login.RetrieveFollowedTask;
import com.Login.UpdateStatus;
import com.StadiumList.StadiumItem;
import com.StadiumList.StadiumList;
import com.example.projectstadium.R;
import com.StadiumView.StadiumView;

/**
 * A fragment representing a single Stadium detail screen. This fragment is
 * either contained in a {@link StadiumListActivity} in two-pane mode (on
 * tablets) or a {@link StadiumDetailActivity} on handsets.
 */
public class StadiumDetailFragment extends Fragment implements LocationListener {
	/**
	 * The fragment argument representing the item ID that this fragment
	 * represents.
	 */
	public static final String ARG_ITEM_ID = "item_id";

	/**
	 * The dummy content this fragment is presenting.
	 */
	private StadiumItem mItem;

	/**
	 * Mandatory empty constructor for the fragment manager to instantiate the
	 * fragment (e.g. upon screen orientation changes).
	 */
	public static ArrayList<Friend> friends;

	public static int myArea = -1;

	private boolean[] occupiedSection;
	private ListView friends_ListView;
	private ArrayList<String> contents_;
	private EditText sectionNum_;
	private ImageButton update_;
	private SharedPreferences mSharedPreferences;
	private ImageButton stadiumView_;
	private String mySection;

	private long[] friendIDs;

	private boolean hasLoadedContent;

	private TextView whereSitting_;
	private LocationManager locManager;

	private Location myLoc;

	private boolean hasConfirmedLocation;

	private Button cheatButton;

	public StadiumDetailFragment() {
	}

	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		if (getArguments().containsKey(ARG_ITEM_ID)) {
			// Load the dummy content specified by the fragment
			// arguments. In a real-world scenario, use a Loader
			// to load content from a content provider.
			mItem = StadiumList.item_map.get(getArguments().getString(
					ARG_ITEM_ID));

		}

		locManager = (LocationManager) this.getActivity().getSystemService(
				Context.LOCATION_SERVICE);

		boolean isGPSEnabled = locManager
				.isProviderEnabled(LocationManager.GPS_PROVIDER);

		if (isGPSEnabled) {
			locManager.requestLocationUpdates(LocationManager.GPS_PROVIDER,
					1000, 10, this);
		}
	}

	@Override
	public View onCreateView(LayoutInflater inflater, ViewGroup container,
			Bundle savedInstanceState) {
		View rootView = inflater.inflate(R.layout.fragment_stadium_detail,
				container, false);

		// Show the dummy content as text in a TextView.
		if (mItem != null) {
			((TextView) rootView.findViewById(R.id.stadium_detail))
					.setText(mItem.getContent());
		}
		stadiumView_ = (ImageButton) rootView
				.findViewById(R.id.btn_stadiumView);
		update_ = (ImageButton) rootView.findViewById(R.id.btnCheckIn);
		contents_ = new ArrayList<String>();
		friends_ListView = (ListView) rootView.findViewById(R.id.friend_list);
		sectionNum_ = (EditText) rootView.findViewById(R.id.seatInput);
		mSharedPreferences = this.getActivity().getSharedPreferences("MyPref",
				0);
		whereSitting_ = (TextView) rootView.findViewById(R.id.textView1);

		cheatButton = (Button) rootView.findViewById(R.id.button1);

		cheatButton.setOnClickListener(new View.OnClickListener() {

			@Override
			public void onClick(View v) {
				hasConfirmedLocation = true;
			}

		});

		friends = new ArrayList<Friend>();
		occupiedSection = new boolean[10];

		hasLoadedContent = false;
		hasConfirmedLocation = false;

		/**
		 * Button click event to Update Status, will call updateTwitterStatus()
		 * function
		 * */
		update_.setOnClickListener(new View.OnClickListener() {

			@Override
			public void onClick(View v) {
				// Call update status function
				// Get the status from EditText
				String status = sectionNum_.getText().toString();
				checkLocation();
				// Check for blank text
				if (!hasConfirmedLocation) {
					toastInvalidLocation();
				} else if (status.trim().length() > 0) {
					mySection = status;

					myArea = setOccupied(mySection);

					whereSitting_.setText("You are in section " + status);

					sectionNum_.setText("Check in a new section...");

					// update status
					status = "I'm at " + mItem.getContent()
							+ ", sitting in section " + status + " #FanMeetup";
					update(status);

				} else {
					emptyTextBox();
				}
			}

		});

		stadiumView_.setOnClickListener(new View.OnClickListener() {
			@Override
			public void onClick(View v) {
				startStadiumView();
			}
		});

		new RetrieveFollowedTask(this.getActivity(), mSharedPreferences, this)
				.execute();

		return rootView;
	}

	private void toastInvalidLocation() {
		Toast.makeText(this.getActivity(),
				"Get to the stadium first, before checking in.",
				Toast.LENGTH_SHORT).show();

	}

	protected void startStadiumView() {
		if (hasLoadedContent) {
			Intent intent = new Intent(this.getActivity(), StadiumView.class);
			startActivity(intent);
		}
	}

	public void update(String s) {
		// new StadiumDetailActivity.updateTwitterStatus().execute(status);
		new UpdateStatus(this.getActivity(), mSharedPreferences, this)
				.execute(s);

	}

	public void emptyTextBox() {
		Toast.makeText(this.getActivity(), "Please enter status message",
				Toast.LENGTH_SHORT).show();
	}

	public EditText getSection() {
		return sectionNum_;
	}

	public void addFriend(Friend friend) {
		friends.add(friend);
	}

	public void processIds(IDs ids) {
		friendIDs = ids.getIDs().clone();

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
		Twitter twitter = new TwitterFactory(builder.build())
				.getInstance(accessToken);

		for (long id : friendIDs) {
			User user;
			try {
				user = twitter.showUser(id);

				String name = user.getScreenName();
				String sectionNum = "";
				int area = -1;

				List<twitter4j.Status> statuseses = twitter
						.getUserTimeline(name);
				String statusText = null;
				for (twitter4j.Status status : statuseses) {
					statusText = status.getText();
					String[] exprArray = statusText.split("\\s+");

					String finalExpr = exprArray[exprArray.length - 1];
					if (finalExpr.equals("#FanMeetup")) {
						sectionNum = exprArray[exprArray.length - 2];
						area = setOccupied(sectionNum);
						break;
					}
				}
				if (!sectionNum.equals("") && area != -1) {
					Friend friend = new Friend(name, "Lane Stadium",
							sectionNum, area);
					addFriend(friend);
				}
			} catch (TwitterException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		setUpContents();
	}

	public int setOccupied(String sec) {

		try {
			int num = Integer.parseInt(sec);
			if (num % 2 == 1 && num > 20 && num < 40) {
				occupiedSection[1] = true;
				return 1;
			} else if (num == 1 || num == 3 || num == 5) {
				occupiedSection[2] = true;
				return 2;
			} else if (num == 7 || num == 9 || num == 11 || num == 13) {
				occupiedSection[3] = true;
				return 3;
			} else if (num == 15 || num == 17 || num == 19) {
				occupiedSection[4] = true;
				return 4;
			} else if ((num > 400 && num < 410) || (num > 500 && num < 511)) {
				occupiedSection[5] = true;
				return 5;
			} else if ((num > 100 && num < 106) || (num > 200 && num < 207)) {
				occupiedSection[6] = true;
				return 6;
			} else if (num == 16 || num == 18 || num == 20) {
				occupiedSection[7] = true;
				return 7;
			} else if (num == 8 || num == 10 || num == 12 || num == 14) {
				occupiedSection[8] = true;
				return 8;
			} else if (num == 2 || num == 4 || num == 6) {
				occupiedSection[9] = true;
				return 9;
			}
		} catch (NumberFormatException e) {
			if (sec.equals("A") || sec.equals("B") || sec.equals("C")
					|| sec.equals("D") || sec.equals("E") || sec.equals("F")
					|| sec.equals("G") || sec.equals("H") || sec.equals("J")
					|| sec.equals("CC") || sec.equals("DD") || sec.equals("EE")
					|| sec.equals("FF") || sec.equals("GG")) {

				occupiedSection[0] = true;
				return 0;
			}
		}
		return -1;

	}

	public boolean[] getOccupied() {
		return occupiedSection;
	}

	public void setUpContents() {
		hasLoadedContent = true;

		for (Friend friend : friends) {
			contents_.add(friend.getCheckInStatus());
		}

		StableArrayAdapter adapter = new StableArrayAdapter(this.getActivity(),
				android.R.layout.simple_list_item_1, contents_);

		friends_ListView.setAdapter(adapter);
	}

	private class StableArrayAdapter extends ArrayAdapter<String> {

		HashMap<String, Integer> mIdMap = new HashMap<String, Integer>();

		public StableArrayAdapter(Context context, int textViewResourceId,
				List<String> objects) {
			super(context, textViewResourceId, objects);
			for (int i = 0; i < objects.size(); ++i) {
				mIdMap.put(objects.get(i), i);
			}
		}

		@Override
		public long getItemId(int position) {
			String item = getItem(position);
			return mIdMap.get(item);
		}

		@Override
		public boolean hasStableIds() {
			return true;
		}

	}

	private void checkLocation() {
		if (myLoc != null) {
			double latitude = myLoc.getLatitude();
			double longitude = myLoc.getLongitude();

			double upperLeftX = 37.231891;
			double upperLeftY = -80.423513;

			double lowerRightX = 37.230533;
			double lowerRightY = -80.421877;

			if (latitude > lowerRightX && latitude < upperLeftX
					&& longitude < lowerRightY && longitude > upperLeftY) {

				hasConfirmedLocation = true;

			}
		}
	}

	@Override
	public void onLocationChanged(Location location) {
		myLoc = location;

	}

	@Override
	public void onStatusChanged(String provider, int status, Bundle extras) {
		// TODO Auto-generated method stub

	}

	@Override
	public void onProviderEnabled(String provider) {
		// TODO Auto-generated method stub

	}

	@Override
	public void onProviderDisabled(String provider) {
		// TODO Auto-generated method stub

	}

}