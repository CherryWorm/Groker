import random

class AI:
	def einsatz(self):
		einsatz = random.randrange(1, 6)
		print("setze:", einsatz)
		return einsatz
