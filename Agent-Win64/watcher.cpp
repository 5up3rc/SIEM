#include "watcher.h"
#include <QFileSystemWatcher>
#include <QDebug>
#include <QTimer>

#define SECOND_PER_MINUTE 60
#define MSEC_PER_SECOND 1000

Watcher::Watcher(QObject *parent) : QObject(parent)
{
    m_watcher = new QFileSystemWatcher(this);
    m_timer = new QTimer(this);

    // FIXME исправить на чтение параметров из QSettings
    m_mode = Mode::Timed;

    connect(m_timer, SIGNAL(timeout()), this, SLOT(debugInfo()));

    m_timer->start(10000);


    //qDebug() << m_watcher->addPath("C:/Windows/System32/winevt/Logs/Application.evtx");
   // qDebug() << m_watcher->addPath("C:/Windows/System32/winevt");

}

Watcher::~Watcher()
{
    delete m_watcher;

    if (m_timer->isActive())
        m_timer->stop();
    delete m_timer;
}

uint Watcher::interval() const
{
    return m_timer->interval();
}

void Watcher::changeMode(const Watcher::Mode mode)
{
    m_mode = mode;
}

void Watcher::debugInfo()
{
    qDebug() << "Timedout: " << m_timer->interval();
}

void Watcher::changeInterval(const uint mins)
{
    if (m_mode == Mode::Timed) {
        m_timer->start(mins * SECOND_PER_MINUTE * MSEC_PER_SECOND);
    }
}

void Watcher::updateSettings()
{
    // TODO брать новые настройки из QSettings
}

