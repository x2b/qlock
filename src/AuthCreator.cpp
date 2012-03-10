#include <QApplication>
#include <QTimer>

#include "AuthCreator.hpp"

AuthCreator::AuthCreator(QWidget* parent)
  : QWidget(parent)
{
  m_main      = new QVBoxLayout;
  m_small     = new QHBoxLayout;
  m_authw     = new AuthWidget;
  lbl_status  = new QLabel;
  pbt_create  = new QPushButton("Create password file");
  pbt_reset   = new QPushButton("Reset");
  
  m_main->addWidget(m_authw);
  m_main->addWidget(lbl_status);
  m_main->addItem(m_small);
  
  m_small->addWidget(pbt_create);
  m_small->addWidget(pbt_reset);
  
  pbt_create->setEnabled(false);
  pbt_reset->setEnabled(false);
  
  lbl_status->setText("Please enter a key");
  
  connect(m_authw, SIGNAL(KeyAcquired(Key)),
    this, SLOT(processKey(Key)));
    
  connect(pbt_reset, SIGNAL(clicked()),
    this, SLOT(resetKeys()));
    
  connect(pbt_create, SIGNAL(clicked()),
    this, SLOT(createKeyFile()));
  
  setLayout(m_main);

}

void AuthCreator::createKeyFile()
{
  if(!create_auth(&m_auth, KEYFILE,
          m_key1.toString().toUtf8().constData()))
  {
    lbl_status->setText("Could not create password file");
  }
  else
  {
    lbl_status->setText("Successfully created password file");
    m_authw->setState(AuthWidget::CORRECT);
    pbt_create->setEnabled(false);
    pbt_reset->setEnabled(false);
    QTimer::singleShot(1000, qApp, SLOT(quit()));
  }
}

void AuthCreator::processKey(Key k)
{
  if(m_key1.size() == 0)
  {
    m_key1 = k;
    m_authw->reset();
    pbt_reset->setEnabled(true);
    lbl_status->setText("Please confirm the key");
  }
  else if(m_key2.size() == 0)
  {
    m_key2 = k;
    if(!(m_key1 == m_key2))
    {
      lbl_status->setText("The two keys do not match");
      m_authw->setState(AuthWidget::INCORRECT);
    }
    else
    {
      lbl_status->setText("The two keys match");
      m_authw->setState(AuthWidget::CORRECT);
      pbt_create->setEnabled(true);
    }
  }
}

void AuthCreator::resetKeys()
{
  m_key1.clear();
  m_key2.clear();
  pbt_reset->setEnabled(false);
  pbt_create->setEnabled(false);
  lbl_status->setText("Please enter a key");
  m_authw->reset();
}

AuthCreator::~AuthCreator()
{
  
}
