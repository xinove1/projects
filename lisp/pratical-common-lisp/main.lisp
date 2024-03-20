(defmacro do-primes ((var start end) &body body)
  `(do ((,var (next-prime ,start) (next-prime (1+ ,var))))
       ((> ,var ,end))
     ,@body))

(defun foo2 ()
  (format t "Entering foo~%")
  (let ((func nil))
    (block a
      (format t " Entering BLOCK~%")
      (setq func #'(lambda () (return-from a)))
      (format t " Leaving BLOCK~%")))
  (format t "Leaving foo~%")
  (format t "calling func~%")
  (funcall func)
  (format t "after func~%"))

(defun foo ()
  (format t "Entering foo~%")
  (block a
    (format t " Entering BLOCK~%")
    (bar #'(lambda () (return-from a)))
    (format t " Leaving BLOCK~%"))
  (format t "Leaving foo~%"))

(defun bar (fn)
  (format t "  Entering bar~%")
  (block a (baz fn))
  (format t "  Leaving bar~%"))

(defun baz (fn)
  (format t "   Entering baz~%")
  (funcall fn)
  (format t "   Leaving baz~%"))
