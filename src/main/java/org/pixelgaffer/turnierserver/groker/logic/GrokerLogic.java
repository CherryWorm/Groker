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

}
