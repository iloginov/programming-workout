(defn fibonacci [n a b]
    (if (= 1 n)
        a
        (recur (dec n) b (+' a (*' b b)))))

(def input (read-line))

(let [[a b n] (map read-string (clojure.string/split input #" "))]
    (println (format "%d" (biginteger (fibonacci n a b)))))