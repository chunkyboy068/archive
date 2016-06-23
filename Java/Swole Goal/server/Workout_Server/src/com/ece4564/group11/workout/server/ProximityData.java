package com.ece4564.group11.workout.server;

/**
 * Stores Persons into a hashmap with their GPS locations. Implements singleton
 * design pattern.
 */

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map.Entry;
import java.util.UUID;

public class ProximityData {

	private static ProximityData prox_ = new ProximityData();

	HashMap<UUID, Person> list_;

	private ProximityData() {
		list_ = new HashMap<UUID, Person>();
	}

	public static ProximityData getInstance() {
		return prox_;
	}

	protected void addNew(UUID id, Person person) {
		list_.put(id, person);
	}

	protected ArrayList<String> getLocal(Person newPerson) {
		ArrayList<String> match = new ArrayList<String>();

		Person current;
		for (Entry<UUID, Person> entry : list_.entrySet()) {
			current = entry.getValue();
			if (newPerson.isCloseTo(current)) {
				match.add(current.getName());
			}
		}
		return match;
	}

	protected void removeUUID(UUID id) {
		list_.remove(id);
	}

}
