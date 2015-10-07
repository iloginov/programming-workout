(ns pascals-triangle.core
  (:gen-class))

(defn gen-next-row [row]
  (if (empty? row)
    [1]
    (vec (map + (cons 0 row) (conj row 0)))))

(defn -main
  "I don't do a whole lot ... yet."
  [& args]
  (loop [N (read-string (read-line))
         row [1]]
    (when (> N 0)
      (println (reduce #(str %1 %2 " ") "" row))
      (recur (dec N) (gen-next-row row)))
    ))
