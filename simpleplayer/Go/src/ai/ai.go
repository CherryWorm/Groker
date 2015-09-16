package ai

import "fmt"

// Init wird vor dem ersten Einsatz ausgeführt.
func Init() {
	fmt.Println("INIIIIIIT")
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
