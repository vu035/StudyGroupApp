Study Group Former
=======
 1. Introduction
 ===

1.1 Purpose

The use case document describes the specification along with some requires of a console application Study Group Former (SGF). In addition, this document will describe how the program works and what requirements are necessary in the use case specification.

1.2 Background
Often times, students find it hard to meet new people in their classes, or find it difficult be able to connect with people of the same classes who are suffering from the same difficulty of the same topic of a course. This desktop application will provide a way for these individuals to get together, across different sections of a class and review the subject.

1.3 Definition, Acronyms, and Abbreviations

  * Study Group Former 		(SGF)

2. System Requirements
===

2.1 Current “System”

Currently study groups are formed when students are presented with opportunity to introduce, meet, or talk with one another. Therefore, these are informally formed by an individual’s desire to have a group dedicated to do so.

2.2 Actors

Students and/or professors will be held accountable for formation of groups and setting a limit or cap on how many attendees there may be.

2.3 Basic Use Cases

2.3.1 Create a Study group

* 2.3.1.1 User logs into the system
		* 2.3.1.1.1 If the user does not have a login, they will create one

			   -First, Last Name, email, Username, Password

	 *	2.3.1.1.2 A SQL database will be used to store study group attributes


* 2.3.1.2 User has looks at list of groups formed
* 2.3.1.3 User will look and join a group
	* 2.3.1.3.1 If there is not a group available for the current user’s topic they will create one

	*	2.3.1.3.2 User will specify attributes for study group:
			       -Class Name, Course Number, Section Number, Max Number of Participants
			        Date of study, (Hidden date – day after date of study)

* 2.3. 1.4 User will wait for other members to join

	* 2.3. 1.5 The group will automatically be deleted the day after the day of study (the hidden date)

	* 2.3. 1.6 Once a cap has been reached, the group will no longer be visible



* 2.3.2 Admin can Edit groups
	* 2.3.2.1 Admin can Remove groups
	* 2.3.2.2 Delete and create users
	* 2.3.2.1 Update courses per semester
