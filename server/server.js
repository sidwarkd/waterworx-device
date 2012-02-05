var connect = require('connect'),
  mongo = require('mongodb'),
  Waterworx = require('./lib/waterworx').Waterworx;


mongo.connect(process.env.MONGOLAB_URI, {}, function(error, db){
  var waterworx = new Waterworx();

  db.addListener("error", function(error){
    console.log("Error connecting to mongo");
  });

  waterworx.init(db, function(){
    console.log("initialize db");
    connect(
      connect.favicon(),
      connect.query(),                      // populate req.query with query parameters
      connect.bodyParser(),                 // Get JSON data from body
      function(req, res, next){
        try {
          waterworx.serveRequest(req, res);
        } catch(e) {
          waterworx.handleError(req, res, e);
        }
      }
    ).listen(process.env.PORT || 56758);
  }); // end waterworx.init function
});
