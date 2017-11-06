# go
a go parser

## usage
> make
> ./interpreter megaexample

## authors
Rui Balau 201103891
Cláudia Correia 201304727

## example output
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
