#!/usr/bin/env guile

exec guile -s $0 "$@"
!#

(use-modules (srfi srfi-37))

(define (show-usage)
  (simple-format #t "Usage: demo [OPTIONS] FILE
Execute a demo for guile-standalong.\n"))

(define options
  (list 
   (option '(#\h "help") #f #f
           (lambda (opt name arg opts)
             (acons 'help #t opts)))
   ))

(define (parse-args args)
  (args-fold args
             options
            (lambda (opt name arg opts)
               (simple-format #t "unrecognized option: ~S" name)
               (exit 1))
             (lambda (file opts)
               (acons 'file file opts))
             '()))

(define (main args)
   (let* ((opts (parse-args args)))
      (when (assq-ref opts 'help)
         (show-usage)
         (exit))
    0))

(main (cdr (program-arguments)))

;; --- last line ---
