

const express = require("express");
const bodyParser = require("body-parser");

const app = express();

// to handle body in request
app.use(bodyParser.urlencoded({ extended: true }));
app.use(bodyParser.json());

// import routes
const idCardRoutes = require("./routes/idcard.routes");

app.use("/api/idcard", idCardRoutes);

const server = app.listen(3000, () => {
  console.log("Server listening on port 3000");
});

module.exports = server;
