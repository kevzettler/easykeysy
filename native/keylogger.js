var keylogger = require('./build/Release/keylogger').Emitter,
    util = require('util'),
    events = require('events');

util.inherits(new keylogger, events.EventEmitter);
exports = keylogger;