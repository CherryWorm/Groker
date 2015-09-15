/*
 * GrokerGameState.java
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
package org.pixelgaffer.turnierserver.groker;

import org.pixelgaffer.turnierserver.gamelogic.interfaces.Ai;
import org.pixelgaffer.turnierserver.gamelogic.interfaces.GameState;

public class GrokerGameState implements GameState<GrokerUpdate, GrokerResponse> {
		
	public int[] wonChips;
	public int[] chips;
	public String[] output;
	
	public GrokerGameState() {
		wonChips = new int[2];
		chips = new int[2];
		output = new String[2];
	}
	
	@Override
	public GrokerUpdate getChanges(Ai ai) {
		int otherIndex = ai.getIndex() == 0 ? 1 : 0;
		GrokerUpdate update = new GrokerUpdate();
		update.ownWonChips = wonChips[ai.getIndex()];
		update.enemyWonChips = wonChips[otherIndex];
		update.ownChips = chips[ai.getIndex()];
		update.enemyChips = chips[otherIndex];
		return update;
	}
	
	@Override
	public void clearChanges(Ai ai) {
	}
	
	@Override
	public void applyChanges(GrokerResponse response, Ai ai) {
		if (response.chips < 1) {
			ai.getObject().loose("Die KI hat weniger als 1 Chip gesetzt");
			return;
		}
		chips[ai.getIndex()] = response.chips;
		output[ai.getIndex()] = response.output;
	}
	
	/**
	 * Wird nur auf dem Server verwendet, bitte in der AI nicht aufrufen
	 */
	public void calculatePoints() {
		if (Math.abs(chips[0] - chips[1]) <= 5) {
			wonChips[0] += chips[0];
			wonChips[1] += chips[1];
			return;
		}
		if (chips[1] > chips[0]) {
			wonChips[0] += chips[0];
			return;
		}
		wonChips[1] += chips[1];
	}
	
	@Override
	public void applyChanges(GrokerUpdate changes) {
		wonChips[0] = changes.ownWonChips;
		wonChips[1] = changes.enemyWonChips;
		chips[0] = changes.ownChips;
		chips[1] = changes.enemyChips;
	}
	
}
