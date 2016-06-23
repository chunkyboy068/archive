package com.ece4564.group11.workout.server;

/**
 * This class is responsible for getting a quote from quotes.xml.  It grabs
 * the initial quote as well as once every 24 hours at 2AM. Implments singleton
 * pattern.
 */

import java.io.File;
import java.util.Calendar;
import java.util.List;
import java.util.Random;
import java.util.Timer;
import java.util.TimerTask;

import org.jdom2.Document;
import org.jdom2.Element;
import org.jdom2.input.SAXBuilder;

public class QuoteGrabber extends TimerTask {

	private static QuoteGrabber quoteGrab_ = new QuoteGrabber();

	String qotd_;
	Random random_;
	int curNum_;
	SAXBuilder builder_;
	File xmlFile_;
	Timer timer_;

	public static QuoteGrabber getInstance() {
		return quoteGrab_;
	}

	private QuoteGrabber() {
		qotd_ = "You're a wizard, Harry.";
		random_ = new Random();
		curNum_ = -9999;
		builder_ = new SAXBuilder();
		randomizeQuote();
		setupTimer();
	}

	private void setupTimer() {
		timer_ = new Timer();
		Calendar date = Calendar.getInstance();
		date.set(Calendar.HOUR_OF_DAY, 2);
		timer_.scheduleAtFixedRate(this, date.getTime(), 86400000);
	}

	protected String getQuote() {
		return qotd_;
	}

	private void randomizeIndex() {
		curNum_ = random_.nextInt(14);
	}

	protected void randomizeQuote() {
		System.out.println("Getting new Random Quote from file...");

		randomizeIndex();
		System.out.println("New Random ID: " + curNum_);

		xmlFile_ = new File("quotes.xml");
		if (xmlFile_.exists()) {
			System.out.println("Quote File found. Building file...");
		} else {
			System.out.println("Error. Quote File NOT found. Stopping...");
			return;
		}

		Document d = buildFile(xmlFile_);
		if (d == null) {
			return;
		}

		String nextQuote = getFromDoc(d);

		if (nextQuote == null) {
			return;
		} else {
			qotd_ = nextQuote;
			System.out.println("New Quote: \n" + qotd_);
		}

	}

	private Document buildFile(File f) {
		try {
			Document doc = (Document) builder_.build(xmlFile_);
			return doc;
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("Error: could not build file. Stopping...");
			return null;
		}
	}

	private String getFromDoc(Document document) {
		try {
			Element rootNode = document.getRootElement();
			List<Element> list = rootNode.getChildren("quote");

			for (Element node : list) {
				if (Integer.parseInt(node.getAttributeValue("id")) == curNum_) {
					return (node.getChildText("body") + " -- " + node
							.getChildText("author"));
				}
			}

			return "You're a wizard, Harry.";
		} catch (Exception e) {
			System.out.println("Error Parsing XML file. Stopping...");
			e.printStackTrace();
			return null;
		}
	}

	@Override
	public void run() {
		System.out.println("Scheduled Randomization of Quote Starting...");
		randomizeQuote();
	}
}
