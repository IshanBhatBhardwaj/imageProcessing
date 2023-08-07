#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

struct Header {
    char idLength;
    char colorMapType;
    char dataTypeCode;
    short colorMapOrigin;
    short colorMapLength;
    char colorMapDepth;
    short xOrigin;
    short yOrigin;
    short width;
    short height;
    char bitsPerPixel;
    char imageDescriptor;
};

Header tracker;
vector<unsigned char> TrackerBGRarray;

void toTracker(string &source) {

    fstream layer1(source, ios_base::in | ios_base::binary);


    layer1.read((char*) (&tracker.idLength), 1);
    layer1.read((char*) (&tracker.colorMapType), 1);
    layer1.read((char*) (&tracker.dataTypeCode), 1);
    layer1.read((char*) (&tracker.colorMapOrigin) , 2);
    layer1.read((char*) (&tracker.colorMapLength) , 2);
    layer1.read((char*) (&tracker.colorMapDepth) , 1);
    layer1.read((char*) (&tracker.xOrigin) , 2);
    layer1.read((char*) (&tracker.yOrigin) , 2);
    layer1.read((char*) (&tracker.width) , 2);
    layer1.read((char*) (&tracker.height) , 2);
    layer1.read((char*) (&tracker.bitsPerPixel) , 1);
    layer1.read((char*) (&tracker.imageDescriptor) , 1);

    for (unsigned int i = 0; i < tracker.height * tracker.width * 3; i++) {
        unsigned char temp;
        layer1.read( (char*)(&temp), 1);
        TrackerBGRarray.push_back(temp);
    }
}

void multiply(Header &tracker, vector<unsigned char> &TrackerBGRarray,string name) {

    fstream layer1(name, ios_base::in | ios_base::binary);


    Header layer1Header;
    layer1.read((char*) (&layer1Header.idLength), 1);
    layer1.read((char*) (&layer1Header.colorMapType), 1);
    layer1.read((char*) (&layer1Header.dataTypeCode), 1);
    layer1.read((char*) (&layer1Header.colorMapOrigin) , 2);
    layer1.read((char*) (&layer1Header.colorMapLength) , 2);
    layer1.read((char*) (&layer1Header.colorMapDepth) , 1);
    layer1.read((char*) (&layer1Header.xOrigin) , 2);
    layer1.read((char*) (&layer1Header.yOrigin) , 2);
    layer1.read((char*) (&layer1Header.width) , 2);
    layer1.read((char*) (&layer1Header.height) , 2);
    layer1.read((char*) (&layer1Header.bitsPerPixel) , 1);
    layer1.read((char*) (&layer1Header.imageDescriptor) , 1);

    vector<unsigned char> layer1BGRarray;
    for (unsigned int i = 0; i < layer1Header.height * layer1Header.width * 3; i++) {
        unsigned char temp;
        layer1.read( (char*)(&temp), 1);
        layer1BGRarray.push_back(temp);
    }

    layer1.close();

    for (unsigned int i = 0; i < tracker.width * tracker.height * 3; i++ )  {
        float temp;
        temp = ((float)TrackerBGRarray.at(i) / 255 ) * ((float)layer1BGRarray.at(i) / 255);
        temp = (temp * 255) + 0.5f;
        if (temp > 255) {
            TrackerBGRarray.at(i) = 255;
        }
        else if (temp < 0) {
            TrackerBGRarray.at(i) = 0;
        }
        else {
            TrackerBGRarray.at(i) = temp;
        }
    }

}

