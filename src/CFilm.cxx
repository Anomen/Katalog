#include "CFilm.h"

#include <sstream>
#include <iostream>
#include <ctime>
    
using namespace std;
using namespace nsCatac;

namespace nsCatac
{
    ostream & operator << (ostream &os, const CFilm &F) 
    {
        return os << '"' << F.m_Titre << "\" :" << endl
                  << "\t- id : " << F.m_Id << endl
                  << "\t- description : " << F.m_Desc << endl
                  << "\t- genre : " << F.m_Genre << endl
                  << "\t- réalisateur : " << F.m_Realisateur << endl
                  << "\t- acteurs : " << F.m_Acteurs << endl
                  << "\t- date : " << F.GetJour() << '/' << F.GetMois() << '/' << F.GetAnnee() << endl
                  << "\t- duree : " << F.m_Duree << flush;
    }
}

void CFilm::fromReq (const string & Str)
{
    string Val;

    istringstream iss (Str);
    getline (iss, Val, '\n');

    getline (iss, Val, '\n');
    m_Id = atoi (Val.c_str());

    getline (iss, Val, '\n');
    m_Titre = Val;

    getline (iss, Val, '\n');
    m_Desc = Val;

    getline (iss, Val, '\n');
    m_Genre = Val;

    getline (iss, Val, '\n');
    m_Realisateur = Val;

    getline (iss, Val, '\n');
    m_Acteurs = Val;

    getline (iss, Val, '/');
    m_J = atoi(Val.c_str());
    getline (iss, Val, '/');
    m_M = atoi(Val.c_str());
    getline (iss, Val, '/');
    m_A = atoi(Val.c_str());

    getline (iss, Val, '\n');
    getline (iss, Val, '\n');
    m_Duree = atoi (Val.c_str());
}

string CFilm::Affich (void) const
{
    ostringstream oss;
    oss << "<h1>" << m_Titre << "</h1>"
        << "<u>Date de sortie</u>: <b>" << m_J << "/" << m_M << "/" << m_A << "</b><br />"
        << "<u>Réalisé par</u> " << m_Realisateur << "<br />"
        << "<u>Avec</u> " << m_Acteurs << "<br />"
        << "<u>Genre</u>: " << m_Genre
        << "<h3>Synopsis</h3>" << m_Desc << endl;

    return oss.str();
}
