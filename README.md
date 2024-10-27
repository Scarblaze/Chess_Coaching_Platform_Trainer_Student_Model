Problem Statement:
Design a system for a chess coaching platform that efficiently manages and matches students with trainers based on specific attributes using an array of structures. The system should store details about students and trainers, their preferences, and progress, enabling an automated trainer-student matching and tracking of performance over time.
Attributes
Student Attributes
• Name
• ELO rating
• Learning goals (e.g., opening strategies, endgame techniques)
• Availability (time slots)
• Preferred coaching styles in the priority order.  Coaching styles are aggressive, positional, defensive.
• Current trainer ID (if trainer is assigned)
• Performance data (weak areas like tactics, endgames, etc.)
• Progress 
Games played/won, 
Puzzles solved, 
Rating changes every month for last 1 year. 

Trainer Attributes
Trainer ID
Name
ELO rating
Coaching style (One of aggressive, defensive, positional)
Availability (time slots)
Experience level (years of coaching)
Elo rating : Does not admit students below some ELO rating “E” (E is an integer above 1400)
Maximum number of students the trainer can take

Operations - (Write functions for these operations). 
Add Student: A function that adds a student to the system with their attributes
Add Trainer: A function that adds a trainer with their details.
Delete student : Delete student record from the list of students.
Delete trainer :  Delete trainer record from the list of students. 
List set of students with every trainer : For every trainer, list the set of students he/she is teaching.  
Sort Students: Sort list of students based on their ELO rating in the decreasing order. If two players have the same ELO rating then the player with higher number of games won is given priority. 
Find out the most popular trainer – A trainer is the most popular if he teaches maximum number of students. Sort the trainers in decreasing order of their popularity. If two trainers have same number of students then the trainer who has students with higher average ELO rating of students is given a preference. 
Find out the strongest trainer – A trainer is strongest if the average rating of his/her students is highest. Sort the list of trainers in the decreasing order based on this criteria. 
Assign Trainer: A function to assign a trainer based for a given student based on Matching criteria defined earlier. 
Find list of students who have successively increased their rating every month for the last one year. Sort them in the decreasing order of ELO rating gains over the last year. 

Matching Algorithm: Based on the student’s attributes (ELO rating, availability, preferred coaching style) and trainer’s attributes (availability, coaching style, experience), we can assign a suitable trainer to a student. A student will like to get assigned to a trainer if student’s availability and preferred coaching style matches with that of trainer, and the trainer has not reached the maximum limit of students.  Please note and use the “E” elo rating criterion by the trainer as well. If a student is not matched to the best choice, he goes for the next best choice. Availabity matching is must, student can compromise on coaching style and ELO rating criterion of the trainer in that order. 