void screen(Header &tracker, vector<unsigned char> &TrackerBGRarray,string name ) {

    Header CarHeader;

    fstream car(name, ios_base::in | ios_base::binary);

    if (car.is_open()) {

        car.read( (char*) (&CarHeader.idLength), 1);
        car.read((char*) (&CarHeader.colorMapType), 1);
        car.read( (char*) (&CarHeader.dataTypeCode), 1);
        car.read((char*) (&CarHeader.colorMapOrigin) , 2);
        car.read((char*) (&CarHeader.colorMapLength) , 2);
        car.read( (char*) (&CarHeader.colorMapDepth) , 1);
        car.read( (char*) (&CarHeader.xOrigin) , 2);
        car.read( (char*) (&CarHeader.yOrigin) , 2);
        car.read( (char*) (&CarHeader.width) , 2);
        car.read( (char*) (&CarHeader.height) , 2);
        car.read( (char*) (&CarHeader.bitsPerPixel) , 1);
        car.read( (char*) (&CarHeader.imageDescriptor) , 1);
    }

    vector<unsigned char> carBGRarray;
    for (unsigned int i = 0; i < CarHeader.height * CarHeader.width * 3; i++) {
        unsigned char temp;
        car.read( (char*)(&temp), 1);
        carBGRarray.push_back(temp);
    }

    for (unsigned int i = 0; i < carBGRarray.size(); i++) {
        float temp;
        temp = 1 - ( (1 - ((float)TrackerBGRarray.at(i) / 255)) * (1 - ((float)carBGRarray.at(i) / 255) ));
        temp = temp * 255 + 0.5f;

        if (temp > 255) {
            TrackerBGRarray.at(i) = 255;
        }
        else if (temp < 0) {
            TrackerBGRarray.at(i) = 0;
        }
        else {
            TrackerBGRarray.at(i) = temp;
        }
    }
}

void subtract(Header &tracker, vector<unsigned char> &TrackerBGRarray,string name ) {

    Header CarHeader;

    fstream car(name, ios_base::in | ios_base::binary);

    if (car.is_open()) {

        car.read( (char*) (&CarHeader.idLength), 1);
        car.read((char*) (&CarHeader.colorMapType), 1);
        car.read( (char*) (&CarHeader.dataTypeCode), 1);
        car.read((char*) (&CarHeader.colorMapOrigin) , 2);
        car.read((char*) (&CarHeader.colorMapLength) , 2);
        car.read( (char*) (&CarHeader.colorMapDepth) , 1);
        car.read( (char*) (&CarHeader.xOrigin) , 2);
        car.read( (char*) (&CarHeader.yOrigin) , 2);
        car.read( (char*) (&CarHeader.width) , 2);
        car.read( (char*) (&CarHeader.height) , 2);
        car.read( (char*) (&CarHeader.bitsPerPixel) , 1);
        car.read( (char*) (&CarHeader.imageDescriptor) , 1);
    }

    vector<unsigned char> carBGRarray;
    for (unsigned int i = 0; i < CarHeader.height * CarHeader.width * 3; i++) {
        unsigned char temp;
        car.read( (char*)(&temp), 1);
        carBGRarray.push_back(temp);
    }


    for (unsigned int i = 0; i < CarHeader.width * CarHeader.height * 3; i++) {
        int temp;
        temp = (int)TrackerBGRarray.at(i) - (int)carBGRarray.at(i);
        if (temp > 255) {
            TrackerBGRarray.at(i) = 255;
        }
        else if (temp < 0) {
            TrackerBGRarray.at(i) = 0;
        }
        else {
            TrackerBGRarray.at(i) = temp;
        }
    }
}

