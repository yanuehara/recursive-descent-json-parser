Recursive descent parser for a LL(1) grammar

This was a university assignment part of Compilers I course (taken in 
2016/1) in [FACOM/UFMS](http://facom.ufms.br) to build a recursive 
descent parser based in the following grammar (approximately JSON 
specification):

Json: Value EOF;
Value: Object | Array | STRING | NUMBER | TRUE | FALSE | NULL;
Object: "{" Members? "}";
Members: Pair ("," Pair)*;
Pair: STRING ":" Value;
Array: "[" Elements? "]";
Elements: Value ("," Value)*

The tokens are defined as follows:

EOF: "\0";
STRING: "\"" ( ~["\"","\\","\t","\n"] | "\\" ["\"","\\","t",n"])* "\"";
digit: ["0"-"9"];
int: -? ("0" | ["1"-"9"] digit*);
frac: "." digit+;
exp: ("e" | "E") ("+" | "-")? digit+;
NUMBER: int frac? exp?;
TRUE: "t" "r" "u" "e";
FALSE: "f" "a" "l" "s" "e";
NULL: "n" "u" "l" "l";

STRING also includes ascii characters.

The solution here is the submitted one. Assingment required to print the 
total of objects and arrays, and also the total of object members and 
array elements.

Feel free to contribute, PRs are welcome.
