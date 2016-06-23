package com.ece4564.group11.workout.media;

/*
 * Music player class which allows selection of 2 files and playing these files one at a time
 * with the ability to switch between them at any time.
 */

import java.io.File;

import android.media.AudioManager;
import android.media.MediaPlayer;
import android.media.MediaPlayer.OnPreparedListener;

public class MusicPlayer {

	MediaPlayer mp_;
	MediaPlayer mp2_;

	int playstate;

	String path1_;
	String path2_;

	public MusicPlayer(OnPreparedListener opl, OnPreparedListener opl2) {
		mp_ = new MediaPlayer();
		mp_.setAudioStreamType(AudioManager.STREAM_MUSIC);
		mp_.setOnPreparedListener(opl);

		mp2_ = new MediaPlayer();
		mp2_.setAudioStreamType(AudioManager.STREAM_MUSIC);
		mp2_.setOnPreparedListener(opl2);

		playstate = 0;
	}

	public MusicPlayer() {
		mp_ = new MediaPlayer();
		mp_.setAudioStreamType(AudioManager.STREAM_MUSIC);

		mp2_ = new MediaPlayer();
		mp2_.setAudioStreamType(AudioManager.STREAM_MUSIC);

		playstate = 0;
	}

	public void setOnPreparedListener(OnPreparedListener opl,
			OnPreparedListener opl2) {
		mp_.setOnPreparedListener(opl);
		mp2_.setOnPreparedListener(opl2);
	}

	private void resetData(int id) {
		try {
			if (id == 1 && checkFile(path1_)) {
				mp_.setDataSource(path1_);
				mp_.prepareAsync();
			} else if (id == 2 && checkFile(path2_)) {
				mp2_.setDataSource(path2_);
				mp2_.prepareAsync();
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	public void start(int id) {

		if (id == 0) {
			if (playstate == 0) {
				start(1);
			} else {
				start(playstate);
			}
		}
		if (id == 1) {
			mp_.start();
			playstate = 1;
		} else if (id == 2) {
			mp2_.start();
			playstate = 2;
		}
	}

	public void switchSongs() {
		if (playstate == 1) {
			playstate = 2;
			mp_.pause();
			mp2_.start();
		} else if (playstate == 2) {
			playstate = 1;
			mp2_.pause();
			mp_.start();
		}
	}

	public void pause() {

		if (playstate == 1) {
			mp_.pause();
		} else if (playstate == 2) {
			mp2_.pause();
		}
	}

	public void reset(int id) {
		if (id == 0) {
			mp_.reset();
			mp2_.reset();
		} else if (id == 1) {
			mp_.reset();
		} else if (id == 2) {
			mp2_.reset();
		}

		playstate = 0;
	}

	public void release() {
		mp_.release();
		mp2_.release();
	}

	public void setFirstPath(String s) {
		path1_ = s;
		reset(1);
		resetData(1);
	}

	public void setSecondPath(String s) {
		path2_ = s;
		reset(2);
		resetData(2);
	}

	private boolean checkFile(String s) {
		File file = new File(s);
		return file.exists();
	}
}
