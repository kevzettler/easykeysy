var keylogger = require(__dirname+ '/keylogger');

keylogger.on('keypress', function(v){
  console.log("We get signal?", v);
})

setInterval(function(){
  console.log(".");
}, 1000);