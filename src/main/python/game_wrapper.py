####################################################################################
# game_wrapper.py
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