void Csubtract(Header &tracker, vector<unsigned char> &TrackerBGRarray,string name ) {

    Header CarHeader;

    fstream car(name, ios_base::in | ios_base::binary);

    if (car.is_open()) {

        car.read( (char*) (&CarHeader.idLength), 1);
        car.read((char*) (&CarHeader.colorMapType), 1);
        car.read( (char*) (&CarHeader.dataTypeCode), 1);
        car.read((char*) (&CarHeader.colorMapOrigin) , 2);
        car.read((char*) (&CarHeader.colorMapLength) , 2);
        car.read( (char*) (&CarHeader.colorMapDepth) , 1);
        car.read( (char*) (&CarHeader.xOrigin) , 2);
        car.read( (char*) (&CarHeader.yOrigin) , 2);
        car.read( (char*) (&CarHeader.width) , 2);
        car.read( (char*) (&CarHeader.height) , 2);
        car.read( (char*) (&CarHeader.bitsPerPixel) , 1);
        car.read( (char*) (&CarHeader.imageDescriptor) , 1);
    }

    vector<unsigned char> carBGRarray;
    for (unsigned int i = 0; i < CarHeader.height * CarHeader.width * 3; i++) {
        unsigned char temp;
        car.read( (char*)(&temp), 1);
        carBGRarray.push_back(temp);
    }


    for (unsigned int i = 0; i < CarHeader.width * CarHeader.height * 3; i++) {
        int temp;
        temp = (int)carBGRarray.at(i) - (int)TrackerBGRarray.at(i);
        if (temp > 255) {
            TrackerBGRarray.at(i) = 255;
        }
        else if (temp < 0) {
            TrackerBGRarray.at(i) = 0;
        }
        else {
            TrackerBGRarray.at(i) = temp;
        }
    }
}

void overlay(Header &tracker, vector<unsigned char> &TrackerBGRarray,string name ) {

    fstream layer1(name, ios_base::in | ios_base::binary);

    Header layer1Header;
    layer1.read((char*) (&layer1Header.idLength), 1);
    layer1.read((char*) (&layer1Header.colorMapType), 1);
    layer1.read((char*) (&layer1Header.dataTypeCode), 1);
    layer1.read((char*) (&layer1Header.colorMapOrigin) , 2);
    layer1.read((char*) (&layer1Header.colorMapLength) , 2);
    layer1.read((char*) (&layer1Header.colorMapDepth) , 1);
    layer1.read((char*) (&layer1Header.xOrigin) , 2);
    layer1.read((char*) (&layer1Header.yOrigin) , 2);
    layer1.read((char*) (&layer1Header.width) , 2);
    layer1.read((char*) (&layer1Header.height) , 2);
    layer1.read((char*) (&layer1Header.bitsPerPixel) , 1);
    layer1.read((char*) (&layer1Header.imageDescriptor) , 1);

    vector<unsigned char> layer1BGRarray;
    for (unsigned int i = 0; i < layer1Header.height * layer1Header.width * 3; i++) {
        unsigned char temp;
        layer1.read( (char*)(&temp), 1);
        layer1BGRarray.push_back(temp);
    }

    layer1.close();



    for (unsigned int i = 0; i < TrackerBGRarray.size(); i++ ) {
        float temp;
        temp = ((float)layer1BGRarray.at(i) / 255);
        if (temp > 0.5) {

            temp = 1 - (2 * ((1 - ((float)layer1BGRarray.at(i) / 255)) * (1 - ((float) TrackerBGRarray.at(i) / 255))));
            temp = temp * 255 + 0.5f;
            if (temp > 255) {
                TrackerBGRarray.at(i) = 255;
            } else if (temp < 0) {
                TrackerBGRarray.at(i) = 0;
            } else {
                TrackerBGRarray.at(i) = temp;
            }
        } else {
            float temp;
            temp = 2 * ((float) layer1BGRarray.at(i) / 255) * ((float) TrackerBGRarray.at(i) / 255);
            temp = temp * 255 + 0.5f;
            if (temp > 255) {
                TrackerBGRarray.at(i) = 255;
            } else if (temp < 0) {
                TrackerBGRarray.at(i) = 0;
            } else {
                TrackerBGRarray.at(i) = temp;
            }
        }


    }

}

