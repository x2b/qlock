#ifndef AUTHWIDGET_HPP
#define AUTHWIDGET_HPP

#include <QWidget>
#include <QTransform>

#include "Key.hpp"

class AuthWidget : public QWidget
{
  Q_OBJECT
  
  public:
    AuthWidget(QWidget* parent = 0, int elements = 4);
    ~AuthWidget();
    
    
    QSize sizeHint() const {return QSize(400,400);}
    
    enum State {UNKNOWN, CORRECT, INCORRECT};
    
  signals:
    void KeyAcquired(Key k);
  
  public slots:
    void reset();
    void setState(State state);
    
  protected:
    void paintEvent(QPaintEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void resizeEvent(QResizeEvent *event);
    void closeEvent(QCloseEvent *event);
    
  private:
    int        m_elements;
    int        m_cur;
    int**      m_activated; // -1: not yet, >= 0 activated
    QTransform m_trafo;
    Key        m_key;
    State      m_state;
  
};

#endif
