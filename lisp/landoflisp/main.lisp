(defparameter *default-small* 1)
(defparameter *default-big* 100)
(defparameter *small* *default-small*)
(defparameter *big* *default-big*)

(defun guess-my-number ()
  (ash (+ *small* *big*) -1))

(defun smaller ()
  (setf *big* (1- (guess-my-number)))
  (guess-my-number))

(defun bigger ()
  (setf *small* (1+ (guess-my-number)))
  (guess-my-number))

(defun start-over()
  (defparameter *small* *default-small*)
  (defparameter *big* *default-big*)
  (guess-my-number))

(defun my-length (list)
  (if list
      (1+ (my-length (cdr list)))
      0))


(defun say-hello ()
  (print "Please type your name:")
  (let ((name (read)))
        (print "Nice to met you, ")
        (print (+ name 5))))
