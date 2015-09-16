package main

/*
Unfertiges Zeugs:
[ ] Crashes
[ ] properties_to_dict

Um die Quali-KI zu verschnellern sind Features standartmäßig deaktiviert.
*/

import (
	"ai"
	"bufio"
	"bytes"
	"fmt"
	"io"
	"io/ioutil"
	"net"
	"os"
	"strings"
)

const redirectOutput = false
const processData = false

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
		fmt.Println(line)
		if strings.HasPrefix(line, "#") || len(line) < 3 {
			continue
		}
		kv := strings.SplitN(line, "=", 2)
		fmt.Println(kv)
		m[kv[0]] = kv[1]
		fmt.Println(kv[0] + " = " + kv[1])
	}
	return m
}

func main() {
	props := openProperties()

	if redirectOutput {
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

		// do Stuff

		fmt.Println("restoreing stdout...")
		w.Close()
		os.Stdout = stdoutOld
		out := <-outC
		fmt.Println("output:", out)

	}

	conn, err := net.Dial("tcp", props["turnierserver.worker.host"]+":"+props["turnierserver.worker.server.port"])
	check(err)

	reader := bufio.NewReader(conn)

	fmt.Fprintln(conn, props["turnierserver.worker.server.aichar"]+props["turnierserver.ai.uuid"])

	ai.Init()
	for {
		fmt.Println("warte auf Daten...")
		str, err := reader.ReadString('\n')
		fmt.Println(str)
		if err != nil {
			fmt.Println("failed to read!")
			os.Exit(1)
		}

		if processData {
			// FIXME: was mit den Daten anfangen
		}

		e := ai.Einsatz()

		fmt.Println("schreibe", fmt.Sprintf("%v:", e))
		_, err = fmt.Fprintf(conn, "%v:", e)
		check(err)
	}
}
