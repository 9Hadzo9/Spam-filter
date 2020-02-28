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

bool fuzziness1(string keyword, string keycheck)
{ //cash -> cesh

    int counter = 0;

    for (int i = 0; i < keyword.length(); i++)
    {

        if (keyword.at(i) != keycheck.at(i))
        {
            counter++;
        }
    }

    if (counter <= 1)
    {
        return true;
    }

    else
    {
        return false;
    }
}

bool fuzziness2(string keyword, string keycheck) // cash -> caash
{
    int counter = 0;

    for (int i = 0; i < keyword.length(); i++)
    {
        if (keycheck.at(i) != keyword.at(i))
        {
            keycheck.erase(i, 1);

            if (keycheck == keyword)
            {
                return true;
            }
            else if (keycheck != keyword)
            {
                return false;
            }
        }
    }
    return false;
}

bool fuzziness3(string keyword, string keycheck)
{ // cash -> csh

    for (int i = 0; keycheck[i] != 0; i++)
    {

        if (keycheck.at(i) != keyword.at(i))
        {
            keyword.erase(i, 1);

            if (keycheck == keyword)
            {
                return true;
            }

            else
            {
                return false;
            }
        }
    }
}

int main()
{

    string emailmess, keycheck, punctmark, before;
    string fuzziness1check;
    string fuzziness2check;
    string fuzziness3check;
    int wordcount = 0;
    int totalscore = 0, i, j;
    float spamcounter = 0; // 'spamcounter' will count how many spam words there are, will be used later when calculating relative spam
    int x, y;
    string before2;

    fstream email("email.txt", ios::in | ios::app);
    fstream result("result.txt", ios::out | ios::app);

    vector<string> keywords;

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
    score.push_back(20);
    score.push_back(20);
    score.push_back(15);
    score.push_back(30);
    score.push_back(10);
    score.push_back(10);
    score.push_back(20);
    score.push_back(15);
    score.push_back(25);

    while (getline(email, emailmess))
    {

        auto tr1 = emailmess.begin();
        auto tr2 = emailmess.end();

        transform(tr1, tr2, emailmess.begin(), ::tolower);

        auto tr3 = emailmess.begin();
        auto tr4 = emailmess.end();

        transform(tr3, tr4, emailmess.begin(), ::tolower);

        emailmess.erase(remove(emailmess.begin(), emailmess.end(), '.'), emailmess.end());
        emailmess.erase(remove(emailmess.begin(), emailmess.end(), ','), emailmess.end());
        emailmess.erase(remove(emailmess.begin(), emailmess.end(), '!'), emailmess.end());
        emailmess.erase(remove(emailmess.begin(), emailmess.end(), '?'), emailmess.end());
        emailmess.erase(remove(emailmess.begin(), emailmess.end(), ':'), emailmess.end());

        if (emailmess[emailmess.length() - 1] != ' ')
        { //because when the line ends and if there is no space after the last word, the first word of the next line will blend with it and they will be counted as one word
            wordcount++;
        }
        for (int m = 0; m < emailmess.length(); m++)
        {
            if (emailmess[m] == ' ')
            {
                wordcount++;
            }
        }

        for (i = 0; i < keywords.size(); i++)
        {
            for (y = 0; y < emailmess.length(); y++)
            {

                if (y + keywords[i].length() + 1 <= emailmess.length())
                {

                    fuzziness1check = emailmess.substr(y, keywords[i].length());
                    fuzziness2check = emailmess.substr(y, keywords[i].length() + 1);
                    fuzziness3check = emailmess.substr(y, keywords[i].length() - 1);

                    bool check = fuzziness1(keywords[i], fuzziness1check);
                    bool check2 = fuzziness2(keywords[i], fuzziness2check);
                    bool check3 = fuzziness3(keywords[i], fuzziness3check);

                    if (check)
                    {
                        totalscore = totalscore + score[i];
                        spamcounter = spamcounter + 1;

                        emailmess.erase(y, fuzziness1check.length());
                    }

                    if (check2)
                    {
                        totalscore = totalscore + score[i];
                        spamcounter = spamcounter + 1;

                        emailmess.erase(y, fuzziness2check.length());
                    }

                    else if (check3)
                    {
                        totalscore = totalscore + score[i];
                        spamcounter = spamcounter + 1;

                        emailmess.erase(y, fuzziness3check.length());
                    }
                }
            }
        }

        for (int s = 0; s < emailmess.length() - 1; s++)
        {
            if (s > 0)
            {
                before = emailmess.substr(s - 1, 1);

                if (emailmess.at(s) == '$')
                {
                    totalscore = totalscore + 10;
                    spamcounter = spamcounter + 1;
                }
            }
            else if ((emailmess.at(s) == '$') && (before == " "))
            {
                totalscore = totalscore + 10;
                spamcounter = spamcounter + 1;
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
