; Q1 (5 points)
(- (+ (* 9 2) 5) 3)
(- (* (+ (/ 12 5) 6) 5) (* 21 4))
(* (* 21 (+ (- 5 (* 7 3)) (/ 9 4)) ) 4) 
(* (+ (/ (+ (/ 5 6) (* 7 8)) (- 9 10)) 4) (+ 2 3)) 
(+ (/ (- (/ (/ (* (- 4 6) (+ (* 6 5) 4)) 2) 2) 5) 2) (+ (/ (+ (* 4 5) (* (/ 5 2) 4)) 2) (* 4 5)))

; Q2 (5 points)
(define two 2)
(define four 4)
(define five 5)
(define six 6)

(+ (/ (- (/ (/ (* (- four six) (+ (* six five) four)) two) two) five) two) (+ (/ (+ (* four five) (* (/ five two) four)) two) (* four five)))

; Q3 (5 points)
(define Product (lambda (x y)
  (* x y)
))
(Product 10 40)

; Q4 (15 points)
(define Power
  (lambda (x y)
    (if (= y 0)
     1
           (Product x (Power x (- y 1))))))
(Power 2 5)

; Q5 (5 points)
(define (ReadForPower)
  (define x (read))
  (define y(read))
  (Power x y))
(ReadForPower)

; Q6 (10 points)
(define ProductPowers (lambda (a b c d)
                        (Product (Power a b) (Power c d))
                        )
  )
(ProductPowers 2 5 3 4)

;Q7 (5 points)
(define (ProductLet x y)
  (let ((a x)(b y))
    (* a b)))
(ProductLet 60 40)
