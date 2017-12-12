var Botkit = require('botkit');
var MongoClient = require('mongodb').MongoClient;
var ObjectId = require('mongodb').ObjectID;

if (!process.env.token) {
    console.log('Error: Specify token in environment');
    process.exit(1);
}

var controller = Botkit.slackbot({
    debug: true,
    clientId: process.env.clientId,
    clientSecret: process.env.clientSecret,
    scopes: ['bot'],
});

var bot = controller.spawn({
    token: process.env.token,
}).startRTM();

var url = "mongodb://localhost:27017/mydb";

// WARNING: A very complicated code follows. Be careful not to lose your sanity trying to understand it! :D


MongoClient.connect(url, function(err, db) {
    if (err) throw err;
    //db.collection("users").drop();
    //db.collection("courses").drop();
    db.createCollection("users", function(err, res) {
        if (err) throw err;
        console.log("Collection users created!");
        db.close();
    });
    db.createCollection("courses", function(err, res) {
        if (err) throw err;
        console.log("Collection courses created!");
        db.close();
    });
});

MongoClient.connect(url, function(err, db) {
    if (err) throw err;
    bot.api.users.list({}, function(err, list) {
        if (err) throw err;
        list.members.map((user) => {
            db.collection('users').findOne({ slack_id: user.id }, function(err, exists) {
                if (err) throw err
                if (exists) {
                    console.log("user exists")
                } else {
                    if (!user.is_bot) {
                        db.collection('users').insertOne({
                            'slack_id': user.id,
                            'first_name': user.profile.first_name,
                            'last_name': user.profile.last_name,
                            'email': user.profile.email,
                            'type': user.is_admin ? 'admin' : 'user',
                            'username': user.name
                        })
                    } else {
                        console.log('user is bot')
                    }
                }
            })
        })
    })
})

MongoClient.connect(url, function(err, db) {
    if (err) throw err;
    db.collection("users").find({}).toArray(function(err, result) {
        if (err) throw err;
        result.map((user) => console.log(user));
        db.close();
    })
    db.collection("courses").find({}).toArray(function(err, result) {
        if (err) throw err;
        result.map((course) => console.log(course))
        db.close();
    })
});


// For future use

// TODO: Divide into modules, for better readablity
// TODO: Add emojis :D
// TODO: Add slash commands and user tag recognition
// TODO: Add 'wazzup' command
// TODO: Add 'help' command
// TODO: Add 'list courses' command
// TODO: Add notification on new event (grade, assignment, exam, etc.)

controller.hears(['hello', 'hi'], 'direct_message,direct_mention,mention', function(bot, message) {
    var currentUser;
    bot.api.users.info({ user: message.user }, function(err, response) {
        if (err) {
            throw err;
        }
        currentUser = response.user;
        MongoClient.connect(url, function(err, db) {
            if (err) {
                throw err;
            }
            db.collection('users').findOne({ slack_id: currentUser.id }, function(err, exists) {
                if (exists) {
                    bot.reply(message, 'Hello, ' + currentUser.name + '!');
                } else {
                    if (!currentUser.is_bot) {
                        db.collection('users').insertOne({
                            'slack_id': currentUser.id,
                            'first_name': currentUser.profile.first_name,
                            'last_name': currentUser.profile.last_name,
                            'email': currentUser.profile.email,
                            'type': currentUser.is_admin ? 'admin' : 'user',
                            'username': currentUser.name
                        }, function(err, response) {
                            if (err) {
                                throw err;
                            } else {
                                bot.reply(message, 'Hi, ' + currentUser.name + '! You were successfully added to the database!');
                            }
                        })
                    } else {
                        console.log('user is bot')
                    }
                }
                db.close()
            })
        })
    });


    bot.api.reactions.add({
        timestamp: message.ts,
        channel: message.channel,
        name: 'robot_face',
    }, function(err, res) {
        if (err) {
            bot.botkit.log('Failed to add emoji reaction :(', err);
        }
    });
})

controller.hears(['who are you', 'what is your name'], 'direct_message,direct_mention,mention', function(bot, message) {
    bot.reply(message, ':robot_face: I am a bot named <@' + bot.identity.name + '>. I will be helping you with your studies.');
});

controller.hears(['who am i', 'whoami'], 'direct_message,direct_mention,mention', function(bot, message) {
    bot.reply(message, 'You are the best! ^^')
    MongoClient.connect(url, function(err, db) {
        db.collection('users').findOne({ slack_id: message.user }, function(err, res) {
            if (err) throw err
            bot.reply(message, 'You are ' + res.type + ' ' + res.first_name + ' ' + res.last_name + '. Your username is ' + res.username + ' and your email is ' + res.email)
        })
    })
})

