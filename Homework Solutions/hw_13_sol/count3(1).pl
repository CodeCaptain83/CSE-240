count3([], 0, 0, 0).
count3([H|T], P, Z, N) :- H>0, count3(T, P1, Z, N), P is P1+1.
count3([H|T], P, Z, N) :- H=:=0, count3(T, P, Z1, N), Z is Z1+1.
count3([H|T], P, Z, N) :- H<0, count3(T, P, Z, N1), N is N1+1.
