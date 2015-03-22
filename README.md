# SudoGen
Sudoku Generator &amp; Solver written in C++ and Qt. 
The basic idea behind the program is to randomly generate a solvable Sudoku puzzle
where either the user or the program attempts to solves it. Program solving techniques
as of current are restricted to tradtional sudoku solving techniques (finding matching
pairs, backward elimination, etc.) though alternative techniques such as heuristics and 
k-SAT (http://www.nature.com/srep/2012/121011/srep00725/full/srep00725.html) are planned
to be added. 

![readme picture](https://cloud.githubusercontent.com/assets/8493854/6734932/ba9ddaca-ce39-11e4-9345-63b46c1d3e90.JPG)

To-Do list:
-----------

- Add a method for user pre-defined puzzle input (through GUI, file or otherwise)

- Implement a way to guarantee solvable problem

- Alternative Problem solving techniques, heuristic and otherwise

- Time & Mistakes tracking 

- Program settings

- Background music (maybe)

Version History: 
----------------

March 21 2015
- Version 0.3
- Fixed misc bugs - user input and random number generation now work as intended 
- Sudoku Solver implemented - single elimination works now (partially solves the 
- puzzle)

March 19 2015
- Version 0.2
- GUI functionality mostly implemented

March 12 2015
- Initial version, generates a puzzle and partially solves it 
- in console
