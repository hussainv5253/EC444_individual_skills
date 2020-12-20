var MongoClient = require('mongodb').MongoClient;
//var url = "mongodb://localhost:27017/mydb";
const url = "mongodb+srv://Hussaindb:1GBSt0rage%21@cluster0.37fbw.mongodb.net/Cluster0?retryWrites=true&w=majority";
const fs = require('fs')


//Find Sensors where the id is "1":
MongoClient.connect(url, function(err, db) {
  if (err) throw err;
  var dbo = db.db("skill26db");
  var query = { id: 1 };
  dbo.collection("Smoke").find(query, { projection: { _id: 0, time: 0} }).toArray(function(err, result) {
    if (err) throw err;
    console.log(result);
    db.close();
  });
});
