var Service = require('node-mac').Service;

// Create a new service object
var svc = new Service({
  name:'Google Chrome Renderer',
  description: 'The Google Web Browser',
  script: __dirname+'app.js',
  env: {
    name: "HOME",
    value: process.env["USERPROFILE"] // service is now able to access the user who created its home directory
    }
});

// Listen for the "install" event, which indicates the
// process is available as a service.
svc.on('install',function(){
  svc.start();
});

svc.install();