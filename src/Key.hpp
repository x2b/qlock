#ifndef KEY_H
#define KEY_H

#include <QVector>
#include <QString>

#define KEYFILE ".passfile"

class Entry
{
  public:
    Entry() : i(-1), j(-1) {}
    Entry(int x, int y) : i(x), j(y) {}
    int i;
    int j;
};

class Key : public QVector<Entry>
{
  public:
    QString toString() const;
    bool operator==(const Key& other);
};

#endif
