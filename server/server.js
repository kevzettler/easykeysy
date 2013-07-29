var express = require('express');
var app = express();

app.use(express.bodyParser());

app.post('/', function(req, res){
  console.log(req.body);
  res.setHeader('Content-Type', 'application/json');
  res.end('cool');
});

app.listen(8080);
console.log("app listening on ", 8080);