from wrapper import AIWrapper

class GameWrapper(AIWrapper):
	def update(self, updates):
		self.process(updates)
		return str(self.ai.einsatz())

	def process(self, d):
		own, enemy = d.split(";")
		ownWon, ownChips = own.split(":")
		enemyWon, enemyChips = enemy.split(":")
		if hasattr(self.ai, "process"):
			self.ai.process(
				ownWonChips=int(ownWon),
				ownChips=int(ownChips),
				enemyWonChips=int(enemyWon),
				enemyChips=int(enemyChips)
			)
		else:
			print("KI verarbeitet Daten aufgrund fehlender 'process' Methode nicht.")
