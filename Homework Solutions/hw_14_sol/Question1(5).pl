% stopping conditions

foo(X,0,Return) :- 
	Return is X, !. /* it is optional to use cut ! in the stopping conditions */
	
foo(X,-1,Return) :- 
	Return is X, !.
	
foo(X,-2,Return) :- 
	Return is X, !.
	
foo(0,Y,Return) :- 
	Return is Y, !.
	
foo(-1,Y,Return) :- 
	Return is Y, !.

% size-n problem
foo(X,Y,Return) :- 
	X >= Y, 
	Z is X - 2,
	foo(Z, Y, R),	% size-m problem
	Return is X+R.
	
% size-n problem
foo(X,Y,Return) :- 
	X < Y, 
	Z is Y - 3,
	foo(X, Z, R),	% size-m problem
	Return is Y+R.