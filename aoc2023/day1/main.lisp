(defun day1 ()
  (with-open-file (file
                   "input2"
                   :direction :input)
    (day1-solver file)))

(defun day1-solver (stream)
  (let ((sum 0))
    (loop for line = (read-line stream nil)
          while line do (setf sum (+ sum (find-first-last line))))
    (format t "~a~%" sum)
    ))

(defun find-first-last (str)
  (let ((first nil) (last nil))
    (dotimes (i (length str))
      (let* ((c (elt str i))
             (n (digit-char-p c)))
        (if n
            (if (equal first nil)
                (setq first c)
                (setq last c)))))
    (if (equal last nil)
        (setq last first))
    (list first last)))

(defun to-str (first-last)
  (concatenate 'string "" first-last))
