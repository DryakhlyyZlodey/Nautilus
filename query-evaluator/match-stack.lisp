
(in-package :xql)

(defstruct (match-stack (:conc-name match-)) tag num-items stack)

(defun create-match-stack (tag)
  (make-match-stack :tag tag :num-items 0 :stack (make-array 0 :fill-pointer 0 :adjustable t)))

(defun push-match (stack entry)
  (vector-push-extend entry (match-stack stack))
  (incf (match-num-items stack)))

(defun pop-match (stack)
  (vector-pop (match-stack stack))
  (decf (match-num-items stack)))

(defun clear-stack (stack)
  (if (> (match-num-items stack) 0)
      (do ((i (match-num-items stack) (decf i)))
	  ((> 1 i))			;
	(pop-match stack))))




		 