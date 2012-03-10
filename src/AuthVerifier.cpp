#include <QApplication>
#include <QDebug>
#include <QTimer>
#include <exception>
using std::exception;

#include "AuthVerifier.hpp"

AuthVerifier::AuthVerifier(QWidget* parent)
  : AuthWidget(parent),
  m_tries(0)
{
  if(!read_auth(&m_auth, KEYFILE))
  {
    throw exception();
  }
  
  connect(this, SIGNAL(KeyAcquired(Key)),
    this, SLOT(verifyPassword(Key)));
  
}


void AuthVerifier::verifyPassword(Key k)
{
  qDebug() << k.toString();
  
  if(verify(m_auth, (const char*) k.toString().toUtf8().constData()))
  {
    setState(AuthWidget::CORRECT);
    QTimer::singleShot(1000, qApp, SLOT(quit()));
  }
  else
  {
    qWarning() << "Failed attempts: " << ++m_tries;
    setState(AuthWidget::INCORRECT);
    QTimer::singleShot(5*1000, this, SLOT(reset()));
  }
}


AuthVerifier::~AuthVerifier()
{
  releaseKeyboard();
  releaseMouse();
  free_auth(&m_auth);
}
