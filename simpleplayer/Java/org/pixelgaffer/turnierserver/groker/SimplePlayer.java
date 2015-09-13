/*
 * SimplePlayer.java
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

import org.pixelgaffer.turnierserver.groker.ai.*;

public class SimplePlayer extends GrokerAi {
	
	public SimplePlayer(String[] args) {
		super(args);
	}
	
	@Override
	public int einsatz(AiDaten du, AiDaten gegner) {
		return 5;
	}
	
	public static void main(String[] args) {
		new SimplePlayer(args).start();
	}
	
}
