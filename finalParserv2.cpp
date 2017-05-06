#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

// loads txt file to be checked, also finds declared identifiers
void loadFile(vector<string>& wordsToCheck,
	vector<string>& knownIdentifier) {

	ifstream inStream;
	inStream.open("finalv2.txt");
	int index;
	int progID = -1;

	if (inStream.is_open()) {
		string wordInFile;
		while (!inStream.eof()) {
			inStream >> wordInFile;
			wordsToCheck.push_back(wordInFile);
			if (wordInFile == "PROGRAM"){
				progID = wordsToCheck.size();
			}
			if(wordInFile == "INTEGER"){
				index = wordsToCheck.size();
			}
		}
	}
	inStream.close();
	if (progID == -1){
		//error code
	}
	else{
		knownIdentifier.push_back(wordsToCheck[progID]);
	}

	while (wordsToCheck[index] != ";"){
		if (wordsToCheck[index] == "," || wordsToCheck[index] == ":"){
			//skip
		}
		else{
			//is identifier add to knownIdentifier, check if next has , or ;
			knownIdentifier.push_back(wordsToCheck[index]);
		}
		index++;
	}
}

// checks whether words are a known identifier, special char, or a number
int wordChecker(string currentWord,
	vector<string> reservedWords,
	vector<string> special,
	vector<string> knownIdentifier) {

		for (int i = 0; i < reservedWords.size(); i++) {
			if (currentWord == reservedWords[i]) {
				return 1;
			}
		}

		for (int i = 0; i < special.size(); i++) {
			if (currentWord == special[i]) {
				return 2;
			}
		}

		bool isANumber = true;
		if(currentWord[0] == '+' || currentWord[0] == '-' || isdigit(currentWord[0])){
			for (int i = 1; i < currentWord.size(); i++){
				if (!isdigit(currentWord[i])) {
					isANumber = false;
				}
			}
		}
		else{
			isANumber = false;
		}
		if (isANumber) {
			return 3;
		}

		for (int i = 0; i < knownIdentifier.size(); i++) {
			if (currentWord == knownIdentifier[i]) {
				return 4;
			}
		}

		return 5;
}

// Rows for the table
int stateEvaluator(string c, bool &error){
	if (c == "<prog>"){
		return 0;
	}
	else if(c == "<identifier>"){
		return 1;
	}
	else if(c == "<more-id-digit>"){
		return 2;
	}
	else if(c == "<dec-list>"){
		return 3;
	}
	else if(c == "<dec>"){
		return 4;
	}
	else if(c == "<A>"){
		return 5;
	}
	else if(c == "<type>"){
		return 6;
	}
	else if(c == "<stat-list>"){
		return 7;
	}
	else if(c == "<B>"){
		return 8;
	}
	else if(c == "<stat>"){
		return 9;
	}
	else if(c == "<print>"){
		return 10;
	}
	else if(c == "<assign>"){
		return 11;
	}
	else if(c == "<expr>"){
		return 12;
	}
	else if(c == "<X>"){
		return 13;
	}
	else if(c == "<term>"){
		return 14;
	}
	else if(c == "<Y>"){
		return 15;
	}
	else if(c == "<factor>"){
		return 16;
	}
	else if(c == "<number>"){
		return 17;
	}
	else if(c == "<sign>"){
		return 18;
	}
	else if(c == "<more-digit>"){
		return 19;
	}
	else if(c == "<digit>"){
		return 20;
	}
	else if(c == "<id>"){
		return 21;
	}
	else{
		error = true;
		return -1;
	}
}

// Collumns for the table
int termEvaluator(string c, bool &error){
	if(c == "0"){
		return 0;
	}
	else if(c == "1"){
		return 1;
	}
	else if(c == "2"){
		return 2;
	}
	else if(c == "3"){
		return 3;
	}
	else if(c == "4"){
		return 4;
	}
	else if(c == "5"){
		return 5;
	}
	else if(c == "6"){
		return 6;
	}
	else if(c == "7"){
		return 7;
	}
	else if(c == "8"){
		return 8;
	}
	else if(c == "9"){
		return 9;
	}
	else if(c == "P"){
		return 10;
	}
	else if(c == "Q"){
		return 11;
	}
	else if(c == "R"){
		return 12;
	}
	else if(c == "S"){
		return 13;
	}
	else if(c == "PROGRAM"){
		return 14;
	}
	else if(c == "INTEGER"){
		return 15;
	}
	else if(c == "PRINT"){
		return 16;
	}
	else if(c == "BEGIN"){
		return 17;
	}
	else if(c == "END."){
		return 18;
	}
	else if(c == ";"){
		return 19;
	}
	else if(c == ":"){
		return 20;
	}
	else if(c == ","){
		return 21;
	}
	else if(c == "+"){
		return 22;
	}
	else if(c == "-"){
		return 23;
	}
	else if(c == "*"){
		return 24;
	}
	else if(c == "/"){
		return 25;
	}
	else if(c == "("){
		return 26;
	}
	else if(c == ")"){
		return 27;
	}
	else if(c == "="){
		return 28;
	}
	else{
		error = true;
		return -1;
	}

}

