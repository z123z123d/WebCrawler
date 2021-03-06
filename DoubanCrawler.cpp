#include <bits/stdc++.h>
#include <direct.h>
#include <io.h>
#include "DoubanCrawler.h"
using namespace std;

#undef DEBUG

#define SEARCH(A, B) regex_search (A, matchstring, regex(B))
#define SEARCH_CHK(A, B) if (SEARCH(A, B) == false) return false

void DoubanCrawler:: addTargetData (const DataType &datatype) {
    TargetDataList.push_back (datatype);
}

void DoubanCrawler:: addObject (BaseObject* object) {
    ObjectList.push_back (static_cast<BaseObject*>(object));
}

void DoubanCrawler:: readFile (const string &HTML, string &str) {
    ifstream fin (HTML.c_str());
    for (char c; c = fin.get(), c != EOF; str.push_back (c));
    fin.close();
}

vector<BaseObject*>& DoubanCrawler:: getObject() {
	return ObjectList;
}

vector<DataType> DoubanCrawler:: getDatatype() {
	return TargetDataList;
}

BaseData* DoubanCrawler:: newData (DataType type) {
    BaseData *data = NULL;
    if (type == _rating)
        data = new DoubleData(type);
    else if (type == _date || type == _director || type == _country || type == _language || type == _runtime)
        data = new StringData(type);
    else
    data = new VectorStringData(type);
    return data;
}

bool DoubanCrawler:: getData (string content, BaseData *data) {
    smatch matchstring;

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
            if (rating_string.length())
                rating_double = stod (rating_string);
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

        case _reviews: {
            static map<int, bool> visited_review;
            bool flag = 0;
            while (SEARCH (content, "https://movie.douban.com/review/([0-9]+)(?:[^0-9])")) {
                int id = stoi(matchstring[1].str());
                if (visited_review[id] == true) {
                    content = matchstring.suffix().str();
                    continue;
                }
                visited_review[id] = true;
                flag = true;

                string content_, tmp_file, ans;
                catcher.saveFile(matchstring.str(), tmp_file = "tmp.html");
                readFile(tmp_file, content_);

                content = matchstring.suffix().str();
                SEARCH(content_, "<meta name=\"description\" content=\"([^<]*)\" />");
                ans = matchstring[1].str();

                SEARCH(content_, "data-author=\"(.*)\"");
                if (matchstring[1].str().length())
                    ans = (flag ? "\n" : "") + ans + "\n" + matchstring[1].str();
                content_ = matchstring.suffix().str();

                while (SEARCH(content_, "<p>([^<]*)</p>")) {
                    if (matchstring[1].str().length() == 0) break;
                    ans = ans + "\n" + matchstring[1].str();
                    content_ = matchstring.suffix().str();
                }
                data->setString(ans + "\n");
                system("rm tmp.html");
            }
            return true;
        }

        case _photos:
            while (SEARCH(content, "<a href=\"https://movie.douban.com/photos/photo/([0-9]+)/\"><img src=\"((?:https?://)?.*p[0-9]*.jpg)\" alt=\"图片\" />")) {
				data-> setString (matchstring[1].str());
                data-> setString (matchstring[2].str());
                content = matchstring.suffix().str();
            }
            return true;
    }
}

void DoubanCrawler:: init() {
	string config = "douban-configuration.txt";
	TargetDataList = readConfiguration (config);
}

#ifdef DEBUG
ofstream ouf ("test.out");
#endif

void DoubanCrawler:: downloadPics (BaseObject *object) {
    vector<string> PhotoList = object-> getData(_photos)-> getVectorString();
    string name = object-> getData(_name)-> getVectorString()[0];
    for (int i = 0; i < PhotoList.size(); i += 2) {
        string name = PhotoList[i], html = PhotoList[i + 1];
#ifdef DEBUG
        cout << "photo: " << html << endl;
#endif
        catcher.saveFile(html, "pic/" + name  + ".jpg", true);
    }
}

BaseObject* DoubanCrawler:: scanPage (const string& HTML) {
    string content;
    readFile (HTML, content);

    BaseObject *object = new BaseObject;
    BaseData *data;

    for (auto it : DoubanMovieDataList) {
        data = newData (it);
        getData (content, data);
        object-> addData(data);
#ifdef DEBUG
        data-> printData(ouf), ouf << endl;
#endif
    }
#ifdef DEBUG
    ouf << endl;
    fprintf (stderr, "Scanned: %s\n", (object->getData(_name)->getVectorString())[0]);
#endif
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
            int id = stoi (matchstring[1].str());
            if (! visited[id]) {
                visited[id] = 1;
                QUrl.push_back(matchstring.str());
            }
            content = matchstring.suffix().str();
        }

        if (i) {
#ifdef DEBUG
            _ouf << i << endl;
#endif
            _ouf << "HTML: " << HTML << endl;
            BaseObject *object = scanPage (HTML);
            SEARCH(Url, "subject/([0-9]+)[^0-9]?");
            downloadPics (object);
            addObject (object);
        }
        while (clock() - start < delay);
    }
#ifdef DEBUG
    _ouf << QUrl.size() << endl;
    for (int i = 0; i < QUrl.size(); i++)
        _ouf << QUrl[i] << endl;
#endif
}
