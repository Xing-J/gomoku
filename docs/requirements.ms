.nr HM 0.5i
.nr FM 0.5i
.EH
.OH
.ND
.TL
GOMOKU PROJECT REQUIREMENTS
.AU
.\" Add your names here
Benjamin I. Raskin, Student No. 180312330
.AI
Wilfrid Laurier University
.NH 1
Introduction
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
.NH 1
Overall Description
.NH 2
Product Description
.LP
.I
Gomoku
if a progressive web application with the game logic (neighbor cell calculation, consecutive simlar cell calculation) being powered by WASM.
.NH 2
Product Functions
.LP
The user will be able to play a game of Gomoku with another user sitting at the same computer. The users will take turns playing turns until a winner emerges.
.NH 2
Intended User
.LP
The user of
.I Gomoku
must fit the following characteristics:
.RS
.IP \(bu 0.2i
The user must be aware of the rules of the game Gomoku
.IP \(bu 0.2i
The user must have access to a computer with a graphical shell
.IP \(bu 0.2i
The user must have access to a modern web browser with WASM support
.RE
.NH 2
Contstraints
.LP
.I Gomoku
is designed to run in modern web browsers which support WASM. Browsers which lack support for WASM will not be able to properly run
.I Gomoku
as the majority of the game logic is implemented through WASM.