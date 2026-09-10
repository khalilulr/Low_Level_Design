#include<bits/stdc++.h>
using namespace std;

class Email{
    string subject;
    string body;
    string cc;
    string bcc;
    string attachment;

    public:
        Email(
            string subject,
            string body,
            string cc,
            string bcc,
            string attachment
            ):  subject(subject),
                body(body),
                cc(cc),
                bcc(bcc),
                attachment(attachment){}

        void showEmail(){
            cout << "Subject: " << subject << endl;
            cout << "Body: " << body << endl;
            cout << "Attachment: " << attachment << endl;
            cout << "CC: " << cc << endl;
            cout << "BCC: " << bcc << endl;
        }

};



class EmailBuilder{
    private:
        string subject;
        string body;
        string cc;
        string bcc;
        string attachment;

    public:
        EmailBuilder& setSubject(string subject){
            this->subject=subject;
            return *this;
        }

        EmailBuilder& setBody(string body){
            this->body=body;
            return *this;
        }

        EmailBuilder& setCC(string cc){
            this->cc=cc;
            return *this;
        }

        EmailBuilder& setBCC(string bcc){
            this->bcc=bcc;
            return *this;
        }

        EmailBuilder& setAttachment(string attachment){
            this->attachment=attachment;
            return *this;
        }


        Email build(){
            return Email(subject,body,cc,bcc,attachment);
        }
};

int main(){
    Email email=EmailBuilder()
                .setSubject("This is subject")
                .setBody("This is body")
                .setAttachment("This is attachment")
                .build();

    email.showEmail();
}