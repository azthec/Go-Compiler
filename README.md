# go
a go parser

## usage
rename corresponding namefile to desired output
> mv Makefile_mips Makefile
> make
> ./print_mips megaexample.txt

## example output for print_ast.c
depth| command

```
func main() {
1| Sprint(varXYZ);
1| x := 1234 ;
1| Sprint(1  + 1  + 1  + 1 );
1| Sprint(1  + 1  + 2  + 3  + 5  + 8  + 13  + 21 );
1| Sscan(xyZED);
1| x := 1313 ;
1| x := 1  + 1  + 1 ;
1| x := 3 ;
1| x := 5  + 3  - 2  * 5  * 5  - 10  10 ;
1| ylul := 4 ;
1| if x > 1 {
2| y := 3 ;
1| }
1| x := 20  5 ;
1| if ! 1 {
2| if ! 0 {
3| if 0  || 0 {
4| ast := 2 ;
3| }
2| }
1| }
1| for 1  {
2| if 0 {
3| y := 0 ;
2| }
1| }
1| if 1  && 1 {
2| if 0  || 0 {
3| yxz := 1 ;
2| }
1| }
1| if 1  == 0 {
2| y := 5 ;
1| }
1| if x < 1 {
2| y := x + 1 ;
1| } elseif x > 1 {
2| y := 1  * x + b;
1| } else
2| x := 3 ;
1| }
1| if x < 1 {
2| x := 1 ;
1| } elseif 1  < x{
2| y := 2 ;
2| xzs := 123 ;
1| }
1| for x < 4  {
2| x := 4 ;
1| }
1| for x:=4 ; x < 4 ; i + 1  {
2| x := 5 ;
1| }
}
```

