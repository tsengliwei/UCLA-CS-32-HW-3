//
//  file.cpp
//  HW 3
//
//  Created by Li-Wei Tseng on 5/1/14.
//  Copyright (c) 2014 Li-Wei Tseng. All rights reserved.
//

#include <iostream>
#include <string>
using namespace std;

//Your declarations and implementations would go here

class File
{
public:
    File(string name){m_string = name;}
    virtual ~File(){};
    
    virtual string name() const{return m_string;}
    virtual void open() const = 0;
    virtual void redisplay() const;

private:
    string m_string;
};

void File::redisplay() const
{
    cout << "refresh the screen";
}

/////////////////////////////////////////

class TextMsg: public File
{
public:
    TextMsg(string name);
    virtual ~TextMsg();
    
    virtual void open() const;
};

/////////TextMsg implementation/////////

TextMsg::TextMsg(string name)
: File(name)
{}

TextMsg::~TextMsg()
{
    cout << "Destroying " << name() << ", a text message" << endl;
}

void TextMsg::open() const
{
    cout << "open text message";
}

////////////////////////////////////////

class Video: public File
{
public:
    Video(string name, int seconds);
    virtual ~Video();
    
    virtual void open() const;
    virtual void redisplay() const;

private:
    int m_seconds;
};

/////////Video implementation/////////

Video::Video(string name, int seconds)
:File(name), m_seconds(seconds)
{}

Video::~Video()
{
    cout << "Destroying " << name() << ", a video" << endl;
}

void Video::open() const
{
    cout << "play " << m_seconds << " second video";
}

void Video::redisplay() const
{
    cout << "replay video";
}
//////////////////////////////////////

class Picture: public File
{
public:
    Picture(string name);
    virtual ~Picture();
    
    virtual void open() const;
};

Picture::Picture(string name)
: File(name)
{}

Picture::~Picture()
{
    cout << "Destroying the picture " << name() << endl;
}

void Picture::open() const
{
    cout << "show picture";
}

/////////Picture implementation/////////


void openAndRedisplay(const File* f)
{
    cout << f->name() << ": ";
    f->open();
    cout << endl << "Redisplay: ";
    f->redisplay();
    cout << endl;
}

//#define FILE
#ifdef FILE

int main()
{
    File* files[5];
    files[0] = new TextMsg("fromFred.txt");
    // Videos have a name and running time
    files[1] = new Video("kitty.mpg", 57);
    files[2] = new Picture("poster.jpg");
    files[3] = new Picture("still.jpg");
    //files[4] = new File("readme");
    
    for (int k = 0; k < 4; k++)
        openAndRedisplay(files[k]);
    
    // Clean up the files before exiting
    cout << "Cleaning up" << endl;
    for (int n = 0; n < 4; n++)
        delete files[n];
}

#endif //FILE
