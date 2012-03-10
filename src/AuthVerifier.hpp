#ifndef AUTHVERIFIER_HPP
#define AUTHVERIFIER_HPP

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
