const server = require('./app');

// create an HTTP server and upgrade it to WebSocket
server.on('upgrade', (request, socket, head) => {
  const { wss } = require('./controller/idcard.controller');
  wss.handleUpgrade(request, socket, head, (ws) => {
    wss.emit('connection', ws, request);
  });
});
