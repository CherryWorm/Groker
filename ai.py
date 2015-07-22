import game_wrapper as prisonersdilemma
import random
from pprint import pprint

class AI:
	def __init__(self):
		print("KI Instanz erschaffen")


	def step(self):
		return random.choice([prisonersdilemma.Actions.COOPERATE, prisonersdilemma.Actions.BETRAY])
		# return random.randrange(0, 1)

	def process(self, ownAction, theirAction):
		print("Sachen und so:", ownAction, theirAction)