void printStack(stack<string> theStack){
	stack<string> newStack;
	while(!theStack.empty()){
		newStack.push(theStack.top());
		theStack.pop();
	}
	while(!newStack.empty()){
		cout << newStack.top() << " ";
		newStack.pop();
	}
	cout << endl;
}

// num corresponds to the numbers used in a spreadsheet.
// corresponding rule is then pushed in reverse order.
void stackPusher(bool &error, int num, stack<string> &theStack){
	if (error){
		//reject
	}
	else if (num == 99){
		//do nothing, read next on stack
	}
	else if (num == 0){
		theStack.push("0");
	}
	else if(num == 1){
		theStack.push("1");
	}
	else if(num == 2){
		theStack.push("2");
	}
	else if(num == 3){
		theStack.push("3");
	}
	else if(num == 4){
		theStack.push("4");
	}
	else if(num == 5){
		theStack.push("5");
	}
	else if(num == 6){
		theStack.push("6");
	}
	else if(num == 7){
		theStack.push("7");
	}
	else if(num == 8){
		theStack.push("8");
	}
	else if(num == 9){
		theStack.push("9");
	}
	else if(num == 10){
		theStack.push("P");
	}
	else if(num == 11){
		theStack.push("Q");
	}
	else if(num == 12){
		theStack.push("R");
	}
	else if(num == 13){
		theStack.push("S");
	}
	else if(num == 14){
		theStack.push("+");
	}
	else if(num == 15){
		theStack.push("-");
	}
	else if(num == 30){
		theStack.push("END.");
		theStack.push("<stat-list>");
		theStack.push("BEGIN");
		theStack.push("<dec-list>");
		theStack.push(";");
		theStack.push("<identifier>");
		theStack.push("PROGRAM");
	}
	else if(num == 31){
		theStack.push("<more-id-digit>");
		theStack.push("<id>");
	}
	else if(num == 32){
		theStack.push("<more-id-digit>");
		theStack.push("<digit>");
	}
	else if(num == 33){
		theStack.push("<more-id-digit>");
		theStack.push("<id>");
	}
	else if(num == 35){
		theStack.push(";");
		theStack.push("<dec>");
		theStack.push(":");
		theStack.push("<type>");
	}
	else if(num == 36){
		theStack.push("<A>");
		theStack.push("<identifier>");
	}
	else if(num == 37){
		theStack.push("<dec>");
		theStack.push(",");
	}
	else if(num == 39){
		theStack.push("INTEGER");
	}
	else if(num == 40){
		theStack.push("<B>");
		theStack.push("<stat>");
	}
	else if(num == 41){
		theStack.push("<stat-list>");
	}
	else if(num == 43){
		theStack.push("<print>");
	}
	else if(num == 44){
		theStack.push("<assign>");
	}
	else if(num == 45){
		theStack.push(";");
		theStack.push(")");
		theStack.push("<identifier>");
		theStack.push("(");
		theStack.push("PRINT");
	}
	else if(num == 46){
		theStack.push(";");
		theStack.push("<expr>");
		theStack.push("=");
		theStack.push("<identifier>");
	}
	else if(num == 47){
		theStack.push("<X>");
		theStack.push("<term>");
	}
	else if(num == 48){
		theStack.push("<X>");
		theStack.push("<term>");
		theStack.push("+");
	}
	else if(num == 49){
		theStack.push("<X>");
		theStack.push("<term>");
		theStack.push("-");
	}
	else if(num == 51){
		theStack.push("<Y>");
		theStack.push("<factor>");
	}
	else if(num == 52){
		theStack.push("<Y>");
		theStack.push("<factor>");
		theStack.push("*");
	}
	else if(num == 53){
		theStack.push("<Y>");
		theStack.push("<factor>");
		theStack.push("/");
	}
	else if(num == 55){
		theStack.push("<identifier>");
	}
	else if(num == 56){
		theStack.push("<number>");
	}
	else if(num == 57){
		theStack.push(")");
		theStack.push("<expr>");
		theStack.push("(");
	}
	else if(num == 58){
		theStack.push("<more-digit>");
		theStack.push("<digit>");
		theStack.push("<sign>");
	}
	else if(num == 60){
		theStack.push("<more-digit>");
		theStack.push("<digit>");
	}
	else if(num == 100){
		error = true;
		printStack(theStack);
	}
}