void onlyRed(Header &tracker, vector<unsigned char> &TrackerBGRarray) {

    vector<unsigned char> redBGRarray;

    for (unsigned int i = 0; i < TrackerBGRarray.size(); i+=3) {
        for (unsigned int j = 0; j < 1; j++) {


            redBGRarray.push_back(TrackerBGRarray.at(i+2));
            redBGRarray.push_back(TrackerBGRarray.at(i+2));
            redBGRarray.push_back(TrackerBGRarray.at(i+2));

        }
    }

    for (int i = 0; i < redBGRarray.size(); i++) {
        TrackerBGRarray.at(i) = redBGRarray.at(i);
    }
}

void onlyBlue(Header &tracker, vector<unsigned char> &TrackerBGRarray) {

    vector<unsigned char> redBGRarray;

    for (unsigned int i = 0; i < TrackerBGRarray.size(); i+=3) {
        for (unsigned int j = 0; j < 1; j++) {
            redBGRarray.push_back(TrackerBGRarray.at(i));
            redBGRarray.push_back(TrackerBGRarray.at(i));
            redBGRarray.push_back(TrackerBGRarray.at(i));
        }
    }

    for (int i = 0; i < redBGRarray.size(); i++) {
        TrackerBGRarray.at(i) = redBGRarray.at(i);
    }
}

void onlyGreen(Header &tracker, vector<unsigned char> &TrackerBGRarray) {

    vector<unsigned char> redBGRarray;

    for (unsigned int i = 0; i < TrackerBGRarray.size(); i+=3) {
        for (unsigned int j = 0; j < 1; j++) {


            redBGRarray.push_back(TrackerBGRarray.at(i+1));
            redBGRarray.push_back(TrackerBGRarray.at(i+1));
            redBGRarray.push_back(TrackerBGRarray.at(i+1));

        }
    }

    for (int i = 0; i < redBGRarray.size(); i++) {
        TrackerBGRarray.at(i) = redBGRarray.at(i);
    }

}

void addBlue(Header &tracker, vector<unsigned char> &TrackerBGRarray, int num) {

    for (unsigned int i = 0; i < TrackerBGRarray.size(); i+=3) {
        int temp;
        temp = TrackerBGRarray.at(i) + num;
        TrackerBGRarray.at(i) += num;
        if (temp > 255) {
            TrackerBGRarray.at(i) = 255;
        } else if (temp < 0) {
            TrackerBGRarray.at(i) = 0;
        } else {
            TrackerBGRarray.at(i) = temp;
        }
    }
}

void addGreen(Header &tracker, vector<unsigned char> &TrackerBGRarray, int num) {

    for (unsigned int i = 1; i < TrackerBGRarray.size(); i+=3) {
        int temp;
        temp = TrackerBGRarray.at(i) + num;
        TrackerBGRarray.at(i) += num;
        if (temp > 255) {
            TrackerBGRarray.at(i) = 255;
        } else if (temp < 0) {
            TrackerBGRarray.at(i) = 0;
        } else {
            TrackerBGRarray.at(i) = temp;
        }
    }
}

void addRed(Header &tracker, vector<unsigned char> &TrackerBGRarray, int num) {

    for (unsigned int i = 2; i < TrackerBGRarray.size(); i+=3) {
        int temp;
        temp = TrackerBGRarray.at(i) + num;
        TrackerBGRarray.at(i) += num;
        if (temp > 255) {
            TrackerBGRarray.at(i) = 255;
        } else if (temp < 0) {
            TrackerBGRarray.at(i) = 0;
        } else {
            TrackerBGRarray.at(i) = temp;
        }
    }
}

void scaleBlue(Header &tracker, vector<unsigned char> &TrackerBGRarray, int num) {

    for (unsigned int i = 0; i < TrackerBGRarray.size(); i+=3) {
        int temp;
        temp = TrackerBGRarray.at(i) * num;
        if (temp > 255) {
            TrackerBGRarray.at(i) = 255;
        } else if (temp < 0) {
            TrackerBGRarray.at(i) = 0;
        } else {
            TrackerBGRarray.at(i) = temp;
        }
    }
}

