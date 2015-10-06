(defn fibonacci [n]
  (let [fib (fn fib [n a b]
  				(if (= 1 n)
    				a
    				(recur (dec n) b (+ a b))))]
    (fib n 0 1)))

(def n (read-string (read-line)))

(println (fibonacci n))