(ns sum-of-odd-elements.core
  (:gen-class))

(defn sum-of-odd [s]
  (apply + (keep #(if (odd? %) %) s)))

(defn -main
  "I don't do a whole lot ... yet."
  [& args]
  (println "Hello, World!"))