controller.hears(['set privilege for (.*) to (.*)'], 'direct_message,direct_mention,mention', function(bot, message) {
    MongoClient.connect(url, function(err, db) {
        if (err) throw err
        db.collection('users').findOne({ slack_id: message.user }, function(err, user) {
            if (err) {
                throw err;
            } else if (user && user.type === "admin") {
                var username = message.match[1];
                var type = message.match[2];
                console.log(type)
                if (type === "instructor" || type === "student" || type === "admin") {
                    db.collection('users').updateOne({ username: username }, { $set: { type: type } }, function(err, res) {
                        if (err) {
                            throw err;
                            bot.reply(message, 'Ooops... Something went wrong :(')
                        }
                        console.log(res)
                        if (res.result.n > 0) {
                            console.log(res);
                            bot.reply(message, 'Success! Set privilege for ' + username + ' to ' + type)
                        } else {
                            bot.reply(message, 'Cannot find specified user')
                        }
                    })
                } else {
                    bot.reply(message, "Invalid privilege type specified!")
                }
            } else {
                bot.reply(message, "Error. You are not privileged enough to do this action!")
            }
        })
    })
})

controller.hears(['create course with id (.*) with name (.*)'], 'direct_message,direct_mention,mention', function(bot, message) {
    MongoClient.connect(url, function(err, db) {
        if (err) throw err
        db.collection('users').findOne({ slack_id: message.user }, function(err, user) {
            if (err) {
                throw err;
            } else if (user.type === "admin") {
                var course_id = message.match[1];
                var course_name = message.match[2];
                db.collection('courses').findOne({ course_id: course_id }, function(err, res) {
                    if (err) throw err;
                    if (res) {
                        bot.reply(message, 'Course with given id already exists!')
                    } else {
                        db.collection('courses').insertOne({
                            'course_id': course_id,
                            'course_name': course_name
                        }, function(err, res) {
                            if (err) {
                                throw err;
                            }
                            bot.reply(message, 'Created course ' + course_id + ' - ' + course_name)
                        })
                    }

                })
            } else {
                bot.reply(message, "Error. You are not privileged enough to do this action!")
            }
        })
    })
})

controller.hears(['set instructor (.*) for course with id (.*)'], 'direct_message,direct_mention,mention', function(bot, message) {
    MongoClient.connect(url, function(err, db) {
        if (err) throw err
        db.collection('users').findOne({ slack_id: message.user }, function(err, user) {
            if (err) {
                throw err;
            } else if (user.type === "admin") {
                var instructor_name = message.match[1];
                db.collection('users').findOne({ username: instructor_name }, function(err, res) {
                    if (err) throw err;
                    else if (res) {
                        if (res.type === "instructor") {
                            var course_id = message.match[2];
                            db.collection('courses').updateOne({ course_id: course_id }, { $set: { instructor: instructor_name } }, function(err, res) {
                                if (err) throw err;
                                if (res.result.n > 0) {
                                    db.collection('users').updateOne({ username: instructor_name }, { $push: { courses: { course_id: course_id } } }, function(err, res) {
                                        if (err) throw err;
                                        else if (res) {
                                            console.log(res)
                                            bot.reply(message, 'Set ' + instructor_name + ' as instructor for ' + course_id)
                                        }
                                    })
                                } else {
                                    bot.reply(message, 'No course with specified id')
                                }
                            })
                        } else {
                            bot.reply(message, 'No instructor with specified username exists')
                        }
                    } else {
                        bot.reply(message, 'No user with specified username exists')
                    }
                })
            } else {
                bot.reply(message, "Error. You are not privileged enough to do this action!")
            }
        })
    })
})

controller.hears(['register for course with id (.*)'], 'direct_message,direct_mention,mention', function(bot, message) {
    MongoClient.connect(url, function(err, db) {
        if (err) throw err
        db.collection('users').findOne({ slack_id: message.user }, function(err, user) {
            if (err) throw err;
            else if (user && (user.type === 'student')) {
                var course_id = message.match[1];
                db.collection('courses').findOne({ course_id: course_id }, function(err, res) {
                    if (err) throw err;
                    if (res) {
                        console.log(res)
                        if (res.students) {
                            if (res.students.indexOf(user.slack_id) !== -1) {
                                bot.reply(message, 'You are already registered!')
                            }
                        } else {
                            db.collection('courses').updateOne({ course_id: course_id }, { $push: { students: user.slack_id } }, function(err, res) {
                                if (err) throw err;
                                else {
                                    db.collection('users').updateOne({ slack_id: user.slack_id }, {
                                        $push: {
                                            courses: {
                                                course_id: course_id,
                                                assignments: []
                                            }
                                        }
                                    }, function(err, res) {
                                        if (err) throw err;
                                        else {
                                            bot.reply(message, 'Registered you for course ' + course_id + '. Welcome!')
                                        }
                                    })
                                }
                            })
                        }
                    } else {
                        bot.reply(message, 'No such course')
                    }
                })
            } else {
                bot.reply(message, "Sorry, only students can register for courses! If you are an instructor, ask admin to set you for course.")
            }
        })
    })
})

