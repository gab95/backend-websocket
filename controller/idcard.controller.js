const WebSocket = require("ws");

// WebSocket server logic
const wss = new WebSocket.Server({ noServer: true });

wss.on("connection", (ws) => {
  console.log("WebSocket client connected");
});

const sendIdCard = (req, res) => {
  const { idCard } = req.body;
  
  wss.clients.forEach((client) => {
    client.send(idCard);
  });
  res.status(200).json({
    ok: true,
    idCard,
  });
};

module.exports = {
  sendIdCard,
  wss, // Export the WebSocket server instance if needed
};
