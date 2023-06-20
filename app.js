const express = require("express");
const bodyParser = require("body-parser");

const app = express();

const PORT = process.env.PORT || 3000;

// to handle body in request
app.use(bodyParser.urlencoded({ extended: true }));
app.use(bodyParser.json());

// import routes
const idCardRoutes = require("./routes/idcard.routes");

app.use("/api/idcard", idCardRoutes);

const server = app.listen(PORT, () => {
  console.log("Server listening on port", PORT);
});

module.exports = server;
