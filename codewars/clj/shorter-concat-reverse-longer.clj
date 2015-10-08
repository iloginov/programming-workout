(ns ReverseLonger)
  
(defn reverseLonger
  [a b]
  (let [mkansw (fn [s l] (str s (clojure.string/reverse l) s))]
    (if (< (count a) (count b))
      (mkansw a b)
      (mkansw b a))))
