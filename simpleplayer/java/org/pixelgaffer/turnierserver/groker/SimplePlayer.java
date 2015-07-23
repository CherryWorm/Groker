package org.pixelgaffer.turnierserver.groker;

public class SimplePlayer extends GrokerAi {
	
	public SimplePlayer(String[] args) {
		super(args);
	}
	
	@Override
	public int einsatz(AiDaten du, AiDaten gegner) {
		return 5;
	}
	
	public static void main(String[] args) {
		new SimplePlayer(args).start();
	}
	
}
