#ifndef AUTHCREATOR_HPP
#define AUTHCREATOR_HPP

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
