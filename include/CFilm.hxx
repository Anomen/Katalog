#if !defined __CFILM_HXX__
#define      __CFILM_HXX__

inline nsCatac::CFilm::CFilm (std::string Titre, unsigned Num)
      : m_Titre (Titre), m_Desc (""), m_Genre (""), m_Realisateur (""), m_Acteurs (""),
      m_Url (""), m_J (0), m_M (0), m_A (0), m_Duree (0), m_Id (0), m_Num (Num)
{ 
    setText (0, QString::fromUtf8 (m_Titre.c_str()));
    setIcon (0, QIcon(QString::fromUtf8(":/icon_film.png")));
}

inline std::string nsCatac::CFilm::GetTitre() const { return m_Titre; }
inline std::string nsCatac::CFilm::GetDesc () const { return m_Desc;  }
inline std::string nsCatac::CFilm::GetGenre() const { return m_Genre; }
inline std::string nsCatac::CFilm::GetRealisateur() const { return m_Realisateur;}
inline std::string nsCatac::CFilm::GetActeurs    () const { return m_Acteurs;    }
inline std::string nsCatac::CFilm::GetUrl        () const { return m_Url;        }
inline unsigned    nsCatac::CFilm::GetDuree() const { return m_Duree; }
inline unsigned    nsCatac::CFilm::GetId   () const { return m_Id; }
inline unsigned    nsCatac::CFilm::GetNum  () const { return m_Num; }
inline unsigned    nsCatac::CFilm::GetJour () const { return m_J; }
inline unsigned    nsCatac::CFilm::GetMois () const { return m_M; }
inline unsigned    nsCatac::CFilm::GetAnnee() const { return m_A; }

inline void nsCatac::CFilm::SetTitre (std::string Titre) { m_Titre = Titre; }
inline void nsCatac::CFilm::SetDesc  (std::string Desc ) { m_Desc = Desc; }
inline void nsCatac::CFilm::SetGenre (std::string Genre) { m_Genre = Genre; }
inline void nsCatac::CFilm::SetRealisateur (std::string Realisateur) { m_Realisateur = Realisateur; }
inline void nsCatac::CFilm::SetActeurs(std::string Acteurs) { m_Acteurs = Acteurs; }
inline void nsCatac::CFilm::SetUrl    (std::string Url    ) { m_Url = Url; }
inline void nsCatac::CFilm::SetDuree  (unsigned Duree) { m_Duree = Duree; }
inline void nsCatac::CFilm::SetId     (unsigned Id) { m_Id = Id; }
inline void nsCatac::CFilm::SetJour   (unsigned J) { m_J = J; }
inline void nsCatac::CFilm::SetMois   (unsigned M) { m_M = M; }
inline void nsCatac::CFilm::SetAnnee  (unsigned A) { m_A = A; }

#endif
