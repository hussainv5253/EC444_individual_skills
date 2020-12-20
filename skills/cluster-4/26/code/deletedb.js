var MongoClient = require('mongodb').MongoClient;
//var url = "mongodb://localhost:27017/mydb";
const url = "mongodb+srv://Hussaindb:1GBSt0rage%21@cluster0.37fbw.mongodb.net/Cluster0?retryWrites=true&w=majority";
const fs = require('fs')


  //Delete db
  MongoClient.connect(url, function(err, db) {
  if (err) throw err;
  var dbo = db.db("skill26db");
  dbo.collection("Smoke").drop(function(err, delOK) {
    if (err) throw err;
    if (delOK) console.log("Collection deleted");
    db.close();
  });
});