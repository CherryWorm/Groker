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
		progress = Math.abs(state.wonChips[0] - state.wonChips[1]) / 100.0;
		display = "Momentane Differenz zwischen den beiden Ais: " + (state.wonChips[0] - state.wonChips[1]);
		sendRenderData(new GrokerRenderData(state, game.getAis().get(0).getId(), game.getAis().get(1).getId()));
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
			getUserObject(ai).millisLeft = 1000;
		}
	}
	
	@Override
	public void lost(Ai ai) {
		super.lost(ai);
		((GrokerGameState) gamestate).wonChips[ai.getIndex()] = -1;
		endGame("Die KI " + ai.getId() + " hat verloren");
	}
	
	@Override
	protected GrokerAiObject createUserObject(Ai ai) {
		return new GrokerAiObject();
	}
	
	@Override
	protected void gameFinished() {
		for (Ai ai : game.getAis()) {
			getUserObject(ai).score = ((GrokerGameState) gamestate).wonChips[ai.getIndex()];
		}
	}
	
}
