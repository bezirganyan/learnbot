# learnbot - (mongoDB based)
A chatbot system that will help in university managment
Note: This branch is using mongodb as a database. The master branch is using C++ data structures (Trees and hash tables, and mostly does everything in memory. Thus, it is faster, but RAM hungry :))

## Description
This is a smart and intuitive assistant which is aimed to help to both the students and instructors. With the help of short commands users can do several complex operation, such as creating a course, adding students, adding homework, grading homework, getting grades, reminders, etc... 
Currentlty the learnbot is aimed for American University of Armenia (AUA), thus it may be uncomfortable to use in other institutions. Nevertheless, we are ready to collaborate with people who will try to adapt learnbot for their organizations as well.

1. Create new Slack workspace.
2. Create new bot and obtain its token (more on that https://api.slack.com/bot-users)
3. Install appropriate mongodb client for your OS, along with nodjs and npm.
4. Clone repository from github.
5. `cd` to the local repo.
6. Change to the mongodb branch: `git checkout learnbot-mongodb`
7. Install needed dependencies: `npm install`
8. Run mongodb process and leave it running
9. Start the bot `token=[YOUR_SLACK_TOKEN] node (or nodejs) bot.js`

If you did everything correctly, now your bot should be up and running on your Slack workspace.

## Functionality
### Commands

The following commands are currently in the stage of development. This means that they are unstable, as corner cases are not completely handled and, thus, may cause crashes. If you have noticed such bug, please feel free to open an issue.

`hello`, `hi`: Greetings :). Also, initializes user in the database, if he is not already there.
`who am i`, `whoami` : Returns your information
`who are you`, `what is your name` : Return information about the bot
`set privilege for [username] to [admin, instructor, student]` : Changes the role of the user (admin only)  
`create course with id [course id] with name [course name]` : Creates course with given course id and name (admin only)  
`set instructor [instructor name] for course with id [course id]` : Sets the instructor for a course (admin only) 
`register for course with id [course id]` : Registers student for a course (student only)  
`set assignment with name [assignment name] with deadline [deadline] for [course id]` : Assignes an assignement (instructor only)  
`set grade [grade] for assignment [assignement name] for student [student username] of course [course id]` : Grades an assignement (instructor only)  
`get grade for assignment [assignment name] of course [course id]` : Get grade of an assignment (student only)
`shutdown` : Shuts the bot down (admin only)

More commands are coming...

## Authors

Grigor Bezirganyan,
Tigran Sedrakayan,
Hovhannes Margaryan,
Nana Sahakyan,
