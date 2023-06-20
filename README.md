# Backend with Websockets

This is an API to read a RFID card with an Arduino NodeMCU board

## Routes
* /api/routes

## Technologies
* Nodejs
* Websockets

## How to Install
1. Connect the NodeMCU board and the RFID-RC522 reader as the following video:
[![nodeMCU V3 + RFID-RC522](https://youtu.be/sRgosRd32eA?t=141)](https://youtu.be/sRgosRd32eA?t=141).
2. Upload the rfid-nodemcu.ino file to the NodeMCU board
2. Clone the repository.
3. Run ```npm install --save``` command to install the node_modules
4. Run ```npm install nodemon wscat -g```  to globally install nodemon and wscat to test the websocket connection
* (you can run ```npm install nodemon wscat --save``` to install it locally)
6. Run  ```npm run dev``` command to start the project

