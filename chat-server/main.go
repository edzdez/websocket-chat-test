package main

import (
	"github.com/gin-gonic/gin"
	"github.com/gorilla/websocket"
	"log"
	"net/http"
)

const Addr = "0.0.0.0:8080"

var wsupgrader = websocket.Upgrader{
	ReadBufferSize:  1024,
	WriteBufferSize: 1024,
}

var clients = make(map[string]websocket.Conn)

func wshandler(w http.ResponseWriter, r *http.Request) {
	user := r.Header.Get("name")
	if user == "" {
		log.Println("someone just tried to login without a username!")
		w.WriteHeader(http.StatusBadRequest)
		w.Write([]byte("no name"))

		return
	}
	if _, exists := clients[user]; exists {
		log.Println("user exists")
		w.WriteHeader(http.StatusUnauthorized)
		w.Write([]byte("user with your name already exists!"))

		return
	}

	conn, err := wsupgrader.Upgrade(w, r, nil)
	if err != nil {
		log.Println(err)
		return
	}

	log.Println(user, "just logged in!")
	clients[user] = *conn

	for {
		t, msg, err := conn.ReadMessage()
		if err != nil {
			log.Println(err)
			break
		}

		log.Printf("%s sent: %s\n", user, string(msg))
		message := user + ": " + string(msg)

		for _, client := range clients {
			if err = client.WriteMessage(t, []byte(message)); err != nil {
				log.Println(err)
				break
			}
		}
	}

	delete(clients, user)
}

func main() {
	r := gin.Default()
	err := r.SetTrustedProxies(nil)
	if err != nil {
		log.Fatal(err)
	}

	r.GET("/", func(c *gin.Context) {
		wshandler(c.Writer, c.Request)
	})

	err = r.Run(Addr)
	if err != nil {
		log.Fatal(err)
	}
}
