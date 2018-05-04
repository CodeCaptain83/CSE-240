/* Solution */

/* Facts */
/* Question 2.1 */
entre(lunch, sandwhich).
entre(dinner, spaghetti).

side(lunch, chips).
side(lunch, lemonade).
side(dinner, bread).
side(dinner, greentea).

ingredient(chips, potato).
ingredient(chips, salt).
ingredient(lemonade, lemon).
ingredient(lemonade, sugar).
ingredient(bread, egg).
ingredient(bread, flour).
ingredient(greentea, green).
ingredient(greentea, tea).

/* Rules */
/* Question 2.2 */
meal(X, Y) :- 
	entre(X, Y);
	side(X, Y).

/* Question 2.3 */
shoppinglist(X, Z) :-
	side(X, Y),
	ingredient(Y, Z).
	
/* 
Rubric:

Question 2.1:
entre facts:
	(-1) minor mistake
	(-2) incorrect answer
	(-3) no facts
side facts:
	(-1) minor mistake
	(-2) incorrect answer
	(-3) no facts
ingredient facts:
	(-1) minor mistake
	(-2) incorrect answer
	(-3) no facts

Questions 2.2 and 2.3:
(-1) minor mistake
(-3) incorrect answer
(-5) no attempt
*/