var Botkit = require('botkit');
var Noodle = require('noodlejs');
var ddg = require('ddg');

var controller = Botkit.slackbot ({
	debug: false
});

options = {
	"useragent": "let's learn",
	"no_redirects": "1",
	"no_html": "0",
};

controller.spawn({
	token: process.env.token,
}).startRTM();

controller.hears('What is (.*)', ['direct_message', 'direct_mention', 'mention'],
		function(bot, message) {
			var meaning = message.match[1];
			ddg.query(meaning, options, function(err, data){
				if (data.AbstractText != '') {
					var result = data.AbstractText + '\nSource: '
						+ data.AbstractSource + '\n URL: '
						+ data.AbstractURL;
				} else {
					var r = data.RelatedTopics[0];
					var result = r.Text + '\nSource: ' + r.FirstURL;
				}
				bot.reply(message, result);
			});
			//console.log(result);
		});

controller.hears(['Hello', 'hi', 'hey'], ['direct_message', 'direct_mention', 'mention'],
		function(bot, message) {
			greetings = ['Hey, how can I help you :smiley:']
				bot.reply(message, greetings[0]);
		});

controller.hears(['Bye', 'Good bye', 'bye bye'], ['direct_message', 'direct_mention', 'mention'],
		function(bot, message) {
			greetings = ['I will miss you Master, come back soon!']
				bot.reply(message, greetings[0]);
		});

controller.hears('help', ['direct_message', 'direct_mention', 'mention'],
		function(bot, message) {
				bot.reply(message, '*+addCourse as [COURSE_NAME] with id [ID]*: addCourse(admin)'+
						'\n*+add [TYPE] as [NAME] in [COURSE] with dl [DEADLINE]*: add Homework(Instructor, TA)'+
						'\n*+addHW* : interactive mode (Instructor, TA)'+
						'\n*+grade [HW] of [STUDENT] [GRADE] from [COURSE]*: garde student (Instructor, TA)'+
						'\n*+getGrade of [HW] from [COURSE]*: gets grade (student)');
		});

var hwnames = [];
var hwdeadlines = [];
controller.hears('\\+addHW', ['direct_message', 'direct_mention', 'mention'],
		function(bot, message) {
			bot.startConversation(message, function(err, convo) {
				convo.say('Sure, let\'s start adding');
				convo.ask('What should be the name of ' + "{{vars.addType}}", function(response, convo) {
					convo.setVar('addName', response.text);
					convo.next();
				});
				convo.ask('Please specify the deadline (MM/dd/yy, hh:mm) of ' + "{{vars.addType}}", function(response, convo) {
					convo.setVar('addDeadline', response.text);
					convo.next();
				});
				convo.ask('Please specify the course in which you want to add the ' + "{{vars.addType}}", function(response, convo) {
					convo.setVar('addCourse', response.text);
				    convo.say('Successfully added {{vars.addName}} to course {{vars.addCourse}} with deadline {{vars.addDeadline}}');
					hwnames.push('{{vars.addName}}');
					hwdeadlines.push('{{vars.addDeadline}}');
					convo.next();
				});
			});
		});

controller.hears('\\+add (.*) as (.*) in (.*) with dl (.*)', ['direct_message', 'direct_mention', 'mention'],
		function(bot, message) {
			hwnames.push(message.match[2]);
			hwdeadlines.push(message.match[4]);
			bot.reply(message, 'Done! I added ' + message.match[1] + ' with name ' + message.match[2] +
					' to ' + message.match[3] + ' course, with deadline ' +  message.match[4]);
		});
var hwgrades = [];
controller.hears('\\+grade (.*) of (.*) (.*) from (.*)', ['direct_message', 'direct_mention', 'mention'],
		function(bot, message) {
			hwgrades.push(message.match[3]);
			bot.reply(message, 'Done! ' + message.match[1] + ' of ' + message.match[2] +
					' was graded ' + message.match[3]);
		});

controller.hears('\\+getGrade of (.*) from (.*)', ['direct_message', 'direct_mention', 'mention'],
		function(bot, message) {

			bot.reply(message, 'Master, your grade of ' + message.match[1] + ' is ' + hwgrades[hwnames.indexOf(message.match[1])] + '. Remeber, Grades don\'t measure your intelligence!');
		});
var courseNames = [];
var courseIDs = [];
controller.hears('\\+addCourse as (.*) with id (.*)', ['direct_message', 'direct_mention', 'mention'],
		function(bot, message) {
			courseNames.push(message.match[1]);
			courseIDs.push(message.match[2]);
			bot.reply(message, 'Master, your course ' + message.match[1] + ' with id ' + message.match[2] + ' is created!!');
		});

controller.hears('tell me a joke', ['direct_message', 'direct_mention', 'mention'],
		function(bot, message) {
			jokes = ['Physics Teacher: “Isaac Newton was sitting under a tree when an apple fell on his head and he discovered gravity. Isn’t that wonderful?”\nStudent: “Yes sir, if he had been sitting in class looking at books like us, he wouldn’t have discovered anything.”', 'Teacher asked George: “How can you prove the earth is round?” \nGeorge replied: “I can’t. Besides, I never said it was.”', 'Teacher: “This essay on your dog is, word for word, the same as your brother’s. \nStudent: Yes, sir, it is the same dog.”', 'Teacher: “Why are you late, Joseph?”\nJoseph: “Because of a sign down the road.”\nTeacher: “What does a sign have to do with you being late?”\nJoseph: “The sign said, \'School Ahead, Go Slow!\'”']
			bot.reply(message, jokes[Math.floor(Math.random() * jokes.length)]);
		});

controller.hears('\\+seehw', ['direct_message', 'direct_mention', 'mention'],
		function(bot, message) {
			bot.reply(message, 'Master, your hw for this week are: \n*Calculus 3:* line integral \n*Mecahnics:* Smart car proect part 2*\n Armenian Language and lierature:* Րաֆֆի խենթը');
		});

controller.hears('what homework do i have', ['direct_message', 'direct_mention', 'mention'],
		function(bot, message) {
			bot.reply(message, 'Master, your hws for this week are: \n*Calculus 3:* line integral \n*Mecahnics:* Smart car proect part 2\n*Armenian Language and lierature:* Րաֆֆի խենթը');
		});
//controller.setupWebserver(8888 ,function(err,webserver) {
//
//  controller.createWebhookEndpoints(controller.webserver, 'ns07Vj3IVFbPHV1vo1M2e1UY');
//
//});
//
//controller.on('slash_command',function(bot,message) {
//
//  // reply to slash command
//  bot.replyPublic(message,'Everyone can see the results of this slash command');
//
//});
