var MongoClient = require('mongodb').MongoClient;
//var url = "mongodb://localhost:27017/mydb";
const url = "mongodb+srv://Hussaindb:1GBSt0rage%21@cluster0.37fbw.mongodb.net/Cluster0?retryWrites=true&w=majority";
const fs = require('fs')

//create db and enter values from Smoke.txt
MongoClient.connect(url, function(err, db) {
    if (err) throw err;
    var dbo = db.db("skill26db");
    var myobj = [];
    fs.readFile('./Smoke.txt', (err, data) => { 
        if (err) throw err; 
        var lines = data.toString().split(/\r?\n/);
        lines.map(function(item){
            var tabs = item.split('\t');   
            if (tabs[0] === 'Time') return;
            myobj.push({time: tabs[0], id: parseInt(tabs[1]), smoke: parseInt(tabs[2]), temp: parseInt(tabs[3])})
            console.log({time: tabs[0], id: tabs[1], smoke: tabs[2], temp: tabs[3]})
        });
        dbo.collection("Smoke").insertMany(myobj, function(err, res) {
            if (err) throw err;
            console.log("Number of documents inserted: " + res.insertedCount);
            db.close();
        });
    });
  });