// issues error codes
void eCodeCheck(int eCode){
	if (eCode == 1){
		cout << "PROGRAM is expected..." << endl; 
	}
	else if (eCode == 2){
		cout << "BEGIN is expected..." << endl;
	}
	else if (eCode == 3){
		cout << "END. is expected..." << endl;
	}
	else if (eCode == 4){
		cout << "INTEGER is expected..." << endl;
	}
	else if (eCode == 5){
		cout << "Unknown identifier..." << endl;
	}
	else if (eCode == 6){
		cout << "';' is missing..." << endl;
	}
	else if (eCode == 7){
		cout << "',' is missing..." << endl;
	}
	else if (eCode == 8){
		cout << "'.' is missing..." << endl;
	}
	else if (eCode == 9){
		cout << "'(' is missing..." << endl;
	}
	else if (eCode == 10){
		cout << "')' is missing..." << endl;
	}
	else if (eCode == 11){
		cout << "PRINT is expected..." << endl;
	}
	else if (eCode == 12){
		cout << "Illegal expression..." << endl;
	}
}

// This checks the stack to find out why code was rejected
// calls eCodeCheck to issue error to terminal
void stackCheck(int row, int col, stack<string> theStack){
	stack<string> tmp = theStack;
	while(!tmp.empty()){
		if(tmp.top() == "<prog>"){
			eCodeCheck(1);
			break;
		}
		else if(tmp.top() == ";"){
			eCodeCheck(6);
			break;
		}
		else if (tmp.top() == "<dec-list>"){
			eCodeCheck(4);
			break;
		}
		else if (tmp.top() == "<A>"){
			eCodeCheck(7);
			break;
		}
		else if (tmp.top() == "<stat-list>"){
			eCodeCheck(2);
			break;
		}
		else if(tmp.top() == "<B>"){
			eCodeCheck(6);
			break;
		}
		tmp.pop();
	}
}