## example output for print_tac.c
```
main:
    BeginFunc 24;
    $t0 = varXYZ;
    PRINT($t0);
    $t1 = x;
    $t0 = 1234;
    $t1 = $t0;
    $t1 = x;
    $t0 = 1;
    $t1 = 1;
    $t2 = $t0 + $t1;
    $t3 = 1;
    $t4 = $t2 + $t3;
    $t5 = 1;
    $t6 = $t4 + $t5;
    PRINT($t6);
    $t0 = 1;
    $t1 = 1;
    $t2 = $t0 + $t1;
    $t3 = 2;
    $t4 = $t2 + $t3;
    $t5 = 3;
    $t6 = $t4 + $t5;
    $t7 = 5;
    $t8 = $t6 + $t7;
    $t9 = 8;
    $t10 = $t8 + $t9;
    $t11 = 13;
    $t12 = $t10 + $t11;
    $t13 = 21;
    $t14 = $t12 + $t13;
    PRINT($t14);
    SCAN(xyZED);
    $t1 = x;
    $t0 = 1313;
    $t1 = $t0;
    $t1 = x;
    $t5 = x;
    $t0 = 1;
    $t1 = 1;
    $t2 = $t0 + $t1;
    $t3 = 1;
    $t4 = $t2 + $t3;
    $t5 = $t4;
    $t5 = x;
    $t1 = x;
    $t0 = 3;
    $t1 = $t0;
    $t1 = x;
    $t13 = x;
    $t0 = 5;
    $t1 = 3;
    $t2 = $t0 + $t1;
    $t3 = 2;
    $t4 = $t2 - $t3;
    $t5 = 5;
    $t6 = $t4 * $t5;
    $t7 = 5;
    $t8 = $t6 * $t7;
    $t9 = 10;
    $t10 = $t8 - $t9;
    $t11 = 10;
    $t12 = $t10 %s;
    $t13 = $t12;
    $t13 = x;
    $t1 = ylul;
    $t0 = 4;
    $t1 = $t0;
    $t1 = ylul;
    $t0 = x;
    $t1 = 1;
    $t2 = $t0 > $t1;
    IfZ $t2 Goto, L0;
    $t4 = y;
    $t3 = 3;
    $t4 = $t3;
    $t4 = y;
    Goto E0;
L0:
E0:
    $t3 = x;
    $t0 = 20;
    $t1 = 5;
    $t2 = $t0 %s;
    $t3 = $t2;
    $t3 = x;
    $t0 = 1;
    $t1 = 1;
    $t2 = !$t0;
    IfZ $t2 Goto, L1;
    $t3 = 0;
    $t4 = 0;
    $t5 = !$t3;
    IfZ $t5 Goto, L2;
    $t6 = 0;
    $t7 = 0;
    $t8 = $t6 || $t7;
    IfZ $t8 Goto, L3;
    $t10 = ast;
    $t9 = 2;
    $t10 = $t9;
    $t10 = ast;
    Goto E3;
L3:
E3:
    Goto E2;
L2:
E2:
    Goto E1;
L1:
E1:
L4:
    $t0 = 1;
    IfZ $t0 Goto, L5;
    $t1 = 0;
    IfZ $t1 Goto, L6;
    $t3 = y;
    $t2 = 0;
    $t3 = $t2;
    $t3 = y;
    Goto E4;
L6:
E4:
    Goto L4;
L5:
    $t0 = 1;
    $t1 = 1;
    $t2 = $t0 && $t1;
    IfZ $t2 Goto, L7;
    $t3 = 0;
    $t4 = 0;
    $t5 = $t3 || $t4;
    IfZ $t5 Goto, L8;
    $t7 = yxz;
    $t6 = 1;
    $t7 = $t6;
    $t7 = yxz;
    Goto E6;
L8:
E6:
    Goto E5;
L7:
E5:
    $t0 = 1;
    $t1 = 0;
    $t2 = $t0 == $t1;
    IfZ $t2 Goto, L9;
    $t4 = y;
    $t3 = 5;
    $t4 = $t3;
    $t4 = y;
    Goto E7;
L9:
E7:
    $t0 = x;
    $t1 = 1;
    $t2 = $t0 < $t1;
    IfZ $t2 Goto, L10;
    $t6 = y;
    $t3 = x;
    $t4 = 1;
    $t5 = $t3 + $t4;
    $t6 = $t5;
    $t6 = y;
    Goto E8;
L10:
    $t7 = x;
    $t8 = 1;
    $t9 = $t7 > $t8;
    IfZ $t9 Goto, L11;
    $t15 = y;
    $t10 = 1;
    $t11 = x;
    $t12 = $t10 * $t11;
    $t13 = b;
    $t14 = $t12 + $t13;
    $t15 = $t14;
    $t15 = y;
    Goto E8;
L11:
    $t17 = x;
    $t16 = 3;
    $t17 = $t16;
    $t17 = x;
E8:
    $t0 = x;
    $t1 = 1;
    $t2 = $t0 < $t1;
    IfZ $t2 Goto, L12;
    $t4 = x;
    $t3 = 1;
    $t4 = $t3;
    $t4 = x;
    Goto E9;
L12:
    $t5 = 1;
    $t6 = x;
    $t7 = $t5 < $t6;
    IfZ $t7 Goto, L13;
    $t9 = y;
    $t8 = 2;
    $t9 = $t8;
    $t9 = y;
    $t11 = xzs;
    $t10 = 123;
    $t11 = $t10;
    $t11 = xzs;
    Goto E9;
L13:
E9:
L14:
    $t0 = x;
    $t1 = 4;
    $t2 = $t0 < $t1;
    IfZ $t2 Goto, L15;
    $t4 = x;
    $t3 = 4;
    $t4 = $t3;
    $t4 = x;
    Goto L14;
L15:
    $t3 = x;
    $t5 = 4;
    $t3 = $t5;
    $t3 = x;
L16:
    $t0 = x;
    $t1 = 4;
    $t2 = $t0 < $t1;
    $t3 = x;
    _t0 = $t3 < $t2;
    _t1 = $t3 == $t2;
    $t4 = _t0 || _t1;
    IfZ $t4 Goto, L17;
    $t7 = x;
    $t6 = 5;
    $t7 = $t6;
    $t7 = x;
    $t3 = x;
    $t4 = 1;
    $t3 = $t3 + $t4;
    $t3 = x;
    Goto L16;
L17:
    EndFunc;
```


## example output for print_mips.c

