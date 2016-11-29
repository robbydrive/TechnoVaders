#pragma once

#include <string>
#include <ctime>
#include "ammo.hpp"
#include "gameentity.hpp"

class Gun
{
public:
  // Constructor for players
  Gun(std::string name, int holderAmmo, float bulletCaliber, float bulletVelocity, float missileCaliber, float missileVelocity,
      float limit, BulletManager & bm)
    : m_name(name), m_ammo(holderAmmo), m_holderAmmo(holderAmmo), m_bulletCaliber(bulletCaliber), m_bulletVelocity(bulletVelocity),
      m_missileCaliber(missileCaliber), m_missileVelocity(missileVelocity), m_limit(limit), m_bm(bm) {}

  // Constructor for aliens
  Gun(std::string name, int holderAmmo, float caliber, float velocity, BulletManager & bm)
    : Gun(name, holderAmmo, caliber, velocity, 0.0f, 0.0f, 0, bm) {}

  void Shot(bool isPlayer, GameEntity const & shooter)
  {
    Logger::Instance() << *this << std::endl;
    if (!m_isReloading)
    {
      m_bm.CreateBullet(isPlayer, shooter.GetBox(), m_bulletVelocity, m_bulletCaliber * m_bulletVelocity, Point2D(0.0f, 1.0f));
      if (--m_ammo == 0) Reload();
    }
    Logger::Instance() << *this << std::endl;
  }

  void Reload()
  {
    m_isReloading = true;
    timer(3000); // 3 seconds
    m_isReloading = false;
    m_ammo = m_holderAmmo;
  }

  void AccumulateScore(float damage) { m_score += damage; }

  void Launch(GameEntity const & shooter)
  {
    if (m_score >= m_limit) m_bm.CreateMissile(shooter.GetBox(), m_missileVelocity, m_missileVelocity * m_missileCaliber, Point2D(0.0f, 1.0f));
    m_score -= m_limit;
  }

  float const GetLimit() const { return m_limit; }
  float const GetScore() const { return m_score; }

  friend std::ostream & operator << (std::ostream & os, Gun const & gun)
  {
    os << "Gun: { Name = " << gun.m_name << " ; Ammo = " << gun.m_ammo << " ; HolderAmmo = " << gun.m_holderAmmo << " ; BulletCaliber = " <<
          gun.m_bulletCaliber << " ; BulletVelocity = " << gun.m_bulletVelocity << " ; MissileCaliber = " << gun.m_missileCaliber <<
          " ; MissileVelocity = " << gun.m_missileVelocity << " ; Limit = " << gun.m_limit << " ; Score = " << gun.m_score << " ; IsReloading = " <<
          gun.m_isReloading << " ; BulletManager = " << gun.m_bm;
    return os;
  }

private:
  std::string m_name;
  int m_ammo;
  int m_holderAmmo;
  float m_bulletCaliber;
  float m_bulletVelocity;
  float m_missileCaliber;
  float m_missileVelocity;
  float m_limit;
  float m_score = 0;
  bool m_isReloading = false;
  BulletManager & m_bm;

  void timer(int ms)
  {
    int CLOCKS_PER_MSEC = CLOCKS_PER_SEC / 1000;
    clock_t end_time = clock() + ms * CLOCKS_PER_MSEC;
    while (clock() < end_time) {}
  }
};