controller.hears(['set assignment with name (.*) with deadline (.*) for (.*)'], 'direct_message,direct_mention,mention', function(bot, message) {
    var assignment_name = message.match[1];
    var deadline = message.match[2];
    var course_id = message.match[3];

    MongoClient.connect(url, function(err, db) {
        if (err) throw err;
        db.collection('users').findOne({ slack_id: message.user }, function(err, user) {
            if (err) throw err;
            else if ((user.type === "instructor") && findCourseById(user.courses, course_id) !== -1) {
                db.collection('courses').updateOne({ course_id: course_id }, {
                    $push: {
                        assignments: {
                            'name': assignment_name,
                            'deadline': deadline
                        }
                    }
                }, function(err, res) {
                    if (err) throw err;
                    else {
                        bot.reply(message, 'Added assignment ' + assignment_name + ' for ' + course_id + ' with deadline ' + deadline)
                        db.collection('courses').findOne({ course_id: course_id }, function(err, course) {
                            if (err) throw err;
                            else if (course) {
                                course.students.map(student => {
                                    message.user = student;
                                    bot.say({
                                        text: "Hey! You just got an assignment " + assignment_name + " from " + course.course_name + " due " + deadline,
                                        channel: student
                                    })
                                })
                            }
                        })
                    }
                })
            } else {
                bot.reply(message, "You can't complete this action unless you are instructor (make sure you are registered in this course)")
            }

        })
    })
})

controller.hears(['set grade (.*) for assignment (.*) for student (.*) of course (.*)'], 'direct_message,direct_mention,mention', function(bot, message) {
    var grade = message.match[1];
    var assignment_name = message.match[2];
    var student_username = message.match[3];
    var course_id = message.match[4];

    MongoClient.connect(url, function(err, db) {
        if (err) throw err;
        db.collection('users').findOne({ slack_id: message.user }, function(err, user) {
            console.log(user.courses, course_id, findCourseById(user.courses, course_id))
            if (err) throw err;
            else if ((user.type === "instructor") && findCourseById(user.courses, course_id) !== -1) {
                db.collection('users').findOne({ username: student_username }, function(err, res) {
                    console.log(res)
                    if (err) throw err;
                    else if (res && (res.type === "student")) {
                        console.log('here')
                        db.collection('users').updateOne({ slack_id: res.slack_id, 'courses.course_id': course_id }, {
                            $push: {
                                'courses.$.assignments': {
                                    'assignment_name': assignment_name,
                                    'grade': grade
                                }
                            }
                        }, function(err, res) {
                            if (err) throw err
                            else {
                                bot.reply(message, 'Set grade for assignment ' + assignment_name + ' for student ' + student_username + ' of course ' + course_id)
                                db.collection('courses').findOne({ course_id: course_id }, function(err, course) {
                                    if (err) throw err;
                                    else if (course) {
                                        console.log(message)
                                        course.students.map(student => {
                                            message.user = student;
                                            console.log(student)
                                            bot.say({
                                                text: "Hey! You just got your grade for assignment " + assignment_name + " of " + course.course_name + '. It is ' + grade,
                                                channel: student
                                            })
                                        })
                                    }
                                })
                            }
                        })
                    } else {
                        bot.reply(message, "Could not find student with specified username")
                    }
                })
            } else {
                bot.reply(message, "You can't complete this action unless you are instructor (make sure you are registered in this course)")
            }
        })
    })
})

controller.hears(['get grade for assignment (.*) of course (.*)'], 'direct_message,direct_mention,mention', function(bot, message) {
    var assignment_name = message.match[1];
    var course_id = message.match[2];

    MongoClient.connect(url, function(err, db) {
        if (err) throw err;
        db.collection('users').findOne({ slack_id: message.user }, function(err, user) {
            if (err) throw err;
            else if ((user.type === "student") && findCourseById(user.courses, course_id) !== -1) {
                db.collection('users').findOne({ slack_id: user.slack_id, 'courses.course_id': course_id }, function(err, res) {
                    if (err) throw err;
                    else if (res) {
                        res.courses.filter((course) => course.course_id === course_id && (course.assignments.map(((assignment) => assignment.assignment_name === assignment_name && bot.reply(message, assignment.grade)))))
                    }
                })
            } else {
                bot.reply(message, "You are not registered in this course")
            }
        })
    })
})

controller.hears(['shutdown'], 'direct_message,direct_mention,mention', function(bot, message) {

    MongoClient.connect(url, function(err, db) {
        if (err) throw err;
        db.collection('users').findOne({ slack_id: message.user }, function(err, user) {
            if (user.type === "admin") {
                bot.startConversation(message, function(err, convo) {
                    convo.ask('Are you sure you want me to shutdown?', [{
                            pattern: bot.utterances.yes,
                            callback: function(response, convo) {
                                convo.say('Bye!');
                                convo.next();
                                setTimeout(function() {
                                    process.exit();
                                }, 3000);
                            }
                        },
                        {
                            pattern: bot.utterances.no,
                            default: true,
                            callback: function(response, convo) {
                                convo.say('*Phew!*');
                                convo.next();
                            }
                        }
                    ])
                })
            } else {
                bot.reply(message, "Sorry, only my lord can shut me down :(")
            }
        })
    })
})

const findCourseById = (courses, course_id) => {
    for (var i = 0; i < courses.length; i++) {
        if (courses[i].course_id === course_id) {
            return i;
        }
    }
    return -1
}