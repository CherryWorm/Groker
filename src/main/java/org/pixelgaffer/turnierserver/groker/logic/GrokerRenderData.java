/*
 * GrokerRenderData.java
 *
 * Copyright (C) 2015 Pixelgaffer
 *
 * This work is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or any later
 * version.
 *
 * This work is distributed in the hope that it will be useful, but without
 * any warranty; without even the implied warranty of merchantability or
 * fitness for a particular purpose. See version 2 and version 3 of the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
package org.pixelgaffer.turnierserver.groker.logic;

import java.util.HashMap;

import org.pixelgaffer.turnierserver.groker.GrokerGameState;

public class GrokerRenderData {

	public GrokerRenderData(GrokerGameState state, String name1, String name2) {
		chips = new HashMap<>();
		chips.put(name1, state.chips[0]);
		chips.put(name2, state.chips[1]);
		wonChips = new HashMap<>();
		wonChips.put(name1, state.wonChips[0]);
		wonChips.put(name2, state.wonChips[1]);
		output = new HashMap<>();
		output.put(name1, state.output[0]);
		output.put(name2, state.output[1]);
	}

	public GrokerRenderData(String name1, String name2) {
		chips = new HashMap<>();
		chips.put(name1, 0);
		chips.put(name2, 0);
		wonChips = new HashMap<>();
		wonChips.put(name1, 0);
		wonChips.put(name2, 0);
		output = new HashMap<>();
		output.put(name1, "Das Spiel startet nun");
		output.put(name2, "Das Spiel startet nun");
	}

	
	public HashMap<String, Integer> chips;
	public HashMap<String, Integer> wonChips;
	public HashMap<String, String> output;

}
