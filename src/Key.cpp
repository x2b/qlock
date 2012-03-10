#include "Key.hpp"

#include <QDebug>

QString Key::toString() const
{
  QString str;
  const_iterator it;
  
  for(it = begin(); it != end(); ++it)
  {
    str += QString("(%1,%2)").arg(it->i).arg(it->j);
    if(it + 1 != end())
      str += QChar(' ');
  }
  
  return str;
}

bool Key::operator==(const Key& other)
{
  qDebug() << "Comparing keys: " << toString() << " " << other.toString();
  const_iterator it, oit;
  
  if(size() != other.size())
    return false;
  
  for(it = begin(), oit = other.begin(); it != end(); ++it, ++oit)
  {
    if(it->i != oit->i || it->j != oit->j)
      return false;
  }
  return true;
}
