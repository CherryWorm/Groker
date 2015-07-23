package org.pixelgaffer.turnierserver.groker;

import org.pixelgaffer.turnierserver.gamelogic.interfaces.Ai;
import org.pixelgaffer.turnierserver.gamelogic.interfaces.GameState;

public class GrokerGameState implements GameState<GrokerUpdate, GrokerResponse> {
	
	public static final int WALLET_SIZE = -1;
	
	public int[] wallet, wonChips;
	public int[] chips;
	public String[] output;
	
	public GrokerGameState() {
		wallet = new int[2];
		wallet[0] = WALLET_SIZE;
		wallet[1] = WALLET_SIZE;
		wonChips = new int[2];
		chips = new int[2];
		output = new String[2];
	}
	
	@Override
	public GrokerUpdate getChanges(Ai ai) {
		int otherIndex = ai.getIndex() == 0 ? 1 : 0;
		GrokerUpdate update = new GrokerUpdate();
		update.ownWallet = wallet[ai.getIndex()];
		update.enemyWallet = wallet[otherIndex];
		update.ownWonChips = wonChips[ai.getIndex()];
		update.enemyWonChips = wonChips[otherIndex];
		update.ownChips = chips[ai.getIndex()];
		update.enemyChips = chips[otherIndex];
		return update;
	}
	
	@Override
	public void clearChanges(Ai ai) {
	}
	
	@Override
	public void applyChanges(GrokerResponse response, Ai ai) {
		if ((response.chips < 1 || response.chips > wallet[ai.getIndex()]) && wallet[ai.getIndex()] != -1) {
			ai.getObject().loose("Die KI hat mehr gesetzt als sie durfte");
			return;
		}
		if (wallet[ai.getIndex()] != -1) {
			wallet[ai.getIndex()] -= response.chips;
		}
		chips[ai.getIndex()] = response.chips;
	}
	
	/**
	 * Wird nur auf dem Server verwendet, bitte in der AI nicht aufrufen
	 */
	public void calculatePoints() {
		if (Math.abs(chips[0] - chips[1]) <= 5) {
			wonChips[0] += chips[0];
			wonChips[1] += chips[1];
			return;
		}
		if (chips[1] > chips[0]) {
			wonChips[0] += chips[0];
			return;
		}
		wonChips[1] += chips[1];
	}
	
	@Override
	public void applyChanges(GrokerUpdate changes) {
		wallet[0] = changes.ownWallet;
		wallet[1] = changes.enemyWallet;
		wonChips[0] = changes.ownWonChips;
		wonChips[1] = changes.enemyWonChips;
		chips[0] = changes.ownChips;
		chips[1] = changes.enemyChips;
	}
	
}
