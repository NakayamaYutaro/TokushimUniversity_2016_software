# TokushimUniversity_2016_software  
This repository contains documents and sources. Used at software training 2016.

## How to Play?  
--- 
cd "working directory"/game/src
make build  
cd "working directory"/game/bin
* client side: ./game.out C "server's IP address" "Wiiremote's MAC address"
* server side: ./game.out S "a number of players" "Wiiremote's MAC address"

## directory structure  
---  
* docs
* game
	+ src
		- controllers
		- views
		- models
		- utils (library)
	+ assets
	+ bin
	
## specification
---
### architecture
This game is constructed by pushMVC architecture.  
+ M:model
	It has parameters/behaviors of each object.  
+ V:view
	It works on window. It shows information/situation to user.  
+ C:controller
	It bridges model and view. It takes information from model, and passes to view.  

### gameflow(server)  
---  
1. Get information from command line arguments.
2. Connect to Wiiremote.
3. Handshake betweeen server and client.
4. Initialize each object and views.
5. Start game.
	1. Set each roomba's position by wiiremote sensor.
	2. Simulate game's situation.
	3. Set each roomba's position by message form client.
	4. Render window.
	5. Judge game finishing.
6. End game.

### commucation
This game communicates between a server and clients.  
Two classes, ServerCommunicator/ClientCommunicator is puted in charge of network communication.  
There classes is placed under "/game/src/models".
Each side programs send strings to opposite program on main thread, and receiving on sub thread.  
And communication messages is formed by json format.  
ex. { "cmd": "D", "ID": "0", "roombas": [ {"x": 200, "y", 300}, {"x": 40, "y": 120} ] }  
+ cmd: Expresses purpose of communication.
	- H: Try handshake with opposite program.
	- S: Starts a game. 
	- D: Distributes game's situation from server to client, or client sends each roomba's position which controlled at client side. 
	- E: Ends a game.  
	
Json parsing with picjson library. (repository: https://github.com/kazuho/picojson)  
A server calculates each object's behavior, and sends game's situation to clients.  

### display objects  
---  
View components is placed under "/game/src/".  
FooWindow classes is expresses entire the window, and FooPanel classed is expresses each objects on the window.
#### view's workflow
1. There are initialized on constructor. (set image file, size and position ...etc)
2. Updates each object's position on Window.updateObjects().
3. Updates window graphic on Window.updateWindow().
