/* Database for family tree. It consists of facts and rules. */

/* Facts */
male(abe).
male(rob).
male(jim).
male(mac).
male(ben).
male(bud).
male(tex).
male(roy).
male(kai).
male(lee).
female(joy).
female(ana).
female(mia).
female(kim).
female(zoe).
female(val).
female(mae).
female(amy).
female(pam).

father_of(abe, ana). /* abe is the father of ana */
father_of(abe, rob). /* abe is the father of ana */
father_of(abe, jim). /* abe is the father of ana */
father_of(kai, lee). 
father_of(kai, pam).
father_of(jim, kim).
father_of(jim, mac).
father_of(bud, zoe).
father_of(bud, val).
father_of(bud, tex).
father_of(bud, roy).
father_of(ben, bud).
father_of(ben, amy).

mother_of(joy, rob). /* joy is the mother of rob */
mother_of(joy, jim). /* joy is the mother of rob */
mother_of(joy, ana). /* joy is the mother of rob */
mother_of(mia, kim).
mother_of(mia, mac).
mother_of(ana, zoe).
mother_of(ana, val).
mother_of(ana, tex).
mother_of(ana, roy).
mother_of(mae, bud).
mother_of(mae, amy).
mother_of(amy, lee).
mother_of(amy, pam).

/* Rules */
is_male(X) :-
 	male(X);
	father_of(X, _).
	
/* Question 1.2 */
is_female(X) :- 
	female(X);
	mother_of(X, _).
	
/* Question 1.3 */
grandmother_of(X, Z) :-	
	mother_of(X, Y), 
	parent_of(Y, Z).

grandfather_of(X, Z) :-
	father_of(X, Y), 
	parent_of(Y, Z).
	
/* Question 1.4 */
sibling_of(X, Y) :-
	parent_of(Z, X),
	parent_of(Z, Y),
	X \== Y.

/* Question 1.5 */
parent_of(X, Y) :- 	
	father_of(X, Y);
	mother_of(X, Y).

/* Question 1.6 */
descendent_of(X, Y) :- 
	parent_of(Y, X).

descendent_of(X, Y) :-
	parent_of(Y, Z),
	descendent_of(X, Z).

	/* 
Rubric:
Each Question is worth 3 - 5 points.
(-1) for minor mistake.
(-2/3 or -3/5) for incorrect answer.
No points for no attempt.
*/