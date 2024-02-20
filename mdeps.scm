;; module dependencies

(use-modules (ice-9 match))
(use-modules ((srfi srfi-1) #:select (fold delete-duplicates)))
(use-modules (ice-9 pretty-print))
(define pp pretty-print)
(define (sf fmt . args) (apply simple-format #t fmt args))

(define (module-filename mod-spec)
  (fold
   (lambda (pfix path)
     (if path path
         (let ((path
                (string-append
                 pfix "/" (string-join (map symbol->string mod-spec) "/")
                 ".scm")))
         (and (access? path R_OK) path))))
   #f %load-path))

(define (spec-dep spec seed)
  (cons
   (match spec
     (((sdl ...) . _) sdl)
     ((sdl ...) sdl))
   seed))

(define (mod-deps exp seed)
  (let loop ((deps seed) (tail (cddr exp)))
    (match tail
      ('() deps)
      (`(#:use-module ,spec . ,rest)
       (loop (spec-dep spec deps) rest))
      ((key val . rest)
       (loop deps rest)))))

(define (probe-module-file filename)
  (call-with-input-file filename
    (lambda (port)
      (let loop ((deps '()) (exp (read port)))
	(match exp
	  ((? eof-object?) (reverse deps))
          (`(define-module . ,_)
	   (loop (mod-deps exp deps) (read port)))
          (`(use-modules . ,specs)
           (loop (fold spec-dep deps specs) (read port)))
          (_
           (loop deps (read port))))))))

;; mod-name : '(ice-9 regex)
(define (probe-module mod-name)
  (sf "probe ~S => ~S\n" mod-name (module-filename mod-name))
  (sleep 1)
  (cons mod-name (probe-module-file (module-filename mod-name))))

(define (get-dict mod-name)
  (let loop ((dict '()) (todo (list mod-name)))
    (cond
     ((null? todo)
      (reverse dict))
     ((assoc-ref dict (car todo))
      (loop dict (cdr todo)))
     (else
      (let ((entry (probe-module (car todo))))
        (loop (cons entry dict) (append (cdr entry) todo)))))))

(define (get-conns dict)
  (let loop ((cns '()) (dis dict))
    (if (null? dis) cns
        (loop (append (map (lambda (dep) (cons (caar dis) dep)) (cdar dis)) cns)
              (cdr dis)))))

;; => (values pre rpost lks)
(define (gen-orders nodes conns)
  (let loop ((pre '()) (rpost '()) (lks '())
             (ix 1) (jx (length nodes))
             (nd #f) (cns '())
             (stk '()) (uvs nodes))
    (cond
     ((pair? cns)
      (cond
       ((and (eq? (caar cns) nd) (not (assq (cdar cns) pre)))
        (let* ((dst (cdar cns))
               (pre (acons dst ix pre))
               (uvs (delq dst uvs))
               (stk (acons nd cns stk)))
          (loop pre rpost lks ix jx nd (cdr cns) stk uvs)))
       (else
        (loop pre rpost lks ix jx nd (cdr cns) stk uvs))))
     ((pair? stk)
      (loop pre (acons nd jx rpost) lks ix (1- jx) (caar stk) (cdar stk)
            (cdr stk) uvs))
     ((pair? uvs)
      (let* ((rpost (if nd (acons nd jx rpost) rpost))
          (jx (if nd (1- jx) jx))
             (nd (car uvs))
             (uvs (cdr uvs)))
        (loop (acons nd ix pre) rpost lks (1+ ix) jx nd conns stk uvs)))
     (else
      (values pre (acons nd jx rpost) lks)))))


;;(pp (get-dict '(nyacc lang c99 munge)))

(let* (
       ;;(module '(nyacc lang c99 munge))
       (module '(ice-9 boot-9))
       (dict (get-dict module))
       (conns (get-conns dict))
       (nodes (delete-duplicates (cons (caar dict) (map cdr conns))))
       )
  (pp dict)
  (pp "====")
  (pp conns)
  (pp "====")
  (pp nodes)
  #f)
;;(load "tzort.scm")
;;(use-modules (tzort))

;;(define dct (get-dict '(nyacc lang c99 munge)))

;;(define g1 '((u v x) (v y) (w y z) (x v) (y x) (z z)))
;;(define lst (tzort g1))

;;(pp lst)

;; --- last line ---
