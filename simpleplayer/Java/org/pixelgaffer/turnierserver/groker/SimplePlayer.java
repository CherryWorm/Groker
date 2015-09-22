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

	//Dies ist der Konstruktor. Bitte modifiziere diesen nicht!
	public SimplePlayer(String[] args) {
		super(args);
	}

	//Dies hier ist für dich die wichtigste Methode. Gebe einfach zurück, wieviel du setzen willst.
	//Die Klasse AiDaten enthält die Felder letzterEinsatz und gewonneneChips.
	@Override
	public int einsatz(AiDaten du, AiDaten gegner) {
		return 5;
	}

	//Dies hier ist die main-Methode. Du kannst sie so lassen wie sie ist und unser Networking-zeugs verwenden, du kannst deine KI aber auch
	//komplett selbst schreiben. Hierbei kannst du Ai.java in unserem GitHub-Repository als Vorbild nehmen. Falls du Verbesserungsvprschläge hast,
	//bitten wir dich, einen pull-request zu erstellen-
	public static void main(String[] args) {
		new SimplePlayer(args).start();
	}

}
