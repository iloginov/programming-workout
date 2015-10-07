(ns sum-of-odd-elements.core-test
  (:require [clojure.test :refer :all]
            [sum-of-odd-elements.core :refer :all]))

(deftest dummy
  (testing "Empty sequence."
    (is (= 0 (sum-of-odd [])))))

(deftest statement
  (testing "Example from statement."
    (is (= 16 (sum-of-odd [3 2 4 6 5 7 8 0 1])))))