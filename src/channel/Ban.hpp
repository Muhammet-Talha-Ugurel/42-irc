#ifndef BAN_H

#define BAN_H

#include <ctime>
#include <string>

class Ban
{
  private:
    std::string _banner;
    std::string _mask;
    time_t      _time;

  public:
    Ban() : _banner(""), _mask(""), _time(0) {}

    Ban(const std::string &banner, const std::string &mask, time_t time) : _banner(banner), _mask(mask), _time(time) {}

    Ban(const Ban &other)
    {
      _banner = other._banner;
      _mask   = other._mask;
      _time   = other._time;
    }

    Ban &operator=(const Ban &other)
    {
      if (this != &other)
      {
        _banner = other._banner;
        _mask   = other._mask;
        _time   = other._time;
      }
      return *this;
    }

    bool operator==(const Ban &other) const
    {
      return (_banner == other._banner && _mask == other._mask && _time == other._time);
    }

    bool        operator!=(const Ban &other) const { return !(*this == other); }
    bool        operator<(const Ban &other) const { return _time < other._time; }
    bool        operator>(const Ban &other) const { return _time > other._time; }

    std::string getBanner() const { return _banner; }
    void        setBanner(const std::string &banner) { _banner = banner; }

    std::string getMask() const { return _mask; }
    void        setMask(const std::string &mask) { _mask = mask; }

    time_t      getTime() const { return _time; }
    void        setTime(time_t time) { _time = time; }

    std::string toString() const { return _banner + " " + _mask + " " + ctime(&_time); }
};

#endif // BAN_H
