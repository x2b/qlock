#ifndef AUTHVERIFIER_HPP
#define AUTHVERIFIER_HPP

#include <QObject>

#include "auth.h"
#include "AuthWidget.hpp"
#include "Key.hpp"

class AuthVerifier : public AuthWidget
{
  Q_OBJECT
  
  public:
    AuthVerifier(QWidget* parent = 0);
    ~AuthVerifier();
    
  public slots:
    void verifyPassword(Key k);
    
  private:
    auth*      m_auth;
    int        m_tries;
};

#endif
