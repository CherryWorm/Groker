package org.pixelgaffer.turnierserver.groker.ai;

import org.pixelgaffer.turnierserver.ailibrary.Ai;
import org.pixelgaffer.turnierserver.groker.GrokerGameState;
import org.pixelgaffer.turnierserver.groker.GrokerResponse;
import org.pixelgaffer.turnierserver.groker.GrokerUpdate;

import com.google.gson.reflect.TypeToken;

public abstract class GrokerAi extends Ai<GrokerGameState, GrokerUpdate> {
	
	private GrokerGameState gameState = new GrokerGameState();
	
	public GrokerAi(String[] args) {
		super(new TypeToken<GrokerUpdate>() {
		}, args);
	}
	
	@Override
	protected Object update(GrokerGameState state) {
		GrokerResponse response = new GrokerResponse();
		response.chips = einsatz(new AiDaten(state, 0), new AiDaten(state, 1));
		response.output = output.toString();
		clear(output);
		return response;
	}
	
	public abstract int einsatz(AiDaten du, AiDaten gegner);
	
	@Override
	protected GrokerGameState getState(GrokerUpdate change) {
		gameState.applyChanges(change);
		return gameState;
	}
	
}
