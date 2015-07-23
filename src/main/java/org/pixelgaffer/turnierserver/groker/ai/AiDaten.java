package org.pixelgaffer.turnierserver.groker.ai;

import org.pixelgaffer.turnierserver.groker.GrokerGameState;

public class AiDaten {
	
	AiDaten(GrokerGameState state, int index) {
		vorrat = state.wallet[index];
		letzterEinsatz = state.chips[index];
		gewonneneChips = state.wonChips[index];
	}
	
	public int vorrat, letzterEinsatz, gewonneneChips;
}
