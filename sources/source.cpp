// Copyright 2018 Your Name <your_email>

#include "header.hpp"

    // Конструктор из строки, содержащей Json-данные.
    Json::Json(const std::string& s): str(s) {}

    // Метод возвращает true, 
    // если данный экземпляр содержит в себе JSON-массив. Иначе false.
    bool Json::is_array() const {
        if (str[position] != '[')
            return false;
        else return true;
    }
    
    // Метод возвращает true, 
    // если данный экземпляр содержит в себе JSON-объект. Иначе false.
    bool Json::is_object() const {
        if(str[position] != '{')
            return false;
        else return true;
    }

    // Метод возвращает значение по ключу key,
    // если экземпляр является JSON-объектом.
    // Значение может иметь один из следующих типов:
    // Json, std::string, double, bool или быть пустым.
    // Если экземпляр является JSON-массивом, генерируется исключение.
    std::any& Json::operator[](const std::string& key) {
        if (this->is_array()) {
            auto it = parsed.find(key);
            return it->second;
        } else {
            throw std::bad_any_cast();
    }

    // Метод возвращает значение по индексу index,
    // если экземпляр является JSON-массивом.
    // Значение может иметь один из следующих типов:
    // Json, std::string, double, bool или быть пустым.
    // Если экземпляр является JSON-объектом, генерируется исключение.
    std::any& Json::operator[](int index) {
        if (this->is_array()) {
            auto it = parsed.begin();
            advance(it, index);
            return it->second;
        } else {
            throw std::bad_any_cast();
    }

    string Json::findKey(const string& s) {
        int start, finish;
        string key;
        start = s.find("\"", position);

        finish = s.find("\"", start+1);
        key.assign(s, start+1, finish-(start+1));
        position = finish;
        return key;
    }

    any Json::findMean(const string& s) {
        string ss;
        any mean;
        position = s.find(":", position);

        if (s[position+1] == ' ')
            position += 2;

            if (s[position] == '\"') {
                ss.assign(s, position + 1, 
                    (s.find("\"", position + 1) - (position + 1)));
                position = s.find("\"", position+1);
                position++;
                return ss;
            }

            if ((s[position] >= '1') && (s[position] <= '9')) {
                do {
                    ss += s.at(position);
                    position++;
                }
                while (s[position] != ',');
                return atoi(ss.c_str());
            }

            if (is_object()) {
                ss.assign(s, position, s.size()-position);
                position = s.find("}", position) + 1;
                return Json::parse(ss);
            }

            if (s[position] == 't') {
                return true;
            }

            if (s[position] == 'f') {
                return false;
            }

            if (is_array()) {
                vector <string> numbers;
                numbers.push_back("");
                int i = 0;
                for (i = 0; s[position] != ']';) {
                    if ((s[position] == '[') || 
                            (s[position] == '\t') || 
                            (s[position] == '\n')) {
                        position++;
                    }
                    else if ((s[position] >= '1') && 
                            (s[position] <= '9')) {
                        numbers[i] = s[position];
                        position++;
                    }
                    else if (s[position] == ',') {
                        position++;
                        ++i;
                        numbers.push_back("");
                    }
                }
                position++;
                int *in_number = new int[numbers.size()];
                for (int j = 0; j <= i; ++j) {
                    in_number[j] = atoi(numbers[j]);
                }
                return in_number;
            }
            return mean;
    }

    // Метод возвращает объект класса Json из строки,
    // содержащей Json-данные.
    static Json Json::parse(const std::string& s) {
        Json object(s);
        object.position = 0;
        string ss = s;
        while(s[object.position] != '}') {
            string key;
            any mean;
            key = object.findKey(s);
            mean = object.findMean(s);
            object.parsed[key] = mean;

            while ((s[object.position] == '\t') 
               || (s[object.position] == '\n') 
               || (s[object.position] == ','))
                object.position++;
        }
        return object;
    }

    // Метод возвращает объекта класса Json из файла,
    // содержащего Json-данные в текстовом формате.
    static Json Json::parseFile(const std::string& path_to_file) {
        ifstream fin(path_to_file);
        string stringToParse("");
        while (!fin.eof()) {
            string buf;
            getline(fin, buf);
            stringToParse += buf;
            stringToParse += '\n';
        }
        return Json::parse(stringToParse);
    }

    int position;
    std::string str;
    std::map <std::string, std::any> parsed;
};

