// cloud.js
// Code for controlling LED connected to RPi board via Cloud
var express = require('express');
var app = express();
var piREST = require('pi-arest')(app);

piREST.set_id('rpi_led');
piREST.set_name('pi_cloud');
piREST.set_mode('bcm');

// Connect to cloud.aREST.io
piREST.connect();

// Start server
var server = app.listen(80, function() {
    console.log('Listening on port %d',server.address().port);
});

