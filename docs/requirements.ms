.nr HM 0.5i
.nr FM 0.5i
.EH
.OH
.ND
.TL
Gomku Project Requirements
.AU
.\" Add your names here
Benjamin Raskin, Student No. 180312330
Chen Jin, Student No. 170631720
Xing Jia, Student No. 180164170
Huiqiao Yang, Student No.186803710
Yongtai Yang, Student No. 190624980
Mengyuan Liu, Student No.186802750
Zehao Liu, Student No. 193074000
.AI
Wilfrid Laurier University
.NH 1
Introduction
.LP
Gomoku is a web-based strategy board game played between two people. The purpose of this game simulation is to practice our group working ability and learn new components through the work. It is a strategy game which is easy to understand in game logic so that people at any age are suitable to play this game. People will train their logical thinking and have fun in this game.
.NH 2
Project Summary
.LP
.I Gomoku
is an implementation of the classic Gomoku game. The game is implemented as a progressive web application powered by WASM for better performance.
.NH 2
Purpose
.LP
This documents covers all of the project requirements and details that are needed for the project to work.
.NH 2
Scope and Business Model
.NH 3
Scope
.LP
Gomoku is web application which allows for users to play Gomoku against other players locally, or against AI. The goal is to create a no-frills, user friendly and accessible web application for both casual Gomoku players as well as enthusiasts. 
.LP
This document covers all of the functional features of
.I Gomoku
and the basic plans for the process of implementation and non-functional features of the project.
.NH 3
Business Model
.LP
.I Gomoku
is Free Software licensed under the GPLv3 and protected by Copyleft. Anyone can use
.I Gomoku
for any purpose, as well as inspect, edit, and share the source code.
.NH 2
Definitions
.IP \(bu 0.2i
.B WASM
Web assembly, a binary format and runtime environment for low level code in the browser
.NH 1
Overall Description
.NH 2
Product Description
.LP
.I Gomoku
if a progressive web application with the game logic (neighbor cell calculation, consecutive simlar cell calculation) being powered by WASM.
.NH 2
Product Functions
.LP
The user will be able to play a game of Gomoku with another user sitting at the same computer. The users will take turns playing turns until a winner emerges.
.\" Sample GUI is in progress, will add in later
.NH 2
Intended User
.LP
The user of
.I Gomoku
must fit the following characteristics:
.IP \(bu 0.2i
The user must be aware of the rules of the game Gomoku
.IP \(bu 0.2i
The user must have access to a computer with a graphical shell
.IP \(bu 0.2i
The user must have access to a modern web browser with WASM support
.NH 2
Contstraints
.LP
.I Gomoku
is designed to run in modern web browsers which support WASM. Browsers which lack support for WASM will not be able to properly run
.I Gomoku
as the majority of the game logic is implemented through WASM.
.\" Document is still WIP
.NH 1
Technical Requirements
.NH 2
External Interface
.LP
The external interface for the application consists of a single page progressive application. The user is presented with a nineteen by nineteen grid upon which the game is played.
.NH 2
Logic and Functions
.LP
The game logic will be implemented using WASM, that is moves and game state is calculated via a set of functions exposed to Javascript through WASM bindings. The logic of the game consists of determinig which user's turn it is as well as whether or not a user has won the game. Javascript code will invoke the game logic functions through WASM bindings to progress the game and to draw the corresponding players on the grid.
.NH 2
Portability
.LP
Since the game is played in the browser, and WASM is now a browser standard the application is portable through and through on all modern web browsers.
