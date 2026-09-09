#include <iostream>
using namespace std;


/*
    Liskov Substitution Principle (LSP)

    A derived class should be usable wherever its base class
    is expected without breaking the correctness of the program.
*/


/*
    Base class.

    Every Document must support:
        - open()
        - save()
*/
class Document {
public:

    virtual void save() = 0;
    virtual void open() = 0;

    // Important for polymorphic base classes
    virtual ~Document() = default;
};


/*
    PrintDocs extends Document.

    A PrintDocs must support:
        - open()
        - save()
        - print()
*/
class PrintDocs : public Document {
public:

    virtual void print() = 0;

    virtual ~PrintDocs() = default;
};


/*
    TextDocument is a Document.

    Therefore it must implement:
        - open()
        - save()
*/
class TextDocument : public Document {
public:

    void save() override {
        cout << "Text document is saved\n";
    }

    void open() override {
        cout << "Text document is opened\n";
    }
};


/*
    PdfDocument is a PrintDocs.

    Therefore it must implement:
        - open()
        - save()
        - print()
*/
class PdfDocument : public PrintDocs {
public:

    void save() override {
        cout << "PDF document is saved\n";
    }

    void open() override {
        cout << "PDF document is opened\n";
    }

    void print() override {
        cout << "PDF document is printed\n";
    }
};


int main() {

    /*
        LSP:

        TextDocument can replace Document.
    */
    TextDocument textDocument;

    Document* document = &textDocument;

    document->open();
    document->save();


    cout << "\n";


    /*
        LSP:

        PdfDocument can replace PrintDocs.
    */
    PdfDocument pdfDocument;

    PrintDocs* printableDocument = &pdfDocument;

    printableDocument->open();
    printableDocument->save();
    printableDocument->print();


    return 0;
}