package com.ece4564.group11.workout.sensor;

/*
 * This class is based on the factory design pattern.  It generates a UUID based on if certain features
 * are present, eventually defaulting on a random UUID.
 */

import android.content.Context;
import android.content.SharedPreferences;
import android.provider.Settings.Secure;
import android.telephony.TelephonyManager;

import java.io.UnsupportedEncodingException;
import java.util.UUID;

public class DeviceUuidFactory {
	protected static final String PREFS_FILE = "device_id.xml";
	protected static final String PREFS_DEVICE_ID = "device_id";
	protected volatile static UUID uuid;

	public DeviceUuidFactory(Context context) {
		if (uuid == null) {
			synchronized (DeviceUuidFactory.class) {
				if (uuid == null) {
					final SharedPreferences prefs = context
							.getSharedPreferences(PREFS_FILE, 0);
					final String id = prefs.getString(PREFS_DEVICE_ID, null);
					if (id != null) {
						uuid = UUID.fromString(id);

					} else {
						final String androidId = Secure
								.getString(context.getContentResolver(),
										Secure.ANDROID_ID);
						try {
							if (!("9774d56d682e549c".equals(androidId))) {
								uuid = UUID.nameUUIDFromBytes(androidId
										.getBytes("utf8"));
							} else {
								final String deviceId = ((TelephonyManager) context
										.getSystemService(Context.TELEPHONY_SERVICE))
										.getDeviceId();

								if (deviceId == null) {
									uuid = UUID.randomUUID();
								} else {
									uuid = UUID.nameUUIDFromBytes(deviceId
											.getBytes("utf8"));
								}
							}
						} catch (UnsupportedEncodingException e) {
							e.printStackTrace();
							System.out.println("Could not Generate UUID");
						}
						prefs.edit()
								.putString(PREFS_DEVICE_ID, uuid.toString())
								.commit();
					}
				}
			}
		}
	}
	public UUID getDeviceUuid() {
		return uuid;
	}
}
