#ifndef PRINTER_I_H
#define PRINTER_I_H
#include <Ice/Ice.h>
#include <Printer.h>

using namespace std;
using namespace Demo;

class PrinterI : public Printer {
	public:
		PrinterI();
		virtual void printString(const string& s, const Ice::Current&);
		virtual string changeString(const string& msg, const Ice::Current&);
};

#endif
