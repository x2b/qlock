#include <iostream>
using namespace std;

#include <QtGui>
#include "AuthWidget.hpp"

#define DIAM 0.6

AuthWidget::AuthWidget(QWidget* parent, int elements)
  : QWidget(parent),
  m_elements(elements),
  m_cur(0),
  m_state(UNKNOWN)
{
  m_activated = new int*[elements];
  for(int i = 0; i < m_elements; ++i)
  {
    m_activated[i] = new int[m_elements];
    for(int j = 0; j < m_elements; ++j)
      m_activated[i][j] = -1;
  }
  
  QPalette pal = palette();
  pal.setColor(backgroundRole(), Qt::white);
  setPalette(pal);
}

void AuthWidget::paintEvent(QPaintEvent * /*event*/)
{
  QPainter painter(this);
  painter.setTransform(m_trafo);
  painter.setBackground(Qt::white);
  painter.setRenderHint(QPainter::Antialiasing, true);
  
  for(int i = 1; i < (int) m_key.size(); ++i)
  {
    Entry p1 = m_key[i-1], p2 = m_key[i];
    painter.drawLine(QPointF(p1.i + 0.5, p1.j + 0.5),
      QPointF(p2.i + 0.5, p2.j + 0.5));
  }
  
  for(int i = 0; i < m_elements; ++i)
  {
    for(int j = 0; j < m_elements; ++j)
    {
      if(m_activated[i][j] != -1)
        switch(m_state)
        {
          case UNKNOWN:
            painter.setBrush(Qt::yellow);
            break;
          case CORRECT:
            painter.setBrush(Qt::green);
            break;
          case INCORRECT:
            painter.setBrush(Qt::red);
            break;
        }
      else
        painter.setBrush(Qt::transparent);
      painter.drawEllipse(QRectF(i+(1-DIAM)/2.,j+(1-DIAM)/2.,DIAM,DIAM));
    }
  }
}

void AuthWidget::mouseMoveEvent(QMouseEvent * event)
{
  if(m_state != UNKNOWN)
    return;
  QPointF pt = m_trafo.inverted().map(event->posF());
  int i = qFloor(pt.x());
  int j = qFloor(pt.y());
  
  if( i < 0 || j < 0 || i >= m_elements || j >= m_elements)
    return;
  
  double dx = pt.x() - i - 0.5;
  double dy = pt.y() - j - 0.5;
  
  if( 4*(dx*dx + dy*dy) <= DIAM*DIAM && m_activated[i][j] == -1 )
  {
    m_activated[i][j] = m_cur++;
    m_key.push_back(Entry(i,j));
    repaint();
  }
}

void AuthWidget::mouseReleaseEvent(QMouseEvent * /*event*/)
{
  if(m_state != UNKNOWN)
    return;
  if(m_key.size() > 0)
  {
    emit KeyAcquired(m_key);
  }
}

void AuthWidget::setState(State state)
{
  if(state == m_state)
    return;
  m_state = state;
  repaint();
}

void AuthWidget::reset()
{
  for(int i = 0;i < m_elements; ++i)
  {
    for(int j = 0; j < m_elements;++j)
    {
      m_activated[i][j] = -1;
    }
  }
  m_state = UNKNOWN;
  m_key.clear();
  m_cur= 0;
  repaint();
}

void AuthWidget::resizeEvent(QResizeEvent * /*event*/)
{
  int x = size().width();
  int y = size().height();
  int w = qMin(x / m_elements, y / m_elements);
  
  m_trafo = QTransform();
  m_trafo.translate((x-w*m_elements)/2., (y-w*m_elements)/2.);
  m_trafo.scale(w, w);
}

void AuthWidget::closeEvent(QCloseEvent *event)
{
  event->ignore();
}

AuthWidget::~AuthWidget()
{
  for(int j = 0; j < m_elements; ++j)
    delete[] m_activated[j];
  delete[] m_activated;
}
