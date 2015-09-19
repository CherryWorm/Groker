package ai

import "fmt"

// RedirectOutput legt fest, ob Debugausgaben weitergeleited werden sollen. (ca. +0.1ms pro Schritt)
// Diese Option auf 'false' zu Setzen macht nur bei eine Quali-KI Sinn.
const RedirectOutput = false

// ProcessData legt fest, ob Informationen verarbeitet werden sollen. (ca. +0.1ms pro Schritt)
// Diese Option auf 'false' zu Setzen macht nur bei eine Quali-KI Sinn.
const ProcessData = false

// Init wird vor dem ersten Einsatz ausgeführt.
func Init() {
	fmt.Println("Hallo, Welt")
}

// Einsatz gibt den Einsatz der KI zurück
func Einsatz() int {
	fmt.Println("Setze 5")
	return 5
}

// Process verarbeitet Daten des letzten Schrittes
func Process(ownWonChips, enemyWonChips, ownChips, enemyChips int) {
	fmt.Println(ownWonChips, enemyWonChips, ownChips, enemyChips)
}
