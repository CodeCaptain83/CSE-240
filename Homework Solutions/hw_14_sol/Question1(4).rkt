(define (foo x y) // size-n problem
  (cond
    ((= y 0) x) // stopping condition, return value of stopping condition
    ((= x 0) y) // stopping condition, return value of stopping condition
    ((>= x y) (+ x (foo (- x 2) y))) // from size-(n-1) to size-n problem
    ((< x y) (+ y (foo x (- y 3)))) // from size-(n-1) to size-n problem
  )
)

(foo 5 6)