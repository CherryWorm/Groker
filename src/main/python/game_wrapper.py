from wrapper import AIWrapper

class GameWrapper(AIWrapper):
	def update(self, updates):
		self.process(updates)
		response = {
			"output": self.output.read(),
			"chips": self.ai.einsatz()
		}
		return response

	def process(self, d):
		if all([key in d for key in ["ownWonChips", "ownChips", "enemyWonChips", "enemyChips"]]):
			if hasattr(self.ai, "process"):
				self.ai.process(
					ownWonChips=d["ownWonChips"],
					ownChips=d["ownChips"],
					enemyWonChips=d["enemyWonChips"],
					enemyChips=d["enemyChips"]
				)
			else:
				print("KI verarbeitet Daten aufgrund fehlender 'process' Methode nicht.")

	def del_output(self, d):
		d.pop("output")

	def add_output(self, d, o):
		d["output"] += o
