/*
 * GrokerLogic.java
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

import org.pixelgaffer.turnierserver.gamelogic.TurnBasedGameLogic;
import org.pixelgaffer.turnierserver.gamelogic.interfaces.Ai;
import org.pixelgaffer.turnierserver.gamelogic.interfaces.GameState;
import org.pixelgaffer.turnierserver.groker.GrokerGameState;
import org.pixelgaffer.turnierserver.groker.GrokerResponse;

import com.google.gson.reflect.TypeToken;

public class GrokerLogic extends TurnBasedGameLogic<GrokerAiObject, GrokerResponse> {

	public GrokerLogic() {
		super(new TypeToken<GrokerResponse>() {
		});
	}

	@Override
	protected Object update() {
		GrokerGameState state = (GrokerGameState) gamestate;
		state.calculatePoints();
		progress = Math.min(Math.abs(state.wonChips[0] - state.wonChips[1]) / 100.0, 1);
		display = "Momentane Differenz zwischen den beiden Ais: " + (state.wonChips[0] - state.wonChips[1]);
		sendRenderData(new GrokerRenderData(state, game.getAis().get(0).getId(), game.getAis().get(1).getId()));
		for (Ai ai : game.getAis()) {
			if(getUserObject(ai).lost)
				continue;
			getUserObject(ai).score = ((GrokerGameState) gamestate).wonChips[ai.getIndex()];
		}
		if (Math.abs(state.wonChips[0] - state.wonChips[1]) >= 100) {
			endGame("Die Differenz zwischen den gewonnenen Chips betrug 100 oder mehr");
		}
		return null;
	}

	@Override
	protected GameState<?, GrokerResponse> createGameState() {
		return new GrokerGameState();
	}

	@Override
	protected void setup() {
		for (Ai ai : game.getAis()) {
			getUserObject(ai).mikrosLeft = 2000000;
		}
		maxTurns = 200;
	}

	@Override
	public void lost(Ai ai) {
		((GrokerGameState) gamestate).wonChips[ai.getIndex()] = -1;
		getUserObject(ai).score = -1;
		endGame("Die KI " + ai.getId() + " hat verloren");
	}

	@Override
	protected GrokerAiObject createUserObject(Ai ai) {
		return new GrokerAiObject();
	}

	@Override
	protected void gameFinished() {

	}
	
	@Override
	protected void sendFirstRenderData() {
		progress = 0;
		display = "Spiel gestartet";
		sendRenderData(new GrokerRenderData(game.getAis().get(0).getId(), game.getAis().get(1).getId()));
	}

	@Override
	public int aiTimeout() {
		return 4000;
	}

}
