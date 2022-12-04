#include <iostream>         // for the input/output
#include <stdlib.h>         // for the getenv call
#include <sys/sysinfo.h>    // for the system uptime call
#include <cgicc/Cgicc.h>    // the cgicc headers
#include <cgicc/CgiDefs.h>
#include <cgicc/HTTPHTMLHeader.h>
#include <cgicc/HTMLClasses.h>
#include "GPIO.h"
#define BUTTON_GPIO "/sys/class/gpio/gpio46/"
using namespace std;
using namespace cgicc;
using namespace exploringBB;

int main(){
   Cgicc form;                      // the CGI form object
   GPIO gpio46(46);
   string cmd;                      // the read button command
   GPIO_VALUE state = HIGH;
   gpio46.setDirection(INPUT);

   // get the state of the form that was submitted - script calls itself
   bool isStatus = form.queryCheckbox("status");
   form_iterator it = form.getElement("cmd");  // the radio command
   if (it == form.getElements().end() || it->getValue()==""){
      cmd = "read";                     // if it is invalid use "off"
   }
   else { cmd = it->getValue(); }      // otherwise use submitted value
   char *value = getenv("REMOTE_ADDR");    // The remote IP address
 
   // generate the form but use states that are set in the submitted form
   cout << HTTPHTMLHeader() << endl;       // Generate the HTML form
   cout << html() << head() << title("CPE 422/522 Reading a Pushbutton as a Digital Input") << head() << endl;
   cout << body() << h1("CPE 422/522 Reading a Pushbutton as a Digital Input") 
    << h1("Reading a Pushbutton on gpio46 via Web Browser") << endl;
   cout << "<form action=\"/usr/lib/cgi-bin/read_button.cgi\" method=\"POST\">\n";
   cout << "<input type=\"submit\" name=\"cmd\" value=\"Read Button\" />" << "</form>";
   cout << h1("Pushbutton State") << endl;

   // process the form data to change the LED state
   if (cmd=="read") state = gpio46.getValue();             
   else cout << "<div> Invalid command! </div>";        // not possible
   if(state == HIGH){
      cout << h2("Button Not Pressed") << endl;
   }
   else{
      cout << h2("Pushbutton Pressed") << endl;
   }
   cout << body() << html();
   return 0;
}
