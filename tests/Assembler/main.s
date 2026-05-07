start:
    ldi A,0x05
    ldi B,0x01
    ldi C,0x1A
add11:
    add A,B
    cmp A,C
    jnz add11
    lb B,[0xffff]
    add A,B
    stri [0xffff], A
    jmp start