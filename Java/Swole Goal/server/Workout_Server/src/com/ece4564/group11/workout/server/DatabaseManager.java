package com.ece4564.group11.workout.server;

/*
 * This class is used to manage the database. It handles creation, adding, and retrieving 
 * results.  It implements a singleton class since we only want a single thing accessing
 * the database at any given time.
 */

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;

import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;

public class DatabaseManager {

	private static DatabaseManager dbM_ = new DatabaseManager();

	Connection connect_;

	private DatabaseManager() {
		try {
			Class.forName("org.sqlite.JDBC");
			connect_ = DriverManager.getConnection("jdbc:sqlite:workout.db");
			System.out
					.println("Connected to database...\nSetting up database...");
			if (createTable()) {
				System.out.println("Database Connection Established");
			}

		} catch (Exception e) {
			System.err.println(e.getClass().getName() + ": " + e.getMessage());
		}
	}

	private boolean createTable() {
		String sql = "CREATE TABLE IF NOT EXISTS stored_programs"
				+ "(id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
				+ " uuid TEXT NOT NULL, " + " workout_name TEXT NOT NULL, "
				+ " data TEXT NOT NULL)";
		try {
			Statement stmt = connect_.createStatement();
			stmt.executeUpdate(sql);
			stmt.close();
			return true;
		} catch (SQLException e) {
			e.printStackTrace();
			return false;
		}
	}

	public static DatabaseManager getInstance() {
		return dbM_;
	}

	protected boolean addToDatabase(String jString, String name, String uuid) {
		PreparedStatement sql;
		try {
			sql = connect_
					.prepareStatement("INSERT INTO stored_programs (uuid,workout_name,data) "
							+ "VALUES (?,?,?);");
			sql.setString(1, uuid);
			sql.setString(2, name);
			sql.setString(3, jString);
			sql.executeUpdate();
			return true;
		} catch (SQLException e) {
			e.printStackTrace();
			return false;
		}
	}

	protected String getIDFromDataBase(String id) {
		PreparedStatement sql;

		try {
			sql = connect_
					.prepareStatement("SELECT * FROM stored_programs WHERE id = ?;");
			sql.setString(1, id);
			ResultSet rs = sql.executeQuery();

			while (rs.next()) {
				String data = rs.getString("data");
				return data;
			}
		} catch (Exception e) {
			e.printStackTrace();
			return null;
		}

		return null;
	}

	protected String getFromDatabase(String uuid) {
		PreparedStatement sql;

		try {
			sql = connect_
					.prepareStatement("SELECT * FROM stored_programs WHERE uuid = ?;");
			sql.setString(1, uuid);
			ResultSet rs = sql.executeQuery();

			JSONObject result = new JSONObject();
			JSONParser parser = new JSONParser();
			JSONObject tempOb;

			while (rs.next()) {
				String name = rs.getString("workout_name");
				String data = rs.getString("data");

				tempOb = (JSONObject) parser.parse(data);
				String plan = tempOb.get(name).toString();

				System.out.println("Appending: " + name + "||||||" + plan);
				result.put(name, plan);
			}

			System.out.println("Final Response:" + result.toString());
			return result.toString();
		} catch (Exception e) {
			System.out.println("Could Not Retrieve results for: " + uuid
					+ " from database");
			e.printStackTrace();
			return null;
		}
	}

	protected ArrayList<WorkoutEntry> getAll() {
		ArrayList<WorkoutEntry> allResults = new ArrayList<WorkoutEntry>();

		PreparedStatement sql;

		try {
			sql = connect_.prepareStatement("SELECT * FROM stored_programs;");
			ResultSet rs = sql.executeQuery();

			while (rs.next()) {
				String name = rs.getString("workout_name");
				String data = rs.getString("data");
				int id = rs.getInt("id");

				allResults.add(new WorkoutEntry(name, id, data));
			}

			return allResults;
		} catch (Exception e) {
			e.printStackTrace();
			return null;
		}

	}
}
