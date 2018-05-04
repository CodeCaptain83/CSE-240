;Name: hw12solution
;Course: CSE 240


;Q1
(define OR-GATE (lambda (a b)
             (if (and (= a 0) (= b 0))
                      0
                      1
             )
            )
)
(define AND-GATE (lambda (a b)
              (if (and (= a 1) (= b 1))
                  1
                  0
               )
              )
 )
(define NOT-GATE (lambda (a)
               (if (= a 0)
                   1
                   0
                )
             )
)
(define XOR-GATE (lambda (a b)
                   (cond
                     ((and (= a 1) (= b 0)) 1)
                     ((and (= a 0) (= b 1)) 1)
                     (else 0)
                   )
                  )
)
(AND-GATE 0 0)
(AND-GATE 0 1)
(AND-GATE 1 0)
(AND-GATE 1 1)
;0
;0
;0
;1
(newline)
(OR-GATE 0 0)
(OR-GATE 0 1)
(OR-GATE 1 0)
(OR-GATE 1 1)
;0
;1
;1
;1
(newline)
(XOR-GATE 0 0)
(XOR-GATE 0 1)
(XOR-GATE 1 0)
(XOR-GATE 1 1)
;0
;1
;1
;0

;Q2
(define bitAdder (lambda (x a b)
                  (cons (sum-bits x a b) (carry-out x a b))
                  )
)
(define sum-bits (lambda (x a b)
                   (XOR-GATE (XOR-GATE b a) x )
                  )
 )
(define carry-out (lambda (x a b)
                    (OR-GATE (AND-GATE x (OR-GATE a b)) (AND-GATE a b))
                   )
)
(newline)
(bitAdder 0 0 0) 	
(bitAdder 0 0 1) 	
(bitAdder 0 1 0) 	
(bitAdder 0 1 1)	
(bitAdder 1 0 0) 	
(bitAdder 1 0 1)	
(bitAdder 1 1 0) 	
(bitAdder 1 1 1) 
;(0 . 0)
;(1 . 0)
;(1 . 0)
;(0 . 1)
;(1 . 0)
;(0 . 1)
;(0 . 1)
;(1 . 1)


;Q3.1
(define tail (lambda (lst)
               (cond
                 ((null? lst) lst)
                 ((null? (cdr lst)) (car lst))
                 (else (tail (cdr lst)))
               )
 )
)
;Q3.2
(define rmtail (lambda (lst)
                (cond
                  ((null? lst) lst)
                  ((null? (cdr lst)) '())
                  (else (cons (car lst) (rmtail (cdr lst))))
                  )
              )
 )
;Q3.3
;1.) Size-n problem: find the binary sum of two binary numbers of the same length.
;2.) Stopping condtion: n == 0. Return value: result bit representing the sum of ai and bi.
;3.) Size-m problem: find the binary sum of two binary numbers of one less length.
;4.) See below

;Q3.4
(define X1 '(0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0) )	
(define X2 '(1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1) )	
(define X3 '(0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1) )	
(define X4 '(1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0) )
(define X5 '(0 1 0 1 0 1 0 1 0 1 0 1 0 1 1 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 1 1) )	
(define X6 '(1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 1 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 1) )

;Solution 1
(define n-bit-adder1 (lambda (L1 L2 n)
                    (cond
                      ((or (null? L1) (null? L2)) (display "Error: need two binary numbers of same length"))
                      ((or (not (= (length L1) (length L2)))) (display "Error: need two binary numbers of same length"))
                      (else
                         (let (
                               (x (bitAdder 0 (tail L1) (tail L2))) 
                               )
                            (cons (list ( n-bit-adder-carry-out (rmtail L1) (rmtail L2) (- n 1) x)) (reverse(n-bit-adderhelper1 (rmtail L1) (rmtail L2) (- n 1) x)) )
                          )  
                      )
                     )
                    )
)
(define n-bit-adderhelper1 (lambda (L1 L2 n resulti)
                      (cond
                        ((= n 0) (list(car resulti)))
                        (else
                         (let (
                               (x (bitAdder (cdr resulti) (tail L1) (tail L2))) 
                               )
                             (cons (car resulti) (n-bit-adderhelper1 (rmtail L1) (rmtail L2) (- n 1) x))
                          )
                         )
                       )
                     )
)
(define n-bit-adder-carry-out (lambda (L1 L2 n resulti)
                      (cond
                        ((= n 0) (cdr resulti))
                        (else
                         (let (
                               (x (bitAdder (cdr resulti) (tail L1) (tail L2))) 
                               )
                             ( n-bit-adder-carry-out (rmtail L1) (rmtail L2) (- n 1) x)
                          )
                         )
                       )
                     )
)
(newline)
(n-bit-adder1  X1 X2 32)
(n-bit-adder1  X3 X4 32)
(n-bit-adder1  X5 X6 32)
(n-bit-adder1  X2 X3 32)
(n-bit-adder1  X4 X5 32)
(n-bit-adder1  X1 X6 32)
;((0) 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1)
;((0) 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1)
;((1) 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0)
;((1) 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 0)
;((1) 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1)
;((0) 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 1 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 1)

;Solution2
(define n-bit-adder (lambda (L1 L2 n)
                    (cond
                      ((or (null? L1) (null? L2)) (display "Error: need two binary numbers of same length"))
                      ((or (not (= (length L1) (length L2)))) (display "Error: need two binary numbers of same length"))
                      (else
                       (let ((lst1 (reverse L1)) (lst2 (reverse L2)))
                         (let (
                               (x (bitAdder 0 (car lst1) (car lst2))) 
                               )
                            (cons (list (n-bit-adderh1 (cdr lst1) (cdr lst2) (- n 1) x)) (reverse(n-bit-adderh (cdr lst1) (cdr lst2) (- n 1) x)) )
                          )
                       )
                      )
                     )
                    )
  
)
(define n-bit-adderh (lambda (L1 L2 n resulti)
                      (cond
                        ((= n 0) (list(car resulti)))
                        (else
                         (let (
                               (x (bitAdder (cdr resulti) (car L1) (car L2))) 
                               )
                             (cons (car resulti) (n-bit-adderh (cdr L1) (cdr L2) (- n 1) x))
                          )
                         )
                       )
                     )
)
(define n-bit-adderh1 (lambda (L1 L2 n resulti)
                      (cond
                        ((= n 0) (cdr resulti))
                        (else
                         (let (
                               (x (bitAdder (cdr resulti) (car L1) (car L2))) 
                               )
                             (n-bit-adderh1 (cdr L1) (cdr L2) (- n 1) x)
                          )
                         )
                       )
                     )
)
(newline)
(n-bit-adder  X1 X2 32)
;((1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1) . 0)
(n-bit-adder  X3 X4 32)
;((1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1) . 0)
(n-bit-adder  X5 X6 32)
;((0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0) . 1)
(n-bit-adder  X2 X3 32)
;((0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 0) . 1)
(n-bit-adder  X4 X5 32)
;((0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1) . 1)
(n-bit-adder  X1 X6 32)
;((1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 1 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 1) . 0)




