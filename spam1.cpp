#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void relativespam(float counter, float count)
{

    fstream email("email.txt", ios::in | ios::app);
    fstream result("result.txt", ios::out | ios::app);

    float result2 = (counter / count * 1.00) * 100;

    if (result2 <= 15)
    {

        result << result2 << "% of the email are spam keywords, so the email is NOT SPAM" << endl;
    }

    else if (result2 > 15 && result2 < 50)
    {

        result << result2 << "% of the email are spam keywords, so the email is MAYBE SPAM" << endl;
    }

    else
    {

        result << result2 << "% of the email are spam keywords, so the email is DEFINITELY SPAM" << endl;
    }
    result << endl;
}

int main()
{

    string emailmess, keycheck, punctmark, before;
    int totalscore = 0, i, j;
    float spamcounter = 0; // 'spamcounter' will count how many spam words there are, will be used later when calculating relative spam

    fstream email("email.txt", ios::in | ios::app);
    fstream result("result.txt", ios::out | ios::app);

    vector<string> keywords;
    keywords.push_back("$");
    keywords.push_back("earn per week");
    keywords.push_back("double your");
    keywords.push_back("income in one week");
    keywords.push_back("trial that lasts forever");
    keywords.push_back("opportunity");
    keywords.push_back("income");
    keywords.push_back("cash");
    keywords.push_back("month free trial");
    keywords.push_back("your love life");

    vector<int> score;
    score.push_back(10);
    score.push_back(20);
    score.push_back(20);
    score.push_back(15);
    score.push_back(30);
    score.push_back(10);
    score.push_back(10);
    score.push_back(20);
    score.push_back(15);
    score.push_back(25);

    int wordcount = 0;

    while (getline(email, emailmess))
    {

        auto tr1 = emailmess.begin();
        auto tr2 = emailmess.end();

        transform(tr1, tr2, emailmess.begin(), ::tolower);

        for (i = 0; i < keywords.size(); i++)
        { //i goes from 0-9

            for (j = 0; j < emailmess.length(); j++)
            { //j goes to the length of the email

                keycheck = emailmess.substr(j, keywords[i].length()); // 'keyckeck' is a substring that checks the keywords

                if (j + keywords[i].length() < emailmess.length())
                { //this statement will be true as long as we don't go over length of the text

                    punctmark = emailmess.substr(j + keywords[i].length(), 1); // 'punctmark' is a substring that includes the punctuation mark (if it exists)
                }

                if (j > 0)
                {

                    before = emailmess.substr(j - 1, 1); //'before' is a substring that includes one space before the keyword
                }

                else if ((keycheck == keywords[i]) && (punctmark == "." || punctmark == " " || punctmark == "!" || punctmark == "?" || punctmark == ","))
                {

                    totalscore = score[i] + totalscore;
                    spamcounter = spamcounter + 1;
                }

                if ((keycheck == keywords[i]) && (j > 0) && (punctmark == "." || punctmark == " " || punctmark == "!" || punctmark == "?" || punctmark == ","))
                {

                    before = emailmess.substr(j - 1, 1);

                    if (before == " " || before == "!" || before == "?" || before == "," || before == ".")
                    {
                        totalscore = score[i] + totalscore;
                        spamcounter = spamcounter + 1;
                    }
                }

                else if ((keycheck == keywords[i]) && (j > 0))
                {

                    before = emailmess.substr(j - 1, 1);

                    if (before == " " || before == "." || before == "?" || before == "," || before == " " || before == "!")
                    {
                        totalscore = score[i] + totalscore;
                        spamcounter = spamcounter + 1;
                    }
                }
            }
        }

        emailmess.erase(remove(emailmess.begin(), emailmess.end(), '.'), emailmess.end());
        emailmess.erase(remove(emailmess.begin(), emailmess.end(), ','), emailmess.end());
        emailmess.erase(remove(emailmess.begin(), emailmess.end(), '!'), emailmess.end());
        emailmess.erase(remove(emailmess.begin(), emailmess.end(), '?'), emailmess.end());
        emailmess.erase(remove(emailmess.begin(), emailmess.end(), ':'), emailmess.end());

        if (emailmess[emailmess.length() - 1] != ' ')
        { //because when the line ends and if there is no space after the last word, the first word of the next line will blend with it and they will be counted as one word
            wordcount++;
        }

        for (int m = 0; m <= emailmess.length(); m++)
        {
            cout << emailmess[m];
            if (emailmess[m] == ' ')
            {
                wordcount++;
            }
        }
    }

    result << "There are " << wordcount << " words in the email "
           << " and " << spamcounter << " of them are the spam keywords." << endl;
    result << endl;

    if (totalscore <= 10)
    {
        result << "The score is:" << totalscore << " "
               << " NOT SPAM" << endl;
    }
    else if (totalscore < 50)
    {
        result << "The score is:" << totalscore << " "
               << " MAYBE SPAM" << endl;
    }
    else if (totalscore >= 50)
    {
        result << "The score is: " << totalscore << " "
               << " DEFINITELY SPAM" << endl;
    }

    result << endl;

    relativespam(spamcounter, wordcount);

    email.close();
    result.close();
    return 0;
}
