
*compilation*
compile with c++17 standard (-std=c++17)

"compile example"
g++ -std=c++17 parseExpr.cpp mainParsing.cpp tokenizer.cpp lexer.cpp getConsoleArguments.cpp getProgramInputStream.cpp typecheckers.cpp tree.impl.cpp codeGeneration.cpp -o parse

*syntax of parser*
./parse --exp ["expression"]
or
./parse --file ["FILEPATH"] 

*options*
--output -file ["FILEPATH"] : sends the output in the mentioned file
	ex. 
	./parse --console " var g = 3 ; func h = a/(6-7) ;" --output -file "files/output.txt"
	or
	./parse --file "files/input.txt" --output -file "files/output.txt"
	

default : prints output in the console
