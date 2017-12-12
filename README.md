# learnbot - (mongoDB based)
A chatbot system that will help in university managment
Note: This branch is using mongodb as a database. The master branch is using C++ data structures (Trees and hash tables, and mostly does everything in memory. Thus, it is faster, but RAM hungry :))

## Description
This is a smart and intuitive assistant which is aimed to help to both the students and instructors. With the help of short commands users can do several complex operation, such as creating a course, adding students, adding homework, grading homework, getting grades, reminders, etc... 
Currentlty the learnbot is aimed for American University of Armenia (AUA), thus it may be uncomfortable to use in other institutins. Nevertheless, we are ready to collaborate with people who will try to adapt leanbot for their organizations as well. 
1. Create new Slack workspace.
2. Create new bot and obtain its token (more on that https://api.slack.com/bot-users)
3. Install mongodb, nodjs and npm
4. Clone repository from github.
5. `cd` to the local repo.
6. `git checkout learnbot-mongodb`
7. `npm install`
8. `mkdir data`
9. `run` mongodb process and `set --dbpath to ./data (mongod --dbpath=./data works for me)` and leave the process running
10. `token=[YOUR_TOKEN] node (or nodejs) bot.js`

If you did everything correctly, now your bot should be up on your slack workspace.

## Functionality
### Commands  
__who am i__ : returns your information  
__set privilege for \[user\] to \[admin\]__ : Changes the role of te student (must be run by admin)  
__create course with id \[course id\] with name \[course name\]__ : creates course by given course name (must be run by admin)  
__set instructor \[instructor name\] for course with id \[course id\]__ : stes instructor for a course (must be run by admin)  
__register for course with id \[course id\]__ : registers for a course (student)  
__set assignment with name \[assignment name\] with deadline \[deadline\] for \[course id\]__ : assignes an assignement (Instructor, student(TA))  
__set grade for assignment \[assignement name\] for student \[student username\] of course \[course id\]__ : grades an assignement (Instructor, student(TA))  

More commands are coming...

## Authors

Grigor Bezirganyan
Tigran Sedrakayan
Hovhannes Margaryan
Nana Sahakyan
