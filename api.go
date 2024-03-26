package main

import (
	"bytes"
	"fmt"
	"io"
	"io/ioutil"
	"log"
	"net/http"
	"time"
	"unicode"

	"github.com/jacobsa/go-serial/serial"
)

func sendLetterToServer(letter string) {
	data := bytes.NewBufferString(letter)
	resp, err := http.Post("http://localhost:8080", "text/plain", data)
	if err != nil {
		log.Printf("Failed to send request: %v", err)
		return
	}
	defer resp.Body.Close()

	body, err := ioutil.ReadAll(resp.Body)
	if err == nil {
		fmt.Printf("Response from server: %s\n", string(body))
	}
}

var lastLetter string
var lastLetterSent string
var lastSendTime time.Time

// Verifica se a string contém apenas uma letra
func isLetter(s string) bool {
	if len(s) == 1 {
		return unicode.IsLetter(rune(s[0]))
	}
	return false
}

func handleRequests(w http.ResponseWriter, r *http.Request) {
	w.Header().Set("Access-Control-Allow-Origin", "*")
	w.Header().Set("Access-Control-Allow-Methods", "POST, GET, OPTIONS")
	w.Header().Set("Access-Control-Allow-Headers", "Content-Type")

	if r.Method == "OPTIONS" {
		w.WriteHeader(http.StatusOK)
		return
	}

	if r.Method == "POST" {
		body, err := ioutil.ReadAll(r.Body)
		if err != nil {
			http.Error(w, "Error reading request body", http.StatusInternalServerError)
			return
		}
		lastLetter = string(body)
	} else if r.Method == "GET" {
		fmt.Fprintln(w, lastLetter)
	} else {
		http.Error(w, "Method not allowed", http.StatusMethodNotAllowed)
	}
}

func main() {
	go func() {
		http.HandleFunc("/", handleRequests)
		fmt.Println("Server is running on port 8080...")
		log.Fatal(http.ListenAndServe(":8080", nil))
	}()

	options := serial.OpenOptions{
		PortName:        "COM2",
		BaudRate:        9600,
		DataBits:        8,
		StopBits:        1,
		MinimumReadSize: 4,
	}

	port, err := serial.Open(options)
	if err != nil {
		log.Fatalf("serial.Open: %v", err)
	}
	defer port.Close()

	lastSendTime = time.Now()
	buf := make([]byte, 128)
	for {
		n, err := port.Read(buf)
		if err != nil {
			if err != io.EOF {
				log.Fatalf("port.Read: %v", err)
			}
		}
		if n > 0 {
			data := string(buf[:n])
			fmt.Print(data)
			// Envia a letra (ou não-letra) assim que for lida, sem verificar se é igual à última ou o delay
			sendLetterToServer(data)
			lastLetterSent = data     // Atualiza a última letra enviada
			lastSendTime = time.Now() // Atualiza o tempo da última transmissão (opcional, se você decidir usar depois)
		}
		time.Sleep(100 * time.Millisecond) // Ajuste conforme necessário para controlar a taxa de leitura
	}
}
