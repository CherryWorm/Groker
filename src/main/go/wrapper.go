package main

// Um die Quali-KI zu verschnellern sind Features standartmäßig deaktiviert.
// Diese Features können im 'ai'-Paket aktiviert werden.

import (
	"ai"
	"bufio"
	"bytes"
	"fmt"
	"io"
	"io/ioutil"
	"net"
	"os"
	"strconv"
	"strings"
)

func check(e error) {
	if e != nil {
		panic(e)
	}
}

func openProperties() map[string]string {
	m := make(map[string]string)
	dat, err := ioutil.ReadFile(os.Args[1])
	check(err)
	lines := strings.Split(string(dat), "\n")
	for _, line := range lines {
		if strings.HasPrefix(line, "#") || len(line) < 3 {
			continue
		}
		kv := strings.SplitN(line, "=", 2)
		m[kv[0]] = kv[1]
		fmt.Println(kv[0] + " = " + kv[1])
	}
	return m
}

func redirectOutput() (*os.File, *os.File, chan string, *os.File) {
	fmt.Println("redirecting stdout...")
	stdoutOld := os.Stdout
	r, w, _ := os.Pipe()
	os.Stdout = w

	outC := make(chan string)
	go func() {
		var buf bytes.Buffer
		io.Copy(&buf, r)
		outC <- buf.String()
	}()

	return r, w, outC, stdoutOld
}

func restoreOutput(r, w *os.File, outC chan string, stdoutOld *os.File) string {

	w.Close()
	os.Stdout = stdoutOld
	out := <-outC
	fmt.Println("Output restored:", out)
	return out
}

func recoverSend(conn net.Conn) {
	if r := recover(); r != nil {
		fmt.Println("Recovering", r)
		data := "CRASH " + fmt.Sprintf("%v", r)
		fmt.Println("sending", data)
		conn.Write([]byte(data))
	}
}

func main() {
	props := openProperties()

	conn, err := net.Dial("tcp", props["turnierserver.worker.host"]+":"+props["turnierserver.worker.server.port"])
	check(err)
	defer recoverSend(conn)

	reader := bufio.NewReader(conn)

	fmt.Fprintln(conn, props["turnierserver.worker.server.aichar"]+props["turnierserver.ai.uuid"])

	var output string

	if ai.RedirectOutput {
		r, w, outC, stdoutOld := redirectOutput()
		ai.Init()
		output += restoreOutput(r, w, outC, stdoutOld)
	} else {
		ai.Init()
	}

	for {
		fmt.Println("warte auf Daten...")
		str, err := reader.ReadString('\n')
		fmt.Println(str)
		if err != nil {
			fmt.Println("failed to read!")
			os.Exit(1)
		}

		if ai.ProcessData {
			// TODO: strings.TrimRight, strings.Split performance
			split := strings.Split(strings.TrimRight(str, "\n"), ";")
			ownWonChips, err := strconv.Atoi(strings.Split(split[0], ":")[0])
			check(err)
			ownChips, err := strconv.Atoi(strings.Split(split[0], ":")[1])
			check(err)
			enemyWonChips, err := strconv.Atoi(strings.Split(split[1], ":")[0])
			check(err)
			enemyChips, err := strconv.Atoi(strings.Split(split[1], ":")[1])
			check(err)
			if ai.RedirectOutput {
				r, w, outC, stdoutOld := redirectOutput()
				ai.Process(ownWonChips, enemyWonChips, ownChips, enemyChips)
				output += restoreOutput(r, w, outC, stdoutOld)
			} else {
				ai.Process(ownWonChips, enemyWonChips, ownChips, enemyChips)
			}
		}

		var einsatz int
		if ai.RedirectOutput {
			r, w, outC, stdoutOld := redirectOutput()
			einsatz = ai.Einsatz()
			output += restoreOutput(r, w, outC, stdoutOld)

			output = strings.Replace(output, "\\", "\\\\", -1)
			output = strings.Replace(output, "\n", "\\n", -1)
		} else {
			einsatz = ai.Einsatz()
		}

		data := strconv.Itoa(einsatz) + ":" + output + "\n"
		output = ""

		fmt.Println("schreibe", data)
		written, err := conn.Write([]byte(data))
		check(err)
		fmt.Println("wrote", written, "bytes")
	}
}
