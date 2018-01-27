#include <Printer.h>
#include <PrinterI.h>
#include <string>

using namespace std;

PrinterI::PrinterI(){

}

void PrinterI::printString(const string& s, const Ice::Current& c){ 
	cout << changeString(s, c) << endl;
}

string PrinterI::changeString(const string& msg, const Ice::Current&){
	string message = msg;
	int length = message.size();
	swap(message[length/2], message[((length/2) - 1)]);
	return message;
}
