var Waterworx = function(db, callback){
  // Do any constructor work here
};

Waterworx.prototype = {
  init: function(db, callback){
    this.setupDb(db, function(){
      callback();
    });
  },
  
  setupDb: function(db, callback){
    var self = this;
    db.createCollection('devices', function(err, collection){
      db.collection('devices', function(err, collection){
        self.devices = collection;
        callback();
      });
    });
  },
  
  createDevice: function(){
    
  },
  
  updateDevice: function(){
    
  },
  
  checkFirmwareVersion: function(deviceOut){
    // Check for newer version of firmware than what device reports
    deviceOut.fw = 0;
  },
  
  checkForProgramUpdates: function(deviceOut){
    // Check for newer version of firmware than what device reports
    deviceOut.pg = 0;
  },
  
  serveRequest: function(req, res){
    // If the device exists update it, otherwise this is the first report and
    // we need to add it to the database.
    var devices = this.devices;
    var device = null;
    var deviceOut = {};
    var self = this;
    
    res.setHeader("Content-Type", "application/json");
    
    this.devices.findOne({did: req.query.did}, function(error, result){
      if(result === null){
        // Couldn't find the device
        devices.insert({did: req.query.did, name: req.query.name}, function(error, result){
          if(error){
            throw error;
          }
          else{
            device = result;
          }
        });
      }
      else {
        device = result;
      }
      
      if(device){   
        // Check for firmware update
        self.checkFirmwareVersion(deviceOut);
        
        // Check for program update
        self.checkForProgramUpdates(deviceOut);
        
        // Store device data in db
        if(req.body.zones)
        {
          deviceOut.zones = req.body;
        }
      }
      
      res.write(JSON.stringify(deviceOut));
      res.end();
    });
  },
  
  handleError: function(req, res, e){
    res.writeHead(500, {});
    res.write(JSON.stringify({rc:500}));
    res.end();
    console.log(e.stack.split('\n'));
  }
}; // end Waterworx.prototype

exports.Waterworx = Waterworx;
