/*
 * GrokerAi.java
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
