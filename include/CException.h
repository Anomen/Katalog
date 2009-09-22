/**
 * @File   : CException.h
 *
 * @Author : Kévin Vicrey, Romain Deveaud
 *
 * @Date   : 11/12/2007
 *
**/

#if !defined __CEXCEPTION_H__
#define      __CEXCEPTION_H__

#include <string>

namespace nsUtil
{
    class CException
    {
      public:
        CException (std::string Str = "") throw();
        CException (int Num)              throw();
        ~CException (void)                throw();

        const std::string & GetStr (void) const throw();
        const int         & GetNum (void) const throw();

      private:
        std::string m_Str;
        int         m_Num;

    };
}

#include "CException.hxx"

#endif    /*  __CEXCEPTION_H__ */
