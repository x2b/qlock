#ifndef AUTHCREATOR_HPP
#define AUTHCREATOR_HPP

#include <QWidget>
#include <QLabel>
#include <QLayout>
#include <QPushButton>

#include "auth.h"
#include "AuthWidget.hpp"

class AuthCreator : public QWidget
{
  Q_OBJECT
  
  public:
    AuthCreator(QWidget* parent = 0);
    ~AuthCreator();
    
  private:
    auth        *m_auth;
    AuthWidget  *m_authw;
    QHBoxLayout *m_small;
    QVBoxLayout *m_main;
    QLabel      *lbl_status;
    QPushButton *pbt_create, *pbt_reset;
    Key         m_key1, m_key2;
    
  private slots:
    void createKeyFile();
    void processKey(Key k);
    void resetKeys();
    
};

#endif