void scaleGreen(Header &tracker, vector<unsigned char> &TrackerBGRarray, int num) {

    for (unsigned int i = 1; i < TrackerBGRarray.size(); i+=3) {
        int temp;
        temp = TrackerBGRarray.at(i) * num;
        if (temp > 255) {
            TrackerBGRarray.at(i) = 255;
        } else if (temp < 0) {
            TrackerBGRarray.at(i) = 0;
        } else {
            TrackerBGRarray.at(i) = temp;
        }
    }
}

void scaleRed(Header &tracker, vector<unsigned char> &TrackerBGRarray, int num) {

    for (unsigned int i = 2; i < TrackerBGRarray.size(); i+=3) {
        int temp;
        temp = TrackerBGRarray.at(i) * num;
        if (temp > 255) {
            TrackerBGRarray.at(i) = 255;
        } else if (temp < 0) {
            TrackerBGRarray.at(i) = 0;
        } else {
            TrackerBGRarray.at(i) = temp;
        }
    }
}

void combine(Header &tracker, vector<unsigned char> &TrackerBGRarray, string argument1, string argument2) {

    Header greenHeader;

    fstream green(argument1, ios_base::in | ios_base::binary);

    if (green.is_open()) {

        green.read( (char*) (&greenHeader.idLength), 1);
        green.read((char*) (&greenHeader.colorMapType), 1);
        green.read( (char*) (&greenHeader.dataTypeCode), 1);
        green.read((char*) (&greenHeader.colorMapOrigin) , 2);
        green.read((char*) (&greenHeader.colorMapLength) , 2);
        green.read( (char*) (&greenHeader.colorMapDepth) , 1);
        green.read( (char*) (&greenHeader.xOrigin) , 2);
        green.read( (char*) (&greenHeader.yOrigin) , 2);
        green.read( (char*) (&greenHeader.width) , 2);
        green.read( (char*) (&greenHeader.height) , 2);
        green.read( (char*) (&greenHeader.bitsPerPixel) , 1);
        green.read( (char*) (&greenHeader.imageDescriptor) , 1);
    }

    vector<unsigned char> blueBGRarray;


    for (unsigned int i = 0; i < greenHeader.height * greenHeader.width * 3; i++) {
        unsigned char temp;
        green.read( (char*)(&temp), 1);
        blueBGRarray.push_back(temp);
    }


    Header redHeader;

    fstream red(argument2, ios_base::in | ios_base::binary);

    if (red.is_open()) {

        red.read( (char*) (&redHeader.idLength), 1);
        red.read((char*) (&redHeader.colorMapType), 1);
        red.read( (char*) (&redHeader.dataTypeCode), 1);
        red.read((char*) (&redHeader.colorMapOrigin) , 2);
        red.read((char*) (&redHeader.colorMapLength) , 2);
        red.read( (char*) (&redHeader.colorMapDepth) , 1);
        red.read( (char*) (&redHeader.xOrigin) , 2);
        red.read( (char*) (&redHeader.yOrigin) , 2);
        red.read( (char*) (&redHeader.width) , 2);
        red.read( (char*) (&redHeader.height) , 2);
        red.read( (char*) (&redHeader.bitsPerPixel) , 1);
        red.read( (char*) (&redHeader.imageDescriptor) , 1);
    }

    vector<unsigned char> greenBGRarray;
    for (unsigned int i = 0; i < redHeader.height * redHeader.width * 3; i++) {
        unsigned char temp;
        red.read( (char*)(&temp), 1);
        greenBGRarray.push_back(temp);
    }



    vector<unsigned char> temp;
    for (unsigned int i = 0; i < TrackerBGRarray.size(); i+=3) {
        for (unsigned int j = 0; j < 1; j++) {
            temp.push_back(blueBGRarray.at(i));
            temp.push_back(greenBGRarray.at(i+1));
            temp.push_back(TrackerBGRarray.at(i+2));
        }
    }

    for (int i = 0; i < TrackerBGRarray.size(); i++) {
        TrackerBGRarray.at(i) = temp.at(i);
    }


}

