import random
import pprint

class AI:
	def einsatz(self):
		"""Diese Funkion wird jede Runde aufgerufen, und gibt die Punkte zurück, die gesetzt werden sollen."""
		einsatz = 5
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
