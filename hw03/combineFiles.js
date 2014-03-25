// Author: Josh Langowitz
// SofSys S2014 HW3
// Quick script to combine two text files into 1.
// Redirect the output of this to the text file you want.


var fs = require('fs');
var sem = require('semaphore')(1);

function readLines(input, func) {
    var remaining = '';

    input.on('data', function(data) {
        remaining += data;
        var index = remaining.indexOf('\n');
        while (index > -1) {
            var line = remaining.substring(0, index);
            remaining = remaining.substring(index + 1);
            func(line);
            index = remaining.indexOf('\n');
    };
  });

    input.on('end', function() {
        if (remaining.length>0){
            func(remaining);
        };
        sem.leave();
    });
}

function printLine(line){
    console.log(line);
}
file1='actormovies.txt'
file2='actressmovies.txt'

sem.take(function(){
    var maleInput = fs.createReadStream(file1);
    readLines(maleInput, printLine);
});

sem.take(function(){
    var femaleInput = fs.createReadStream(file2);
    readLines(femaleInput, printLine);
});
