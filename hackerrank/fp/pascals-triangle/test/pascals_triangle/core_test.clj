(ns pascals-triangle.core-test
  (:require [clojure.test :refer :all]
            [pascals-triangle.core :refer :all]))

(deftest first-row
  (testing "Empty prev. row."
    (is (= [1] (gen-next-row [])))))

(deftest second-row
  (testing "Generate second row."
    (is (= [1 1] (gen-next-row [1])))))

(deftest fifth-row
  (testing "Generate fifth row."
    (is (= [1 4 6 4 1] (gen-next-row [1 3 3 1])))))