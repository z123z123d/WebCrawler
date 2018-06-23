#include <bits/stdc++.h>
#include <direct.h>
#include <io.h>
#include "DoubanCrawler.h"
using namespace std;

#define DEBUG

#define SEARCH(content, str) regex_search (content, matchstring, regex(str))
#define SEARCH_CHK(content, str) if (SEARCH(content, str) == false) return false

void DoubanCrawler:: addTargetData (const DataType &datatype) {
    TargetDataList.push_back (datatype);
}

void DoubanCrawler:: addObject (BaseObject* object) {
    ObjectList.push_back (static_cast<DoubanMovieObject*>(object));
}

void DoubanCrawler:: readFile (const string &HTML, string &str) {
    ifstream fin (HTML.c_str());
    for (char c; c = fin.get(), c != EOF; str.push_back (c));
    fin.close();
}

bool DoubanCrawler:: getData (string content, BaseData *data) {
    smatch matchstring;

    //cout << data-> getType() << ":" << endl;
    switch (data-> getType()) {
        case _name:
            SEARCH_CHK(content, "<span property=\"v:itemreviewed\">([^<]*)</span>");
            if (matchstring[1].str().length() == 0) return false;
            data-> setString (matchstring[1]);
            if (SEARCH(content, "又名.*")) {
                content = matchstring.str();
                SEARCH_CHK(content, "</span> ([^<]*)<br/>");
                data-> setString (matchstring[1].str());
            }
            return true;

        case _date:
            SEARCH_CHK(content, "<span class=\"pl\">上映日期.*");
            content = matchstring.str();
            while (SEARCH (content, ">([^<]*)</span>")) {
                data->setString(matchstring[1].str());
                content = matchstring.suffix().str();
            }
            return true;

        case _director:
            SEARCH_CHK(content, "<div id=\"info\">");
            content = matchstring.suffix().str();
            SEARCH_CHK(content, "<span class='pl'>导演</span>.*<a .*>(.*)</a>");
            data-> setString (matchstring[1]);
            return true;

        case _writers:
            SEARCH_CHK(content, "<div id=\"info\">");
            content = matchstring.suffix().str();
            SEARCH_CHK(content, "<span class='pl'>编剧</span>.*<a .*>(.*)</a>");
            data-> setString (matchstring[1]);
            return true;

        case _actors:
            SEARCH_CHK(content, "<span class='pl'>主演</span>(.*)\n");
            content = matchstring[1];
            while (SEARCH (content, "<a[^<]*>([^<]*)</a>")) {
                data-> setString(matchstring[1].str());
                content = matchstring.suffix().str();
            }
            return true;

        case _labels:
            SEARCH_CHK(content, "<span class=\"pl\">类型.*");
            content = matchstring.str();
            while (SEARCH (content, ">([\u4e00-\u9fa5]*)</span>")) {
                data-> setString (matchstring[1].str());
                content = matchstring.suffix().str();
            }
            return true;

        case _country:
            SEARCH_CHK(content, "<span class=\"pl\">制片国家/地区.*");
            content = matchstring.str();
            SEARCH_CHK(content, "</span> ([^<]*)<br/>");
            data-> setString (matchstring[1].str());
            return true;

        case _language:
            SEARCH_CHK(content, "<span class=\"pl\">语言.*");
            content = matchstring.str();
            SEARCH_CHK(content, "</span> ([^<]*)<br/>");
            data-> setString (matchstring[1].str());
            return true;

        case _runtime:
            SEARCH_CHK(content, "<span class=\"pl\">片长.*");
            content = matchstring.str();
            SEARCH_CHK(content, ">(\r|[0-9].*)</span>");
            data-> setString (matchstring[1].str());
            return true;

        case _producer:
            return false;

        case _earnings:
            return false;

        case _rating: {
            SEARCH_CHK(content, "<[^<]*rating_num[^<]*>([^<]*)</strong>");
            double rating_double = 0;
            string rating_string (matchstring[1].str());
            if (rating_string.length()) {
                stringstream tmp;
                tmp << rating_string;
                tmp >> rating_double;
            }
            else
                rating_double = -1;
            data->setDouble(rating_double);
            return true;
        }

        case _awards:
            while (SEARCH(content, "<ul class=\"award\">")) {
                content = matchstring.suffix().str();
                SEARCH_CHK(content, "<li>[^<]*<a[^<]*>([^<]*)</a>[^<]*</li>");
                string tmp = matchstring[1].str();
                content = matchstring.suffix().str();
                SEARCH_CHK(content, "<li>([^<]*)</li>");
                tmp = tmp + ":" + matchstring[1].str();
                data-> setString(tmp);
                content = matchstring.suffix().str();
            }
            return true;

        case _reviews:
            static map<int, bool> visited_review;
            while (SEARCH (content, "https://movie.douban.com/review/([0-9]+)")) {
                int id = atoi (matchstring[1].str().c_str());
                if (visited_review[id] == true) {
                    content = matchstring.suffix().str();
                    continue;
                }
                visited_review[id] = true;

                string content_, tmp_file, ans;
                catcher.saveFile(matchstring.str(), tmp_file = "tmp.html");
                readFile(tmp_file, content_);

                SEARCH(content_, "<meta name=\"description\" content=\"([^<]*)\" />");
                ans = matchstring[1].str();

                SEARCH(content_, "data-author=\"(.*)\"");
                if (matchstring[1].str().length())
                    ans = ans + "\n" + matchstring[1].str();
                content_ = matchstring.suffix().str();

                while (SEARCH(content_, "<p>([^<]*)</p>")) {
                    if (matchstring[1].str().length() == 0) break;
                    ans = ans + "\n" + matchstring[1].str();
                    content_ = matchstring.suffix().str();
                }
                data-> setString(ans + "\n");
                content = matchstring.suffix().str();
                system ("rm tmp.html");
            }
            return true;

        case _photos:
            while (SEARCH(content, "<a href=\"https://movie.douban.com/photos/photo/([0-9]+)/\"><img src=\"((?:https?://)?.*p[0-9]*.jpg)\" alt=\"图片\" />")) {
                data-> setString (matchstring[2].str());
                content = matchstring.suffix().str();
            }
            return true;
    }
}

