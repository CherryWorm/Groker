####################################################################################
# ai.py
#
# Copyright (C) 2015 Pixelgaffer
#
# This work is free software; you can redistribute it and/or modify it
# under the terms of the GNU Lesser General Public License as published by the
# Free Software Foundation; either version 2 of the License, or any later
# version.
#
# This work is distributed in the hope that it will be useful, but without
# any warranty; without even the implied warranty of merchantability or
# fitness for a particular purpose. See version 2 and version 3 of the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
####################################################################################
import random
import pprint

class AI:
	def einsatz(self):
		"""Diese Funkion wird jede Runde aufgerufen, und gibt die Punkte zurück, die gesetzt werden sollen."""
		einsatz = random.randrange(1, 6)
		print("setze:", einsatz)
		return einsatz

	def process(self, ownWonChips, enemyWonChips, ownChips, enemyChips):
		"""Diese Funkion wird nach jedem Schritt aufgerufen und ist dafür da, Daten zu verarbeiten.
		Es werden ownWonChips   (gesammten Chips, die die eigene KI bekommen hat),
		          enemyWonChips (gesammten Chips, die der gegner bekommen hat),
		          ownChips      (Chips, die man diese Runde gesetzt hat),
		          enemyChips    (Chips, die der Gegner diese Runde gesetzt hat) übergeben."""
		pprint.pprint({
			"ownWonChips": ownWonChips,
			"enemyWonChips": enemyWonChips,
			"ownChips": ownChips,
			"enemyChips": enemyChips
		})
