package org.pixelgaffer.turnierserver.groker.logic;

import java.util.HashMap;

import org.pixelgaffer.turnierserver.groker.GrokerGameState;

public class GrokerRenderData {

	public GrokerRenderData(GrokerGameState state, String name1, String name2) {
		chips = new HashMap<>();
		chips.put(name1, state.chips[0]);
		chips.put(name2, state.chips[1]);
		wallet = new HashMap<>();
		wallet.put(name1, state.wallet[0]);
		wallet.put(name2, state.wallet[1]);
		wonChips = new HashMap<>();
		wonChips.put(name1, state.wonChips[0]);
		wonChips.put(name2, state.wonChips[1]);
		output = new HashMap<>();
		output.put(name1, state.output[0]);
		output.put(name2, state.output[1]);
	}

	public HashMap<String, Integer> chips;
	public HashMap<String, Integer> wallet;
	public HashMap<String, Integer> wonChips;
	public HashMap<String, String> output;

}