void DoubanCrawler:: init() {
    ifstream fin ("crawler-configuration.txt");
    for (int i = 0; i < 15; i++) {
        int x = 1;
#ifdef DEBUG
        fin >> x;
#endif
        if (x)
            addTargetData(DataType (i));
    }
} //

ofstream ouf ("test.out"); //

void DoubanCrawler:: downloadPics (DoubanMovieObject *object) {
    vector<string> PhotoList = object-> getData(_photos)-> getVectorString();
    string name = object-> getData(_name)-> getVectorString()[0];
    for (auto it : PhotoList) {
        cout << "photo: " << it << endl;
        string content(it);
        smatch matchstring;
        catcher.saveFile(it, "pic/" + matchstring[1].str(), true);
    }
}

DoubanMovieObject* DoubanCrawler:: scanPage (const string& HTML) {
    string content;
    readFile (HTML, content);

    DoubanMovieObject *object = new DoubanMovieObject;
    BaseData *data;

    for (auto it : DoubanMovieDataList) {
        data = DoubanMovieObject:: newData (it);
        getData (content, data);
        object-> addData(data);
#ifdef DEBUG
        data-> printData(ouf), ouf << endl; //
#endif
    }
#ifdef DEBUG
    ouf << endl; //
#endif

    fprintf (stderr, "Scanned: %s\n", (object->getData(_name)->getVectorString())[0]); //
    return object;
}

void DoubanCrawler:: work() {
    ofstream _ouf ("con");
    string StartUrl = "https://movie.douban.com/";
    vector<string> QUrl {StartUrl};
    map<int, bool> visited;

    system (("md " + string("pic")).c_str());
    srand ((unsigned) time (NULL));
    for (int i = 0; i < QUrl.size() && i <= 10; i++) {
        clock_t delay = (rand() % 100 + 100) / 400 * CLOCKS_PER_SEC, start = clock();

        smatch matchstring;
        string Url = QUrl[i], content;
        string HTML = "page" + to_string(i) + ".html";
        catcher.saveFile (Url, HTML, false);
        readFile (HTML, content);

        while (SEARCH(content, "https://movie.douban.com/subject/([0-9]+)(?:[^0-9])")) {
            int id = atoi (matchstring[1].str().c_str());
            if (! visited[id]) {
                visited[id] = 1;
                QUrl.push_back(matchstring.str());
            }
            content = matchstring.suffix().str();
        }

        if (i) {
            _ouf << i << endl;
            DoubanMovieObject *object = scanPage (HTML);
            SEARCH(Url, "subject/([0-9]+)[^0-9]?");
            downloadPics (object);
            addObject (object);
        }

        while (clock() - start < delay);
    }
    _ouf << QUrl.size() << endl;
    for (int i = 0; i < QUrl.size(); i++)
        _ouf << QUrl[i] << endl;
}
