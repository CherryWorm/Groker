/*
 * AiDaten.java
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

import org.pixelgaffer.turnierserver.groker.GrokerGameState;

public class AiDaten {
	
	AiDaten(GrokerGameState state, int index) {
		vorrat = state.wallet[index];
		letzterEinsatz = state.chips[index];
		gewonneneChips = state.wonChips[index];
	}
	
	public int vorrat, letzterEinsatz, gewonneneChips;
}
