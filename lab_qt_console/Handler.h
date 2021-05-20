#ifndef HANDLER_H
#define HANDLER_H

#include <QObject>
#include <QTimerEvent>
#include <QSocketNotifier>

#include <vector>
#include <set>
#include <utility>
#include <string>
#include <functional>

class Handler : public QObject
{
Q_OBJECT

private:
  std::function<bool(const std::string&, const std::string&)> cmp = [&](const std::string& lhs, const std::string& rhs) -> bool 
  {
    size_t lhs_size = 0, rhs_size = 0;
    size_t counter = 0;
    for (auto& p : vec)
    {
      if (lhs == p.first)
      {
        lhs_size = p.second;
        counter++;
      }
      if (rhs == p.first)
      {
        rhs_size = p.second;
        counter++;
      }
      if (counter == 2) break;
    }
    if (lhs_size == rhs_size)
    {
      return lhs < rhs;
    }
    else
    {
      return lhs_size < rhs_size;
    }
  };


private:
  int m_timeout;
  int m_timerId;

  double avg;
  
  QSocketNotifier* m_notifier;

  std::vector<std::pair<std::string, size_t>> vec;
  std::set<std::string, decltype(cmp)> s;

private:
  void timerStop();
  void timerStart();
  void timerTimeout(int interval);

  void printSet() const;

protected:
  virtual void timerEvent(QTimerEvent*) override;

public:
  static const int CODE_TO_RESTART;

public:
  Handler(QObject* parent = 0);

signals:
  void exit(int n);

private slots:
  void ReadSlot();
  void ExitSlot(int n);
};

#endif //HANDLER_H
