## Expr rest

```
expr_rest -> + term expr_rest
+

expr_rest -> - term expr_rest
-

expr_rest -> ε
$ )
```

## Factor

```
factor -> '(' expr ')'
'('

factor -> NUM
NUM
```

## Term rest

```
term_rest -> * factor term_rest 
*

term_rest -> / factor term_rest 
/

term_rest -> ε
+ $ - )
```
