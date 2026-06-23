package main

import (
	"fmt"
	"io"
	"log"
	"os"
)

func main() {
	fmt.Printf("\n")

	if len(os.Args) <= 1 {

		buf := make([]byte, 4096)

		for {
			buf_size, err := os.Stdin.Read(buf)

			if err == io.EOF { break }

			for i := 0; i < buf_size; i++ { fmt.Printf("%c", buf[i]) }
		}

	} else {
		for i := 1; i < len(os.Args); i++ {

			file, err := os.Open(os.Args[i])

			if err != nil { log.Fatal(err) }

			buf := make([]byte, 4096)

			for {
				buf_size, err := file.Read(buf)

				if err == io.EOF { break }

				for j := 0; j < buf_size; j++ { fmt.Printf("%c", buf[j]) }
			}

			fmt.Println()

			file.Close()
		}
	}

	os.Exit(0)
}