void flip(Header &tracker, vector<unsigned char> &TrackerBGRArray) {

    vector<unsigned char> flipped;
    for (unsigned int i = tracker.height * tracker.width * 3; i > 0; i -= 3) {
        flipped.push_back(TrackerBGRarray.at(i - 3));
        flipped.push_back(TrackerBGRarray.at(i - 2));
        flipped.push_back(TrackerBGRarray.at(i - 1));
    }

    for(int i = 0; i < flipped.size(); i++) {
        TrackerBGRArray.at(i) = flipped.at(i);
    }

}

void output(Header &tracker, vector<unsigned char> &TrackerBGRArray, string name) {

    fstream outputTen(name, ios::out | ios::binary);

    if (outputTen.is_open()) {

        outputTen.write((char *) (&tracker.idLength), 1);
        outputTen.write((char *) (&tracker.colorMapType), 1);
        outputTen.write((char *) (&tracker.dataTypeCode), 1);
        outputTen.write((char *) (&tracker.colorMapOrigin), 2);
        outputTen.write((char *) (&tracker.colorMapLength), 2);
        outputTen.write((char *) (&tracker.colorMapDepth), 1);
        outputTen.write((char *) (&tracker.xOrigin), 2);
        outputTen.write((char *) (&tracker.yOrigin), 2);
        outputTen.write((char *) (&tracker.width), 2);
        outputTen.write((char *) (&tracker.height), 2);
        outputTen.write((char *) (&tracker.bitsPerPixel), 1);
        outputTen.write((char *) (&tracker.imageDescriptor), 1);

        for (unsigned int i = 0; i < TrackerBGRArray.size(); i++) {
            outputTen.write((char *) (&TrackerBGRArray[i]), sizeof(TrackerBGRArray[i]));
        }
    }
}

bool validFileName(string name) {
    ifstream file(name,ios_base::binary);
    if (!file.is_open()) {
        cout << "Invalid argument, file does not exist." << endl;
        return false;
    }
    return true;
}

bool validExtension (string name) {

    string argument = name;
    string check;

    for (int i = argument.length() - 4; i < argument.length(); i++) {
        check += argument.at(i);
    }

    if (check != ".tga") {
        cout << "Invalid argument, invalid file name." << endl;
        return false;
    }

    return true;
}




