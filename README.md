# learnbot
A chatbot system that will help in university managment

## Description
This is a smart and intuitive assistant which is aimed to help to both the students and instructors. With the help of short commands users can do several complex operation, such as creating a course, adding students, adding homework, grading homework, getting grades, reminders, etc... 
Currentlty the learnbot is aimed for American University of Armenia (AUA), thus it may be uncomfortable to use in other institutins. Nevertheless, we are ready to collaborate with people who will try to adapt leanbot for their organizations as well. 

## Version notes
Currently the app doesn't have a fully functional working version. Server (C++) and bot (node.js, botkit framework) are working separately. 

## Building notes
Since the app hasn't still a release version and bot works separately from the c++ server, building is a bit of complicated process. for running the bot part you need to run `bot.js` with node and give your slack bot token wither as enviromental variable or hardcode in code.

For testing the C++ part, you have to compile `main.cpp` with g++/gcc and also provide paths to other files. in server directory run 
```
$ g++ main.cpp -o server server.cpp student.cpp user.cpp course.cpp ../data_structures/BinSearchTree/BinSearchTree.cpp ../data_structures/HashTable/HashTable.cpp
$ ./server
```

_(A better testing variant will be added soon)_
