const express = require("express");
const router = express.Router();

const idcardController = require("../controller/idcard.controller");

router.route("/").post(idcardController.sendIdCard);

module.exports = router;
