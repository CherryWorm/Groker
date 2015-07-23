from wrapper import AIWrapper

class GameWrapper(AIWrapper):
	def update(self, updates):
		response = {
			"output": self.output.read(),
			"chips": self.ai.einsatz()
		}
		return response

	def process(self, d):
		if all([key in d for key in ["ownWallet", "ownWonChips", "ownChips", "enemyWallet", "enemyWonChips", "enemyChips", ]]):
			if hasattr(self.ai, "process"):
				self.ai.process(*d.values())
			else:
				print("KI verarbeitet Daten aufgrund fehlender 'process' Methode nicht.")

	def del_output(self, d):
		d.pop("output")

	def add_output(self, d, o):
		d["output"] += o

