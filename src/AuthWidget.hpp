#ifndef AUTHWIDGET_HPP
#define AUTHWIDGET_HPP

/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA
 */

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
