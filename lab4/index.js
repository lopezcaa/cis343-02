const fs = require('fs')
const csv = require('csv-parse')

let heroes = {};

// create a reader for csv file
const parser = csv.parse(
	{ columns: true }, 
	function(err, records){
		heroes = records;
	}
);

// read csv file as a stream
fs.createReadStream(__dirname + '/superheroes.csv').pipe(parser)

const express = require('express');
const app = express()
const port = 3000;

// server return static files from the "public" folder
app.use(express.static('public'))

app.get('/', 
	(req, res) => {
		res.send('<h1>Welcome to our awesome Superhero API!</h1>');
	}
);

app.get('/heroes',
	(req, res) => {
		res.send(heroes);
	}
);

app.get('/search/:term',
	(req, res) => {
		let selected = [];
		// printing our user request
		console.log(req.params);
		// TODO: Return a list of heros that satisfy the user request

		selected = heroes.filter(hero => {
			return (
				hero.Name.includes(term),
				hero.Identity.includes(term),
				hero.Alignment.includes(term),
				hero.EyeColor.includes(term),
				hero.HairColor.includes(term),
				hero.Gender.includes(term),
				hero.Status.includes(term),
				hero.Appearances.includes(term),
				hero.FirstAppearance.includes(term),
				hero.Year.includes(term),
				hero.Universe.includes(term)
			);
		});
		
		res.send(selected);
	}
);

app.listen(port, () => {
	console.log("I've become aware.");
});
