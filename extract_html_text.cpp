#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

string readFile(string file){
  string a, b;
  string output = "";
/*check if the file opened correctly*/
  ifstream in(file);
  if(!in.is_open()){
    cout << "Could not open the file" << endl;
    return output;
  }

  ostringstream oss;

  while(getline(in, a)){
      istringstream cc(a);
      if(cc >> b)
         output += cc.str();
      output += "\n";
/* ^ will add an extra line at the end,
will not matter since the other functions will ignore that space
*/
  }
  in.close();//closing file
  return output;
}

string extractParagraphs(string html){

  string output = "";
  string f_output = "";
/*
Using the position of each char on the string I created a for loop
that loops to every char on the string. If a <p> is found everything
is stored into the output. If a "</p>" is found the inner loop is broken

 */

  for(int i = 0; i < html.size(); i++){
    if((html[i] == '<') && (html[i + 1] == 'p') && (html[i + 2] == '>')){
      for(int j = i; j < html.size(); j++){
          output += html[j+3];
          if((html[j] == '<') && (html[j + 1] == '/') && (html[j + 2] == 'p')
              && (html[j + 3] == '>')){
            i = j + 4;
            output += "\n\n";
            break;
          }
      }
    }
  }
/* for larger html files my function will sometimes will include some "</p>",
I created this extra forloop to get rid of them"
*/
  for(int i = 0; i < output.size(); i++){
    if( (output[i] == '<') && (output[i + 1] == '/') && (output[i + 2] == 'p')
        && (output[i + 3] == '>') )i += 4;

      f_output += output[i];
  }

  return f_output;
}

string removeTags(string htmltext){

  string output = "";
  int flag = 0;
/*
Using the position of each char on the string array
to check if its on the HTML tag range.
if the char is not one of the tags, it is added to
the output
*/
  for(int i = 0; i < htmltext.size(); i++){
    if(htmltext[i] == '>')
      flag = 0;
    if(htmltext[i] == '<')
      flag = 1;
    if(htmltext[i] != '>'&& !flag)
      output += htmltext[i];
  }

  return output;
}

int main(){
//  input your file here!
    string file_name = "a.html";
    string output = "";

    output = removeTags(extractParagraphs(readFile(file_name)));
    cout << output << endl;

    return 0;
}
