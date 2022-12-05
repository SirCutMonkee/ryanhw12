#include <iostream>         // for the input/output
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
   GPIO_VALUE state = HIGH;
   gpio46.setDirection(INPUT);
 
   // generate the form but use states that are set in the submitted form
   cout << HTTPHTMLHeader() << endl;       // Generate the HTML form
   cout << html() << head() << title("Reading a Pushbutton") << head() << endl;
   cout << body() << h1("CPE 422/522 Reading a Pushbutton as a Digital Input") << endl;
   cout << h1("Reading a Pushbutton on gpio46 via Web Browser") << endl;
   cout << "<form action=\"/cgi-bin/read_button.cgi\" method=\"POST\">\n";
   cout << "<input type=\"submit\" value=\"Read Button\" /></div>";
   cout << "<br>";
   cout << "</div></form>";
   cout << h1("Pushbutton State") << endl;

   // Read button and output state o HTML
   state = gpio46.getValue();             
   if(state == HIGH) cout << h2("Button Not Pressed") << endl;
   else cout << h2("Button Pressed") << endl;
   cout << "<br>" << endl;
   cout << body() << html();
   return 0;
}