```
.data
    varXYZ
    x
    xyZED
    ylul
    y
    ast
    yxz
    b
    xzs
.text
    lw $t0, varXYZ
    li $v0, 1
    li $a0, $t0
    syscall
    lw $t1, x
    li $t0, 1234
    add $t1, $t0, $0
    sw $t1, x
    li $t0, 1
    li $t1, 1
    add $t2, $t0, $t1
    li $t3, 1
    add $t4, $t2, $t3
    li $t5, 1
    add $t6, $t4, $t5
    li $v0, 1
    li $a0, $t6
    syscall
    li $t0, 1
    li $t1, 1
    add $t2, $t0, $t1
    li $t3, 2
    add $t4, $t2, $t3
    li $t5, 3
    add $t6, $t4, $t5
    li $t7, 5
    add $t8, $t6, $t7
    li $t9, 8
    add $t10, $t8, $t9
    li $t11, 13
    add $t12, $t10, $t11
    li $t13, 21
    add $t14, $t12, $t13
    li $v0, 1
    li $a0, $t14
    syscall
    li $v0, 5
    syscall
    move $t0, $v0
    sw $t0, xyZED
    lw $t1, x
    li $t0, 1313
    add $t1, $t0, $0
    sw $t1, x
    lw $t5, x
    li $t0, 1
    li $t1, 1
    add $t2, $t0, $t1
    li $t3, 1
    add $t4, $t2, $t3
    add $t5, $t4, $0
    sw $t5, x
    lw $t1, x
    li $t0, 3
    add $t1, $t0, $0
    sw $t1, x
    lw $t13, x
    li $t0, 5
    li $t1, 3
    add $t2, $t0, $t1
    li $t3, 2
    sub $t4, $t2, $t3
    li $t5, 5
    mult $t4, $t5
    mflo $t6
    li $t7, 5
    mult $t6, $t7
    mflo $t8
    li $t9, 10
    sub $t10, $t8, $t9
    li $t11, 10
    div $t10, $t11
    mfhi $t12
    add $t13, $t12, $0
    sw $t13, x
    lw $t1, ylul
    li $t0, 4
    add $t1, $t0, $0
    sw $t1, ylul
    lw $t0, x
    li $t1, 1
    sgt $t2, $t0, $t1
    beq $t2, $0, L0
    lw $t4, y
    li $t3, 3
    add $t4, $t3, $0
    sw $t4, y
    j E0
L0:
E0:
    lw $t3, x
    li $t0, 20
    li $t1, 5
    div $t0, $t1
    mfhi $t2
    add $t3, $t2, $0
    sw $t3, x
    li $t0, 1
    li $t1, 1
    nor $t2
    beq $t2, $0, L1
    li $t3, 0
    li $t4, 0
    nor $t5
    beq $t5, $0, L2
    li $t6, 0
    li $t7, 0
    or $t8, $t6, $t7
    beq $t8, $0, L3
    lw $t10, ast
    li $t9, 2
    add $t10, $t9, $0
    sw $t10, ast
    j E3
L3:
E3:
    j E2
L2:
E2:
    j E1
L1:
E1:
L4:
    li $t0, 1
    beq $t0, $0, L5
    li $t1, 0
    beq $t1, $0, L6
    lw $t3, y
    li $t2, 0
    add $t3, $t2, $0
    sw $t3, y
    j E4
L6:
E4:
    j L4
L5:
    li $t0, 1
    li $t1, 1
    and $t2, $t0, $t1
    beq $t2, $0, L7
    li $t3, 0
    li $t4, 0
    or $t5, $t3, $t4
    beq $t5, $0, L8
    lw $t7, yxz
    li $t6, 1
    add $t7, $t6, $0
    sw $t7, yxz
    j E6
L8:
E6:
    j E5
L7:
E5:
    li $t0, 1
    li $t1, 0
    seq $t2, $t0, $t1
    beq $t2, $0, L9
    lw $t4, y
    li $t3, 5
    add $t4, $t3, $0
    sw $t4, y
    j E7
L9:
E7:
    lw $t0, x
    li $t1, 1
    slt $t2, $t0, $t1
    beq $t2, $0, L10
    lw $t6, y
    lw $t3, x
    li $t4, 1
    add $t5, $t3, $t4
    add $t6, $t5, $0
    sw $t6, y
    j E8
L10:
    lw $t7, x
    li $t8, 1
    sgt $t9, $t7, $t8
    beq $t9, $0, L11
    lw $t15, y
    li $t10, 1
    lw $t11, x
    mult $t10, $t11
    mflo $t12
    lw $t13, b
    add $t14, $t12, $t13
    add $t15, $t14, $0
    sw $t15, y
    j E8
L11:
    lw $t17, x
    li $t16, 3
    add $t17, $t16, $0
    sw $t17, x
E8:
    lw $t0, x
    li $t1, 1
    slt $t2, $t0, $t1
    beq $t2, $0, L12
    lw $t4, x
    li $t3, 1
    add $t4, $t3, $0
    sw $t4, x
    j E9
L12:
    li $t5, 1
    lw $t6, x
    slt $t7, $t5, $t6
    beq $t7, $0, L13
    lw $t9, y
    li $t8, 2
    add $t9, $t8, $0
    sw $t9, y
    lw $t11, xzs
    li $t10, 123
    add $t11, $t10, $0
    sw $t11, xzs
    j E9
L13:
E9:
L14:
    lw $t0, x
    li $t1, 4
    slt $t2, $t0, $t1
    beq $t2, $0, L15
    lw $t4, x
    li $t3, 4
    add $t4, $t3, $0
    sw $t4, x
    j L14
L15:
    lw $t3, x
    li $t5, 4
    add $t3, $t5, $0
    sw $t3, x
L16:
    lw $t0, x
    li $t1, 4
    slt $t2, $t0, $t1
    lw $t3, x
    sle $t4, $t3, $t2
    beq $t4, $0, L17
    lw $t7, x
    li $t6, 5
    add $t7, $t6, $0
    sw $t7, x
    lw $t3, x
    li $t4, 1
    add $t3, $t3, $t4
    sw $t3, x
    j L16
L17:
Exit:
    li $v0, 10
    syscall
```
