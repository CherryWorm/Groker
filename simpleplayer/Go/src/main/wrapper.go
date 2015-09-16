package main

// [ ] Crashes
// [ ] properties_to_dict

import (
	"ai"
	"bufio"
	"bytes"
	"fmt"
	"io"
	"net"
	"os"
)

func main() {

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

	conn, err := net.Dial("tcp", "127.0.0.1:1234")
	if err != nil {
		fmt.Println(err)
		os.Exit(1)
	}

	reader := bufio.NewReader(conn)
	writer := bufio.NewWriter(conn)

	writer.WriteString("A")

	ai.Init()
	for {
		str, err := reader.ReadString('\n')
		fmt.Println(str)
		if err != nil {
			fmt.Println("failed to read!")
			os.Exit(1)
		}

		e := ai.Einsatz()

		writer.WriteString(fmt.Sprintf("%v:", e))
	}
}