int main(){
	/*
	99 = lambda, 100 = error, 10 = P, 11 = Q, 12 = R, 13 = S, 14 = +, 15 = -, see excel for the rest
	*/
	int table[22][29]={										   //15
		{100,100,100,100,100,100,100,100,100,100,100,100,100,100,30 ,100,100,100,100,100,100,100,100,100,100,100,100,100,100},
		{100,100,100,100,100,100,100,100,100,100, 31, 31, 31, 31,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100},
		{ 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 33, 33, 33, 33,100,100,100,100,100, 99,100, 99, 99, 99, 99, 99,100, 99, 99},
		{100,100,100,100,100,100,100,100,100,100,100,100,100,100,100, 35,100,100,100,100,100,100,100,100,100,100,100,100,100},
		{100,100,100,100,100,100,100,100,100,100, 36, 36, 36, 36,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100},
		{100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100, 99,100, 37,100,100,100,100,100,100,100},
		{100,100,100,100,100,100,100,100,100,100,100,100,100,100,100, 39,100,100,100,100,100,100,100,100,100,100,100,100,100},
		{100,100,100,100,100,100,100,100,100,100, 40, 40, 40, 40,100,100, 40,100,100,100,100,100,100,100,100,100,100,100,100},
		{100,100,100,100,100,100,100,100,100,100, 41, 41, 41, 41,100,100, 41,100, 99,100,100,100,100,100,100,100,100,100,100},
		{100,100,100,100,100,100,100,100,100,100, 44, 44, 44, 44,100,100, 43,100,100,100,100,100,100,100,100,100,100,100,100},
		{100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100, 45,100,100,100,100,100,100,100,100,100,100,100,100},
		{100,100,100,100,100,100,100,100,100,100, 46, 46, 46, 46,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100},
		{ 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47,100,100,100,100,100,100,100,100, 47, 47,100,100, 47,100,100},
		{100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100, 99,100,100, 48, 49,100,100,100, 99,100},
		{ 51, 51, 51, 51, 51, 51, 51, 51, 51, 51, 51, 51, 51, 51,100,100,100,100,100,100,100,100, 51, 51,100,100, 51,100,100},
		{100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100, 99,100,100, 99, 99, 52, 53,100, 99,100},
		{ 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 55, 55, 55, 55,100,100,100,100,100,100,100,100, 56, 56,100,100, 57,100,100},
		{ 58, 58, 58, 58, 58, 58, 58, 58, 58, 58,100,100,100,100,100,100,100,100,100,100,100,100, 58, 58,100,100,100,100,100},
		{ 99, 99, 99, 99, 99, 99, 99, 99, 99, 99,100,100,100,100,100,100,100,100,100,100,100,100, 14, 15,100,100,100,100,100},
		{ 60, 60, 60, 60, 60, 60, 60, 60, 60, 60,100,100,100,100,100,100,100,100,100, 99,100,100, 99, 99, 99, 99,100, 99, 99},
		{  0,  1,  2,  3,  4,  5,  6,  7,  8,  9,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100},
		{100,100,100,100,100,100,100,100,100,100, 10, 11, 12, 13,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100}
	};

	vector<string> wordsInStatement;
	vector<string> tokensInStatement;
	vector<string> reservedWords = {"PROGRAM", "BEGIN", "INTEGER", "PRINT", "END."};
	vector<string> special = {";", ":", ",", "+", "-", "*", "/", "(", ")", "="};
	vector<string> followOfIdentifier = {";",",","=",")","*","/","+","-"};
	vector<string> knownIdentifier;
	stack<string> parentheses;
	string statement;
	int eCode, col, row;
	bool error = false;
	loadFile(wordsInStatement,knownIdentifier);

	//identifies invalid identifiers and creates tokens of all non reserved words
	for(int i = 0; i < wordsInStatement.size(); i++){
		eCode = wordChecker(wordsInStatement[i],reservedWords,special,knownIdentifier);
		bool reserved = false;
		if(eCode == 5){
			eCodeCheck(eCode);
			//error = true;
			break;
		}
		for(int j = 0; j < reservedWords.size(); j++){
			if(wordsInStatement[i] == reservedWords[j]){
				tokensInStatement.push_back(wordsInStatement[i]);
				reserved = true;
			}
		}
		for(int j = 0; j < special.size(); j++){
			if(wordsInStatement[i] == special[j]){
				tokensInStatement.push_back(wordsInStatement[i]);
				reserved = true;
				if (wordsInStatement[i] == "("){
					parentheses.push("(");
				}
				if (wordsInStatement[i] == ")"){
					if (parentheses.empty()){
						//error no corresponding "("
						error = true;
						eCodeCheck(9);
					}
					else{
						parentheses.pop();
					}
				}
			}
		}
		//not special or reserved so should be identifier or number
		if (!reserved){
			for(int j = 0; j < wordsInStatement[i].length(); j++){
				tokensInStatement.push_back(string(1,wordsInStatement[i][j]));
			}
			//pushes a delimiter to identify end of id or number
			tokensInStatement.push_back("|");
		}
	}
	if(!parentheses.empty()){
		//error no corresponding ")"
		error = true;
		eCodeCheck(10);
	}
	stack<string> theStack;
	if(!error){
		theStack.push("<prog>");
		printStack(theStack);
	}

	//parsing begins here with each token in the statement
	for (int i = 0; i < tokensInStatement.size(); i++){
		if(error){
			break;
		}
		//this marks the end of an identifier or number
		//use follow to make sure the correct symbol comes after
		if(tokensInStatement[i] == "|"){
			bool followError = true;
			for (int j = 0; j < followOfIdentifier.size(); j++){
				if (tokensInStatement[i+1] == followOfIdentifier[j]){
					//skip the delimiter, the parser will check if the right follow is there
					i++;
					followError = false;
					break;
				}
			}
			if(followError){
				//figure out the error based on the stack?
				error = true;
				break;
			}
		}

		while (!theStack.empty() && theStack.top() != tokensInStatement[i] && !error){
			string current = theStack.top();
			theStack.pop();
			// row and collumn saved for exact table location of error
			row = stateEvaluator(current,error);
			col = termEvaluator(tokensInStatement[i],error);
			int num = table[row][col];
			stackPusher(error,num,theStack);
			printStack(theStack);
		}
		if(tokensInStatement[i] == theStack.top() && !theStack.empty()){
			theStack.pop();
		}
	}
	if (error || !theStack.empty()){
		cout << "Rejected" << endl;
		//call stackCheck to issue error
		stackCheck(row,col,theStack);
	}
	else {
		cout << "Accepted" << endl;
	}
	return 0;
}