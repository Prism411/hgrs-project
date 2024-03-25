package main

import (
	"bytes"
	"fmt"
	"io"
	"io/ioutil"
	"log"
	"net/http"

	"github.com/jacobsa/go-serial/serial"
)

// Função para enviar a letra para o servidor (este se torna o cliente enviando para outro servidor)
func sendLetterToServer(letter string) {
	data := bytes.NewBufferString(letter)
	resp, err := http.Post("http://localhost:8080", "text/plain", data)
	if err != nil {
		log.Printf("Failed to send request: %v", err)
		return
	}
	defer resp.Body.Close()

	// Leia a resposta, se necessário
	body, err := ioutil.ReadAll(resp.Body)
	if err == nil {
		fmt.Printf("Response from server: %s\n", string(body))
	}
}

// Variável global para armazenar a última letra recebida
var lastLetter string

// Função que manipula as requisições recebidas pelo servidor, agora com suporte a CORS
// Função que manipula as requisições recebidas pelo servidor
func handleRequests(w http.ResponseWriter, r *http.Request) {
	// Configuração de cabeçalhos CORS
	w.Header().Set("Access-Control-Allow-Origin", "*")
	w.Header().Set("Access-Control-Allow-Methods", "POST, GET, OPTIONS")
	w.Header().Set("Access-Control-Allow-Headers", "Content-Type")

	// Tratamento de requisições OPTIONS
	if r.Method == "OPTIONS" {
		w.WriteHeader(http.StatusOK)
		return
	}

	// Tratamento de requisições POST
	if r.Method == "POST" {
		body, err := ioutil.ReadAll(r.Body)
		if err != nil {
			http.Error(w, "Error reading request body", http.StatusInternalServerError)
			return
		}
		lastLetter = string(body)
		fmt.Printf("Received on server: %s\n", lastLetter)
	} else if r.Method == "GET" {
		// Responde com a última letra recebida
		fmt.Fprintln(w, lastLetter)
	} else {
		// Método não suportado
		http.Error(w, "Method not allowed", http.StatusMethodNotAllowed)
	}
}

func main() {
	// Inicia o servidor em uma goroutine para que ele não bloqueie a leitura serial
	go func() {
		http.HandleFunc("/", handleRequests)
		fmt.Println("Server is running on port 8080...")
		log.Fatal(http.ListenAndServe(":8080", nil))
	}()

	// Configuração da porta serial
	options := serial.OpenOptions{
		PortName:        "COM2",
		BaudRate:        9600,
		DataBits:        8,
		StopBits:        1,
		MinimumReadSize: 4,
	}

	// Abre a porta serial
	port, err := serial.Open(options)
	if err != nil {
		log.Fatalf("serial.Open: %v", err)
	}
	defer port.Close()

	buf := make([]byte, 128)
	for {
		n, err := port.Read(buf)
		if err != nil {
			if err != io.EOF {
				log.Fatalf("port.Read: %v", err)
			}
		}
		if n > 0 {
			letter := string(buf[:n])
			fmt.Print(letter)
			// Envia a letra lida para o servidor na porta 8080
			sendLetterToServer(letter)
		}
	}
}
