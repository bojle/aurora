
start:
    lda a
    cmp 10          ; cmp_flag = 1
    jmp is_10
not_10
    print no
    jmp exit
is_10
    print 10
exit
