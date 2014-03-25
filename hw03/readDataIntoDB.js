// Dependencies
var fs = require('fs');
var mongoose = require('mongoose');
var models = require('./models'),
    Actor = models.Actor,
    Movie = models.Movie;
var sem = require('semaphore')(1);
mongoose.connect('mongodb://localhost/makinbacon');

// Globals for building database
var movieList = [];
var actorList = [];
var prevActor='';
var prevMovie='';

function readLines(input, func) {
    // Parses each line of a text file and calls a function on that line, releasing the semaphore when done
    // input: fs readStream
    // func: function that processes a line of text
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


function storeLineActor (line) {
    // Parses actor lines and stores an actor to DB
    // line: string containing "actor,\tmovie"
    var splitLine = line.split(',\t');
    var actorName = splitLine[0];
    var movieName = splitLine[1];
    storeActors(actorName, movieName);
};

function storeLineMovie (line) {
    // Parses movie lines and stores a movie to DB
    // line: string containing "movie,\tactor"
    var splitLine = line.split(',\t');
    var movieName = splitLine[0];
    var actorName = splitLine[1];
    storeMovies(actorName, movieName);        
};

function storeActors (actorName, movieName){
    // Checks to see if we have switched actors, if so stores the previous actor's data
    // Also builds each actor's movie list
    // actorName: actor of the current line
    // movieName: movie of the current line
    if (prevActor && prevActor != actorName){
        var actor = new Actor({name:prevActor, movies:movieList});
        movieList = [];
        actor.save(function(err){
            if (err) {
                return console.log(err);
            };
        });
    };
    prevActor = actorName;

    if (movieList.indexOf(movieName)==-1){
        movieList.push(movieName)
    };
};

function storeMovies (actorName, movieName){
    // Checks to see if we have switched movies, if so stores the previous movie's data
    // Also builds each movie's actor list
    // movieName: movie of the current line
    // actorName: actor of the current line
    if (prevMovie && prevMovie != movieName){
        var movie = new Movie({name:prevMovie, actors:actorList});
        actorList = [];
        movie.save(function(err){
            if (err) {
                return console.log(err);
            };
        });
    };
    prevMovie = movieName;

    if (actorList.indexOf(actorName)==-1){
        actorList.push(actorName)
    };
};


// Parse the list of all actors then all movies into the database 
// (semaphores because fs doesn't like having 2 files open)
sem.take(function(){
    var actorInput = fs.createReadStream('allActors.txt');
    readLines(actorInput, storeLineActor);
});

sem.take(function(){
    var movieInput = fs.createReadStream('allMovies.txt');
    readLines(movieInput, storeLineMovie);
});