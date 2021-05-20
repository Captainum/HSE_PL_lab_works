#include "Handler.h"

#include <QCoreApplication>
#include <QDir>
#include <QFileInfo>

#include <iostream>
#include <limits>

const int Handler::CODE_TO_RESTART = -123456789;

void Handler::timerStop()
{
  if (m_timerId == -1)
  {
    std::cout << "There is no timer to stop\n> ";
  }
  else
  {
    std::cout << "Timer has been stopped\n> ";
    killTimer(m_timerId);
    m_timerId = -1;
  }
  std::cout.flush();
}

void Handler::timerStart()
{
  if (m_timerId != -1)
  {
    std::cout << "Timer has already started\n> ";
  }
  else if (m_timeout == -1)
  {
    std::cout << "Enter timeout <interval>\n> ";
  }
  else
  {
    std::cout << "Timer has been started\n> ";
    m_timerId = startTimer(m_timeout);

    printSet(); 
  }
  std::cout.flush();
}

void Handler::timerTimeout(int interval)
{
  if (interval < 0)
  {
    std::cout << "Interval is incorrect\n> ";
  }
  else if (m_timerId != -1)
  {
    std::cout << "You have to stop the current timer\n> ";
  }
  else
  {
    std::cout << "Timeout has been changed\n> ";
    m_timeout = interval;
  }
  std::cout.flush();
}

void Handler::timerEvent(QTimerEvent*)
{
  if (s.size() == 0)
  {
    printSet();
    return ;
  }
  double tavg = avg * 0.75;
  double min = std::numeric_limits<double>::max();
  std::string str_to_delete = "";
  size_t val = 0;

  for (const auto& file : s)
  {
    for (const auto& p : vec)
    {
      if (p.first == file)
      {
        double delta = p.second - tavg;
        delta *= delta;
        if (delta < min)
        {
          min = delta;
          str_to_delete = file;
          val = p.second;
        }
        break;
      }
    }
  }

  s.erase(str_to_delete);
  avg = ((avg * (s.size() + 1)) - val) / s.size();

  printSet();
}

void Handler::printSet() const
{
  auto counter = s.size();
  std::cout << "\r{";
  for (const auto& el : s)
  {
    std::cout << el;
    if (--counter)
    {
      std::cout << ", ";
    }
  }
  std::cout << "}\n> " << std::flush;
}

Handler::Handler(QObject* parent) : QObject(parent), m_timeout(-1), m_timerId(-1), avg(0.0)
{
  m_notifier = new QSocketNotifier(fileno(stdin), QSocketNotifier::Read, this);
  s = std::set<std::string, decltype(cmp)>(cmp);

  QDir dir(QDir::current());
  auto files = dir.entryInfoList(QDir::Files | QDir::Hidden);
  
  vec.reserve(files.size());

  for (const auto& file : files)
  {
    vec.push_back(std::make_pair(file.fileName().toStdString(), static_cast<size_t>(file.size())));
  }

  for (const auto& p : vec)
  {
    avg += p.second;
    s.insert(p.first);
  }

  avg /= files.size();
  
  connect(m_notifier, SIGNAL(activated(int)), this, SLOT(ReadSlot()));
  connect(this, SIGNAL(exit(int)), this, SLOT(ExitSlot(int)));

  std::cout << "> " << std::flush;
}

void Handler::ReadSlot()
{
  std::string s;
  std::getline(std::cin, s);
  if (s == "")
  {
    std::cout << "> " << std::flush;
  }
  else if (s == "stop")
  {
    timerStop();
  }
  else if (s == "start")
  {
    timerStart();
  }
  else if (s == "restart")
  {
    emit exit(Handler::CODE_TO_RESTART);
  }
  else if (s == "exit")
  {
    emit exit(0);
  }
  else
  { 
    auto spc = s.find(' ', 0);
    auto word = s.substr(0, spc);
      
    if (word == "timeout")
    {
      auto word2 = s.substr(spc+1);
      try
      {
        int interval = std::stoi(word2);
        if (std::to_string(interval) == word2)
        {
          timerTimeout(interval);
        }
        else
        {
          std::cout << "Interval must be integer\n> ";
        }
      }
      catch (...)
      {
        std::cout << "Enter \"timeout <integer interval>\"\n> ";
      }
    }
    else
    {
      std::cout << "No such command: " << s << "\n> ";
    }
  }
  std::cout.flush();
}

void Handler::ExitSlot(int n)
{
  if (n == 0) QCoreApplication::exit(0);
  else if (n == Handler::CODE_TO_RESTART) QCoreApplication::exit(Handler::CODE_TO_RESTART);
}