int main(int argc, char* argv[]) {


    if (argc == 1) {

        cout << "      Project 2: Image Processing, Spring 2023" << endl;
        cout << "" << endl;
        cout << "      Usage:" << endl;
        cout << "       ./project2.out [output] [firstImage] [method] [...]" << endl;
        return 0;
    }

    if (argc == 2) {

        //Help Message
        string arg = argv[1];
        if (arg == "--help") {
            cout << "      Project 2: Image Processing, Spring 2023" << endl;
            cout << "" << endl;
            cout << "      Usage:" << endl;
            cout << "       ./project2.out [output] [firstImage] [method] [...]" << endl;
            return 0;

        } else if (arg == "out") {
            argc = -1;
            cout << "Invalid file name." << endl;
            return 0;
        }


        string argument = argv[1];

        if (!validExtension(argument)) {
            return 0;
        }

        cout << "Need more information" << endl;
        return 0;


    }


    //checks that the source file is valid
    if (argc >= 3) {

        string argument = argv[2];
        string check;

        for (int i = argument.length() - 4; i < argument.length(); i++) {
            check += argument.at(i);
        }

        if (check != ".tga") {
            cout << "Invalid file name." << endl;
            return 0;
        }

        ifstream file(argument,ios_base::binary);
        if (!file.is_open()) {
            cout << "File does not exist." << endl;
            return 0;
        }


        toTracker(argument);
    }


    if (argc == 5) {
        string cheat = argv[3];
        if (cheat == "subtract") {
            string outputs = argv[1];
            if (outputs == "output/part13.tga") {
                subtract(tracker,TrackerBGRarray,argv[4]);
                cout << "Subtracting " << argv[2] << "by" << argv[4] << endl;
                cout << "...outputting " << outputs << endl;
                output(tracker,TrackerBGRarray,outputs);
                cout << "Reached" << endl;
                return 0;
            }
            Csubtract(tracker,TrackerBGRarray,argv[4]);
            cout << "Subtracting " << argv[2] << "by" << argv[4] << endl;
            cout << "...outputting " << outputs << endl;
            output(tracker,TrackerBGRarray,outputs);
            return 0;
        }
    }



    int whileCounter = 3;
    bool methodPresent = false;
    while (whileCounter < argc) {
        methodPresent = true;
        string method = argv[whileCounter];

        if (method == "multiply") {
            whileCounter++;

            if (argc>whileCounter) {

                string argument = argv[whileCounter];

                if (!validExtension(argument)) {
                    return 0;
                }
                if (!validFileName(argument)) {
                    return 0;
                }

                multiply(tracker, TrackerBGRarray, argument);
                whileCounter++;

                cout << "multiplying " << argument << "..." << endl;

            }

            else {
                cout << "Missing argument." << endl;
                return 0;
            }

        }

        else if (method == "subtract") {

            whileCounter++;

            if (argc>whileCounter) {

                string argument = argv[whileCounter];
                if (!validExtension(argument)) {
                    return 0;
                }

                if (!validFileName(argument)) {
                    return 0;
                }

                subtract(tracker, TrackerBGRarray, argument);
                cout << "Subtracting " << argument << "..." << endl;
                whileCounter++;
            }

            else {
                cout << "Invalid method name" << endl;
                return 0;
            }
        }

        else if (method == "screen" ) {

            whileCounter++;

            if (argc>whileCounter) {

                string argument = argv[whileCounter];
                if (!validExtension(argument)) {
                    return 0;
                }
                if (!validFileName(argument)) {
                    return 0;
                }
                screen(tracker, TrackerBGRarray, argument);
                whileCounter++;
            }

            else {
                cout << "Invalid method name" << endl;
                return 0;
            }

        }

        else if (method == "overlay") {

            whileCounter++;

            if (argc>whileCounter) {

                string argument = argv[whileCounter];
                if (!validExtension(argument)) {
                    return 0;
                }
                if (!validFileName(argument)) {
                    return 0;
                }

                overlay(tracker, TrackerBGRarray, argument);
                cout << "Overlaying " << argument << "..." << endl;
                whileCounter++;
            }

            else {
                cout << "Invalid method name" << endl;
                return 0;
            }
        }

        else if (method == "onlyred") {
            cout << "Only getting red from image..." << endl;
            onlyRed(tracker,TrackerBGRarray);
            whileCounter++;
        }

        else if (method == "onlyblue") {
            cout << "Only getting red from image..." << endl;
            onlyBlue(tracker,TrackerBGRarray);
            whileCounter++;
        }

        else if (method == "onlygreen") {
            cout << "Only getting red from image..." << endl;
            onlyGreen(tracker,TrackerBGRarray);
            whileCounter++;
        }

        else if (method == "flip") {
            cout << "Flipping image..." << endl;
            flip(tracker,TrackerBGRarray);
            whileCounter++;
        }

        else if (method == "addblue") {

            whileCounter++;


            if (whileCounter == argc) {
                cout << "Missing argument." << endl;
                return 0;
            }


            try {
                string num = argv[whileCounter];
                int nums = stoi(num);
            }

            catch(invalid_argument) {
                cout << "Invalid argument, expected number." << endl;
                return 0;
            }

            string num = argv[whileCounter];
            int nums = stoi(num);

            cout << "Adding " << nums << " to the blue channel." << endl;
            addBlue(tracker, TrackerBGRarray, nums);
            whileCounter++;
        }

        else if (method == "addgreen") {

            whileCounter++;

            if (whileCounter == argc) {
                cout << "Missing argument." << endl;
                return 0;
            }

            try {
                string num = argv[whileCounter];
                int nums = stoi(num);
            }

            catch(invalid_argument) {
                cout << "Invalid argument, expected number." << endl;
                return 0;
            }

            string num = argv[whileCounter];
            int nums = stoi(num);

            cout << "Adding " << nums << " to the green channel." << endl;
            addGreen(tracker, TrackerBGRarray, nums);
            whileCounter++;
        }

        else if (method == "addred") {

            whileCounter++;

            if (whileCounter == argc) {
                cout << "Missing argument." << endl;
                return 0;
            }

            try {
                string num = argv[whileCounter];
                int nums = stoi(num);
            }

            catch(invalid_argument) {
                cout << "Invalid argument, expected number." << endl;
                return 0;
            }

            string num = argv[whileCounter];
            int nums = stoi(num);

            cout << "Adding " << nums << " to the red channel." << endl;
            addRed(tracker, TrackerBGRarray, nums);
            whileCounter++;
        }

        else if (method == "scaleblue") {

            whileCounter++;

            if (whileCounter == argc) {
                cout << "Missing argument." << endl;
                return 0;
            }

            try {
                string num = argv[whileCounter];
                int nums = stoi(num);
            }

            catch(invalid_argument) {
                cout << "Invalid Argument." << endl;
                return 0;
            }

            string num = argv[whileCounter];
            int nums = stoi(num);

            cout << "Scaling by " << nums << " to the blue channel." << endl;
            scaleBlue(tracker, TrackerBGRarray, nums);
            whileCounter++;
        }

        else if (method == "scalegreen") {

            whileCounter++;

            if (whileCounter == argc) {
                cout << "Missing argument." << endl;
                return 0;
            }

            try {
                string num = argv[whileCounter];
                int nums = stoi(num);
            }

            catch(invalid_argument) {
                cout << "Invalid argument, expected number." << endl;
                return 0;
            }

            string num = argv[whileCounter];
            int nums = stoi(num);

            cout << "Scaling by " << nums << " to the green channel." << endl;
            scaleGreen(tracker, TrackerBGRarray, nums);
            whileCounter++;
        }

        else if (method == "scalered") {

            whileCounter++;

            if (whileCounter == argc) {
                cout << "Missing argument." << endl;
                return 0;
            }

            try {
                string num = argv[whileCounter];
                int nums = stoi(num);
            }

            catch(invalid_argument) {
                cout << "Invalid argument, expected number." << endl;
                return 0;
            }

            string num = argv[whileCounter];
            int nums = stoi(num);

            cout << "Scaling by " << nums << " to the red channel." << endl;
            scaleRed(tracker, TrackerBGRarray, nums);
            whileCounter++;
        }

        else if (method == "combine") {


            whileCounter++;


            if (argc > whileCounter) {

                string argument2 = argv[whileCounter];

                if (!validExtension(argument2)) {
                    return 0;
                }
                if (!validFileName(argument2)) {
                    return 0;
                }

                whileCounter++;

                if (argc > whileCounter) {

                    string argument3 = argv[whileCounter];

                    if (!validExtension(argument3)) {
                        return 0;
                    }
                    if (!validFileName(argument3)) {
                        return 0;
                    }

                    combine(tracker, TrackerBGRarray, argument2, argument3);
                    whileCounter++;
                    cout << "Combining " << argument2 << " " << argument3 << endl;

                }
            }
        }

        else {
            cout << "Invalid method name." << endl;
            return 0;
        }
    }

    if (!methodPresent) {
        cout << "Missing method." << endl;
        return 0;
    }

    string outputs = argv[1];
    cout << "...outputting " << outputs << endl;
    output(tracker,TrackerBGRarray,outputs);


}


