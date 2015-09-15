from wrapper import AIWrapper

class GameWrapper(AIWrapper):
	def update(self, updates):
		self.process(updates)
		return str(self.ai.einsatz()) + ":"

	def process(self, d):
		own, their = d.split(";")
		ownWon, ownChips = own.split(":")
		enemyWon, enemyChips = enemy.split(":")
		if hasattr(self.ai, "process"):
			self.ai.process(
				ownWonChips=ownWon,
				ownChips=ownChips,
				enemyWonChips=enemyWon,
				enemyChips=enemyChips
			)
		else:
			print("KI verarbeitet Daten aufgrund fehlender 'process' Methode nicht.")

	def add_output(self, d, o):
		d += ":" + o
